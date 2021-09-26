



 






 
F_BMA253_INIT: 

 STZ R_GSENSOR_SAVEP
 STZ R_GSENSOR_SAVES

.IF( C_BMA253_HWSPI_EN .EQ. 1 )

 SPI_INIT
.ENDIF

 JSR BMA222E_RESET_TO_NORMAL

 
 JSR F_BMA253_READ_POLLING

 LDA R_BMA253_RTN
 BEQ L_BMA253_NOTREAD
 CMP #C_BMA253_CHIP_ID
 BEQ L_BMA253_SETUP
L_BMA253_NOTREAD:
 INC R_BMA253_RTN
 RTS
 
L_BMA253_SETUP: 
 LDA #C_BMA253_RANGE_SELECT_ADDR 
 STA R_BMA253_ADDR
 LDA #C_BMA253_RANGE
 STA R_BMA253_DATA
 JSR F_BMA253_WRITE1BYTE
 
 LDA #C_BMA253_BW_SELECT_ADDR 
 STA R_BMA253_ADDR
 LDA #C_BMA253_PMU_BW
 STA R_BMA253_DATA
 JSR F_BMA253_WRITE1BYTE
 
 LDA #C_BMA253_DATA_CTRL_ADDR
 STA R_BMA253_ADDR
 LDA #C_BMA253_FILTERED 
 STA R_BMA253_DATA
 JSR F_BMA253_WRITE1BYTE
 
 LDA #C_BMA253_INTR_SET_ADDR
 STA R_BMA253_ADDR
 LDA #C_BMA253_INT_CTRL 
 STA R_BMA253_DATA
 JSR F_BMA253_WRITE1BYTE
 
 
 
 STZ R_BMA253_RTN
 RTS


 
 



F_BMA253_READXYZ:
 STZ R_BMA253_CNT
 STZ R_BMA253_RTN 
 LDA #.LOW.R_BMA253_XVAL
 STA R_BMA253_PT 
 LDA #.HIGH.R_BMA253_XVAL
 STA R_BMA253_PT+1 
 SPI_ON
 SPI_WRITE (C_BMA253_X_LSB_ADDR+80H)
L_BMA253_READXYZ_WAIT:
 SPI_READ   
 LDA R_BMA253_CNT
 BIT #01H
 BNE F_BMA253_READXYZ_MSB
F_BMA253_READXYZ_LSB:
 TYA 
 LSR A
 ROL R_BMA253_RTN 
 BRA F_BMA253_READXYZ_NEXTBYTE
F_BMA253_READXYZ_MSB:
 LDA R_BMA253_CNT 
 LSR A    
 PHA 
 TYA 
 PLY 
 STA (<R_BMA253_PT),Y 
F_BMA253_READXYZ_NEXTBYTE:
 INC R_BMA253_CNT
 LDA R_BMA253_CNT
 CMP #006
 BCS 3
 JMP L_BMA253_READXYZ_WAIT
 SPI_OFF
 RTS

F_BMA253_NORMAL_MODE:
 LDA #C_BMA253_MODE_CTRL_ADDR
 STA R_BMA253_ADDR
 LDA #C_BMA253_NORMALMODE
 STA R_BMA253_DATA


F_BMA253_WRITE1BYTE:
 SPI_ON 
 SPI_WRITE_RAM R_BMA253_ADDR
 SPI_WRITE_RAM R_BMA253_DATA
 SPI_OFF
 RTS 
F_BMA253_READ_POLLING:
 SPI_ON
 SPI_WRITE (C_BMA253_CHIP_ADDR+80H)
 SPI_READ
 STA R_BMA253_RTN
 SPI_OFF
DEBUG_HW_SETUP:
 LDA R_BMA253_RTN
 CMP #0FAH 
 BNE DEBUG_HW_SETUP
 
 RTS
BMA253_DEEPSUSPEND:
 LDA #C_BMA253_MODE_CTRL_ADDR 
 STA R_BMA253_ADDR
 LDA #00100000B
 STA R_BMA253_DATA
 JSR F_BMA253_WRITE1BYTE
 RTS
 



F_GSENSOR_SAVEXYZ_EXIT:
 RTS
F_GSENSOR_SAVEXYZ:








 LDX R_GSENSOR_SAVEP
 LDA R_BMA253_XVAL
 STA R_SAVEX_BASE, X
 LDA R_BMA253_YVAL
 STA R_SAVEY_BASE, X
 LDA R_BMA253_ZVAL
 STA R_SAVEZ_BASE, X
 INX
 CPX #C_GDATA_STOTAL
 BCC L_GSENSOR_SAVEXYZ_PT_UPDATED
 LDX #0 
L_GSENSOR_SAVEXYZ_PT_UPDATED:
 STX R_GSENSOR_SAVEP
 
 CPX R_GSENSOR_SAVES
 BEQ L_GSENSOR_END_MOVE
 RTS
 
L_GSENSOR_END_MOVE: 
 STZ R_SAVEX_BASE, X
 STZ R_SAVEY_BASE, X
 STZ R_SAVEZ_BASE, X
 INX
 CPX #C_GDATA_STOTAL
 BCC L_GSENSOR_SAVEXYZ_END_UPDATED
 LDX #0
L_GSENSOR_SAVEXYZ_END_UPDATED:
 STX R_GSENSOR_SAVES
 RTS 


 
 
 



 
 
