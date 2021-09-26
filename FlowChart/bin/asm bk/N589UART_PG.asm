;N589 software UART handle
;by Garfield Lam @ Trinity Electronics Limited
;UART baud rate=9600
;TimerA used
;
;	CHIP		N589
;	INCLUDE		PGM_HEAD.INI
;	INCLUDE		N589UART.ini
;	PUBLIC	R_UART_Port_Value
;	PUBLIC	R_UART_Tx_Data	;destory when done
;	PUBLIC	R_UART_Rx_Data	;user clear after read
;	PUBLIC	R_UART_Port_Mode
;
;	PUBLIC	F_UART_Port_Init
;.ifdef C_UART_RECEIVE_EN	
;	PUBLIC	F_UART_Port_ISR
;.endif	
;	PUBLIC	F_UART_TimerA_ISR
;	PUBLIC	F_UART_Send_Data
;	
;	EXTERN	C_Gdata_STotal
;	EXTERN	R_SaveX_Base
;	EXTERN	R_SaveY_Base
;	EXTERN	R_SaveZ_Base
		
		
	USER_RAM:	SECTION
R_UART_Port_Value	DS	1
R_UART_Port_Mode	DS	1
R_UART_Tx_Data		DS	1	;data to send, destory 
R_UART_Rx_Data		DS	1
R_UART_TxRx_Step	DS	1	;step of UART Timer
R_UART_Tx_Pt		DS	1	;point to Tx data array
R_UART_Tx_Set		DS	1	;which set data
C_UART_TX_TOTAL_SET	EQU	3 ;XYZ DATA
;C_UART_TX_PT_FINAL	EQU	4	;last byte
;R_UART_Tx_Array		DS	4	;4 byte to send

C_UART_TMRA_C	EQU	07H
C_UART_TMRA_V	EQU	16	;9600*2Hz  for band=9600,1(start)+8(data),+4 bit stop
C_UART_TX_FINISH	EQU	9	;step 9*2=18
C_UART_TX_WAIT_TIME	EQU	8	;wait 4 bit time to send next byte

;C_UART_RECEIVE_EN	EQU	1

	.ENDS
	
	CODE:	SECTION
		
		
;==============================
;call when POR		
;==============================
;
F_UART_Port_Init:
	LDA	#C_UART_TX_PIN
	TSB	!C_UART_TX_PORT_DATA
	TRB	!C_UART_TX_PORT_DIR
	TSB	!C_UART_TX_PORT_MODE
	
	;enable RX PIN interrupt
.IFDEF C_UART_RECEIVE_EN
	LDA	#C_UART_RX_PIN
	STA	!C_UART_RX_PORT_EN
	LDA	!IEF0
	ORA	#INT0_PORT
	STA	!IEF0	
.ENDIF	 ;C_UART_RECEIVE_EN

	RTS

;=============================
;	call when UART START
;==============================	
F_UART_INIT:
	LDA	!IEF0
.ifdef C_UART_RECEIVE_EN	
	AND	#~INT0_PORT
.endif   ;C_UART_RECEIVE_EN
	ORA	#INT0_TMA
	STA	!IEF0
	LDA	#C_UART_TMRA_V
	STA	!TMAV
	LDA	#C_UART_TMRA_C
	STA	!TMAC
	
	RTS
	
;==============================
;------Interface-----------
;call when need to send data
;==============================
F_UART_Send_Data:	;start to send data
	;disable port interrupt
	
	JSR	F_UART_INIT
	
	STZ	R_UART_Tx_Pt
	STZ	R_UART_Tx_Set

	LDA	R_SaveX_Base
	STA	R_UART_Tx_Data	;1st byte of data to send
;DEBUG
;	LDA	#55H
;	STA	R_UART_Tx_Data
		
	STZ	R_UART_TxRx_Step

	LDA	#C_UART_TX_PIN
	TRB	C_UART_TX_PORT_DATA
	
	;setup timerA
	LDA	#C_UART_DATA_SENDING
	STA	R_UART_Port_Mode
	
	RTS
	
;=========================================
; call at timerA
;=========================================
;	PHX ;X used
;	JSR F_UART_TimerA_ISR	;for UART Bard Rate operation
;	PLX
;==================================================
F_UART_TimerA_ISR:
	LDA	R_UART_Port_Mode
	BIT	#C_UART_DATA_SENDING
	BNE	L_UART_Sending
	BIT	#C_UART_WAIT_SEND
	BNE	L_UART_WAITING
.ifdef C_UART_RECEIVE_EN			
	BIT	#C_UART_RECEIVING
	BEQ	L_UART_TimerA_Exit
	JMP	L_UART_Receiving_Data
.endif	;C_UART_RECEIVE_EN
L_UART_TimerA_Exit:	
	RTS

L_UART_WAITING:
	INC	R_UART_TxRx_Step
	LDA	R_UART_TxRx_Step
	CMP	#C_UART_TX_WAIT_TIME
	BCC	L_UART_WAITING_Exit
	;send next byte
	LDA	#C_UART_DATA_SENDING
	STA	R_UART_Port_Mode
	STZ	R_UART_TxRx_Step
	BRA	L_UART_Tx_Low	;Start Bit
L_UART_WAITING_Exit:	
	RTS
	

L_UART_Sending:
	INC	R_UART_TxRx_Step
	LDA	R_UART_TxRx_Step	;0-1=start bit, 2-3=bit0, 4-5=bit1, 6-7=bit2, 8-9=bit3, 10-11=bit4, 12-13=bit5, 14-15=bit6, 16-17=bit7, 18=finished
	LSR	A
	BCS	L_UART_TimerA_Exit	;middle between pulse
	CMP	#C_UART_TX_FINISH
	BCS	L_UART_Tx_Sent1Byte
	;from 2~18->1~9
	LSR	R_UART_Tx_Data
	BCS	L_UART_Tx_High
	;UART send bit Low
L_UART_Tx_Low:
	LDA	#C_UART_TX_PIN
	TRB	C_UART_TX_PORT_DATA

	BRA	L_UART_Tx_WritePort
	
L_UART_Tx_Sent1Byte:	
	;finished 1 byte, change to wait 4 bit cycle
	INC	R_UART_Tx_Set
	LDA	R_UART_Tx_Set
	CMP	#C_UART_TX_TOTAL_SET
	BCC	L_UART_Tx_Wait_NextByte
	STZ	R_UART_Tx_Set
	INC	R_UART_Tx_Pt
	LDX	R_UART_Tx_Pt	
	CPX	#C_Gdata_STotal ; X BYTE For X,Y,Z axis
	BCC	L_UART_Tx_Wait_NextByte
;END
	;4 byte send done, turn off TimerA, enable Port Interrupt
	STZ	!TMAC
	LDA	!IEF0
	AND	#~INT0_TMA
.ifdef C_UART_RECEIVE_EN	
	ORA	#INT0_PORT
.endif	;C_UART_RECEIVE_EN
	STA	!IEF0	
	STZ	R_UART_Port_Mode

;
;	MR_XYZ_SAVE_EN
	
	BRA	L_UART_Tx_High
	
L_UART_Tx_Wait_NextByte:	
	LDA	#C_UART_WAIT_SEND
	STA	R_UART_Port_Mode
	STZ	R_UART_TxRx_Step

	LDX	R_UART_Tx_Pt	
	LDA	R_UART_Tx_Set
	BEQ	L_Load_SetX_data
	CMP	#1
	BEQ	L_Load_SetY_data
	LDA	R_SaveZ_Base,X
	BRA	L_Save_Tx_Data
L_Load_SetX_data:	
	LDA	R_SaveX_Base,X
	BRA	L_Save_Tx_Data
L_Load_SetY_data:	
	LDA	R_SaveY_Base,X
L_Save_Tx_Data:	
	STA	R_UART_Tx_Data	;prepared data
L_UART_Tx_High:
	LDA	#C_UART_TX_PIN
	TSB	C_UART_TX_PORT_DATA
	
L_UART_Tx_WritePort:	

	RTS
	
	
;==================================================
.IFDEF C_UART_RECEIVE_EN		
L_UART_Receiving_Data:
	INC	R_UART_TxRx_Step	
	;1-2=start bit, 3-4=bit0 (read at 3), 5-6=bit1, 7-8=bit2, 9-10=bit3, 11-12=bit4, 13-14=bit5, 15-16=bit6, 17-18=bit7, 19->exit
	LDA	R_UART_TxRx_Step
	LSR	A
	BCC	L_UART_Receiving_Exit
	;if A=0->start bit, other value save data
	BEQ	L_UART_Receiving_Exit
	;save data?
	CMP	#C_UART_TX_FINISH
	BCS	L_UART_Received_Data	;8 bit recieved
	;saving data, Carry is clear
	LDA	!C_UART_TX_PORT_DATA
	AND	#C_UART_RX_PIN
	BEQ	L_UART_Save_BitLow
	;save bit high
	SEC		
L_UART_Save_BitLow:	
	ROR	R_UART_Rx_Data
L_UART_Receiving_Exit:
	RTS
	
L_UART_Received_Data:	;all bit received
	LDA	#C_UART_RECEIVED	
	STA	R_UART_Port_Mode
	;data in R_UART_Rx_Data, disable TmrA, enable Port Interrupt
	STZ	!TMAC
	LDA	!IEF0
	AND	#~INT0_TMA
	ORA	#INT0_PORT
	STA	!IEF0	
	RTS
	
	
F_UART_Port_ISR:
	LDA	!C_UART_TX_PORT_DATA
	AND	#C_UART_RX_PIN
	BEQ	L_UART_Rx_Start_Bit
	RTS
	
L_UART_Rx_Start_Bit:	
	LDA	!IEF0
	AND	#~INT0_PORT
	ORA	#INT0_TMA
	STA	!IEF0	
	STZ	R_UART_TxRx_Step
	;setup timerA
	LDA	#C_UART_TMRA_V
	STA	!TMAV
	LDA	#C_UART_TMRA_C
	STA	!TMAC
	LDA	#C_UART_RECEIVING
	STA	R_UART_Port_Mode
	RTS
.ENDIF ;C_UART_RECEIVE_EN
	
	ENDS
				