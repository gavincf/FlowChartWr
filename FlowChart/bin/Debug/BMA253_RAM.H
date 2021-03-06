


DIR6_FLAG DS 1



DIR6_CNT DS 1

 
GSENSOR_DLY DS 1





R_1ST_AVR_CNT DS 1

R_AVR_FLAG DS 1




 
XAVR_P DS 1
YAVR_P DS 1
ZAVR_P DS 1

R_AVR1_FLAG DS 1



XAVR1_P DS 1
YAVR1_P DS 1
ZAVR1_P DS 1

R_XVAL DS 1
R_YVAL DS 1
R_ZVAL DS 1





C_PLUS EQU 0
C_MINUS EQU 1
C_HORIZONTAL_DIR EQU C_MINUS
C_VERTICAL_DIR EQU C_MINUS

R_HORIZONTAL_VAL_P EQU R_XVAL
R_HORIZONTAL_AVR_P EQU XAVR_P

R_VERTICAL_VAL_P EQU R_YVAL
R_VERTICAL_AVR_P  EQU YAVR_P




MR_AVR_X_EN MACRO
  LDA #C_BIT0
  TSB R_AVR_FLAG
 ENDM
MR_AVR_Y_EN MACRO
  LDA #C_BIT1
  TSB R_AVR_FLAG
 ENDM
MR_AVR_Z_EN MACRO
  LDA #C_BIT2
  TSB R_AVR_FLAG
 ENDM

MR_AVR_X_DIS MACRO
  LDA #C_BIT0
  TRB R_AVR_FLAG
 ENDM
MR_AVR_Y_DIS MACRO
  LDA #C_BIT1
  TRB R_AVR_FLAG
 ENDM
MR_AVR_Z_DIS MACRO
  LDA #C_BIT2
  TRB R_AVR_FLAG
 ENDM

MR_BMA222E_WR MACRO ADDR,VALUE
 LDA #ADDR
 STA R_BMA253_ADDR
 LDA #VALUE
 STA R_BMA253_DATA
 JSR F_BMA253_WRITE1BYTE
 ENDM

MR_BMA222E_RD MACRO ADDR
 SPI_ON
 SPI_WRITE (ADDR+80H)
 SPI_READ
 STA R_BMA253_RTN
 SPI_OFF
 ENDM

