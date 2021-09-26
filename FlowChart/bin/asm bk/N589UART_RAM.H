;N589 software UART handle
;by Garfield Lam @ Trinity Electronics Limited
;UART baud rate=9600
;
;1,include N589UART_RAM.H,N589UART_PG.asm,setting IO in: N589UART_RAM.H
; call 'F_UART_Port_Init' as intial IO,enable TMGX for tranmitt TX.
;2,use MCU 1 io as UART_TX pin connect to CH341A UART RX
;3,manual mode:use MCU 1 Io as Trigger key, connect 1 key to GND
;4,when trigger key, call 'F_UART_Send_Data'.


;===================================
;	SETTING
;===================================
C_UART_TX_PORT_DATA	EQU	BP2R;BP3R
C_UART_TX_PORT_DIR		EQU	BP2D;BP3D
C_UART_TX_PORT_MODE	EQU	BP2M;BP3M
C_UART_TX_PIN		EQU	C_BIT4

C_UART_RX_PORT_EN		EQU	BP2EN;BP3EN

.IFDEF C_UART_RECEIVE_EN		
C_UART_RX_PIN		EQU	00H
.ENDIF
	
C_UART_MODE_IDLE	EQU	0
C_UART_DATA_SENDING	EQU	1
C_UART_WAIT_SEND	EQU	2	;wait next cycle to send
C_UART_RECEIVING	EQU	4
C_UART_RECEIVED		EQU	8
;	EXTERN	R_UART_Tx_Array	;4 byte data array to be send


