;	SPI_ON ;for F/W / H/W
;	SPI_WRITE_RAM	R_BMA253_Addr;for F/W / H/W
;	SPI_WRITE_RAM	R_BMA253_Data;for F/W / H/W
;	SPI_OFF;for F/W / H/W
	
;BMA253 G sensor by N589 SPIO
;Interrupt mode did not setup yet
;By Garfield Lam
;Date 20191120


	
F_BMA253_Init:	;Initial BMA253 with SPIO port

	STZ	R_Gsensor_SaveP
	STZ	R_Gsensor_SaveS

.IF( C_BMA253_HWSPI_EN .EQ. 1 )
;for HW interface 
	SPI_INIT
.ENDIF

	JSR	BMA222E_RESET_TO_NORMAL

	
	JSR	F_BMA253_Read_Polling
;
	LDA	R_BMA253_rtn
	BEQ	L_BMA253_NotRead
	CMP	#C_BMA253_CHIP_ID
	BEQ	L_BMA253_Setup
L_BMA253_NotRead:
	INC	R_BMA253_rtn
	RTS
	
L_BMA253_Setup:	
	LDA	#C_BMA253_RANGE_SELECT_ADDR	;Range
	STA	R_BMA253_Addr
	LDA	#C_BMA253_RANGE
	STA	R_BMA253_Data
	JSR F_BMA253_Write1byte
	
	LDA	#C_BMA253_BW_SELECT_ADDR	;bandwidth
	STA	R_BMA253_Addr
	LDA	#C_BMA253_PMU_BW
	STA	R_BMA253_Data
	JSR F_BMA253_Write1byte
	
	LDA	#C_BMA253_DATA_CTRL_ADDR
	STA	R_BMA253_Addr
	LDA	#C_BMA253_FILTERED	;filtered
	STA	R_BMA253_Data
	JSR F_BMA253_Write1byte
	
	LDA	#C_BMA253_INTR_SET_ADDR
	STA	R_BMA253_Addr
	LDA	#C_BMA253_INT_CTRL	;push-pull,active low
	STA	R_BMA253_Data
	JSR F_BMA253_Write1byte
	
	;@_@ Interrupt mode did not setup yet
	
	STZ	R_BMA253_rtn
	RTS


	
	
;--------------------------------------------------------------
;read XYZ MSB :store in R_BMA253_Xval+0:R_BMA253_Xval+1:R_BMA253_Xval+2
;--------------------------------------------------------------
F_BMA253_ReadXYZ:
	STZ	R_BMA253_Cnt
	STZ	R_BMA253_rtn	;bit2=X,bit1=Y,bit0=Z changed
	LDA	#.LOW.R_BMA253_Xval
	STA	R_BMA253_pt ;store ram address
	LDA	#.HIGH.R_BMA253_Xval
	STA	R_BMA253_pt+1 ;store ram address
	SPI_ON
	SPI_WRITE	(C_BMA253_X_LSB_ADDR+80H)
L_BMA253_ReadXYZ_Wait:
	SPI_READ			; result in A and Y
	LDA	R_BMA253_Cnt
	BIT	#01H
	BNE	F_BMA253_ReadXYZ_MSB
F_BMA253_ReadXYZ_LSB:
	TYA	; data from G-sensor ;store high byte data
	LSR	A
	ROL	R_BMA253_rtn ;skip LSB
	BRA	F_BMA253_ReadXYZ_NextByte
F_BMA253_ReadXYZ_MSB:
	LDA	R_BMA253_Cnt	; 1,3,5
	LSR	A				; 0,1,2
	PHA ;STACK
	TYA	; data from G-sensor
	PLY	; RAM pointer to Y ;stack
	STA	(<R_BMA253_pt),Y ;store
F_BMA253_ReadXYZ_NextByte:
	INC	R_BMA253_Cnt
	LDA	R_BMA253_Cnt
	CMP	#006
	BCS	3
	JMP	L_BMA253_ReadXYZ_Wait
	SPI_OFF
	RTS
;-----------------------------------------------
F_BMA253_Normal_Mode:
	LDA	#C_BMA253_MODE_CTRL_ADDR
	STA	R_BMA253_Addr
	LDA	#C_BMA253_NORMALMODE
	STA	R_BMA253_Data
;	JMP F_BMA253_Write1byte	
;------------------------------------------
F_BMA253_Write1byte:
	SPI_ON ;for F/W / H/W
	SPI_WRITE_RAM	R_BMA253_Addr
	SPI_WRITE_RAM	R_BMA253_Data
	SPI_OFF;for F/W / H/W
	RTS	
F_BMA253_Read_Polling:
	SPI_ON
	SPI_WRITE	(C_BMA253_CHIP_ADDR+80H)
	SPI_READ
	STA	R_BMA253_rtn
	SPI_OFF
DEBUG_HW_SETUP:
	LDA	R_BMA253_rtn
	CMP	#0FAH ;--------BMA253 ID
	BNE	DEBUG_HW_SETUP
	
	RTS
BMA253_DeepSuspend:
	LDA	#C_BMA253_MODE_CTRL_ADDR	;POWER
	STA	R_BMA253_Addr
	LDA	#00100000B
	STA	R_BMA253_Data
	JSR F_BMA253_Write1byte
	RTS
	
;-------------------------------------------------------------
; --- F_Gsensor_SaveXYZ ---
;-------------------------------------------------------------
F_Gsensor_SaveXYZ_EXIT:
	RTS
F_Gsensor_SaveXYZ:
;	LDA	R_Gsensor_Skip
;	BEQ	L_Gsensor_SaveData
;	DEC	R_Gsensor_Skip
;	RTS
;L_Gsensor_SaveData:	
;	LDA	USER_FLAG20
;	BIT	#C_BIT0
;	BEQ	F_Gsensor_SaveXYZ_EXIT
	LDX	R_Gsensor_SaveP
	LDA	R_BMA253_Xval
	STA R_SaveX_Base, X
	LDA	R_BMA253_Yval
	STA R_SaveY_Base, X
	LDA	R_BMA253_Zval
	STA R_SaveZ_Base, X
	INX
	CPX	#C_Gdata_STotal
	BCC	L_Gsensor_SaveXYZ_pt_updated
	LDX	#0	;change back to start position
L_Gsensor_SaveXYZ_pt_updated:
	STX	R_Gsensor_SaveP
	;check pt reach end pointer
	CPX	R_Gsensor_SaveS
	BEQ	L_Gsensor_End_Move
	RTS
	
L_Gsensor_End_Move:	;pointer hit End point, End point move 1 step
	STZ	R_SaveX_Base, X
	STZ	R_SaveY_Base, X
	STZ	R_SaveZ_Base, X
	INX
	CPX	#C_Gdata_STotal
	BCC	L_Gsensor_SaveXYZ_End_updated
	LDX	#0
L_Gsensor_SaveXYZ_End_updated:
	STX	R_Gsensor_SaveS
	RTS	


	
	
	



	
	

