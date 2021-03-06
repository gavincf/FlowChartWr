
;=========================================================================
; CONST
;=========================================================================
;==========================================
;Module version: V01I;2018/11/12 ����һ ���� 1:45:50
;==========================================

.IFDEF C_CHK_MODE_M_EN
C_SYS_MODE_MAX	EQU	C_MAX_MODE
.ELSE
C_SYS_MODE_MAX	EQU	1
.ENDIF





;=========================================================================
; CODE0:PWON
;=========================================================================
;LVR+LVD ->SLEEP,

;RESET_F.0=1;LVR
;RESET_F.3=1;POR
;RESET_F.4=1;RESET PIN

POI_USER:
	JSR	S_CHK_RAM_OV

.IF (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
;======================================
;rugou touch exist:
;wakeup time: 20ms
;======================================
	.IF(WITH_FW_CAP_SENSOR_KEYS .GT. 0)
	M_INT_DISABLE PORT_INT_BIT
	IS_WAKEUP_FROM_TOUCH_SOURCE
	BEQ	3
	JMP	E_POI_WAKEUP_BY_CAPSENSOR	; wakeup by cap sensor ; FW DETECT
	.ENDIF
;check port wake in priority


	JSR S_N589_WAKEUP_N_RESET	; check wakeup or reset
	JMP	(E_POI_TABLE,X)
E_POI_TABLE:
	DW	E_POI_DEBUGGER_RERUN	; rerun the debugger
	DW	E_POI_RESET_RESETB		; normal -> reset pin
	DW	E_POI_RESET_LVR			; normal -> LVR
	DW	E_POI_RESET_POR			; normal -> POR
	DW	E_POI_RESET_NO_WAKEUP_SRC	; normal -> no wakeup source
	DW	E_POI_RESET_WDT			; normal -> WDT
	DW	E_POI_WAKEUP_PORT		; stop -> port
	DW	E_POI_WAKEUP_LRC		; stop -> LRC
	DW	E_POI_WAKEUP_IRWU		; stop -> IR wakeup 
	DW	E_POI_WAKEUP_RESETB		; stop -> reset pin
;===============================================
;type0 - wakeup by key from stop mode
E_POI_WAKEUP_PORT:		; sleep -> port

	JSR	S_RAM_RESTORE
	MR_WAKEUP_SET_IO
;DELAY
;	JSR	L_DELAY10MS;10MS

	.IF( C_N589_TOUCH_EN .EQ. 1 )
	EN_CAP_SENSOR
	.ENDIF
;-------------------------------------
;	N589 TYPE0 init
;-------------------------------------
	JSR	POR_MODULE_INIT
;	LDA	#1
;	STA	R_WAKEUP_FLAG
	JMP	MAIN_WAKEUP_N589
	
;===============================================
;type1 - POR, reset pin
E_POI_DEBUGGER_RERUN:
E_POI_RESET_POR:
E_POI_RESET_RESETB:
E_POI_WAKEUP_RESETB:

	MR_POI_SET_IO
	JSR	S_IP_STABLE_WAIT
	MR_PWON_SET_IO
;DELAY
;	JSR	L_DELAY10MS;10MS

	.IF( C_N589_TOUCH_EN .EQ. 1 )
	EN_CAP_SENSOR
	.ENDIF

;-------------------------------------
;	N589 TYPE1 init
;-------------------------------------
	JSR	POR_MODULE_INIT

;delay for ISP[BP00:BP01]
	JSR	L_DELAY10MS;10MS
	JSR	L_DELAY10MS;10MS
	JSR	L_DELAY10MS;10MS
	JSR	L_DELAY10MS;10MS
	JSR	L_DELAY10MS;10MS

	JMP	   POR_END
	
;===============================================
;type2 - abnormal
E_POI_WAKEUP_IRWU:		; stop -> IR wakeup 
E_POI_WAKEUP_LRC:		; stop -> LRC:
E_POI_RESET_LVR:			; normal -> LVR
E_POI_RESET_NO_WAKEUP_SRC:	; normal -> no wakeup source
E_POI_RESET_WDT:			; normal -> WDT
E_POI_RETURN:


	MR_POI_SET_IO
	JSR	S_IP_STABLE_WAIT
	MR_PWON_SET_IO
	.IF( C_N589_TOUCH_EN .EQ. 1 )
	EN_CAP_SENSOR
	.ENDIF
;	JSR	L_DELAY10MS;10MS

;-------------------------------------
;	N589 TYPE2 init
;-------------------------------------
	JSR	POR_MODULE_INIT

	JMP	POR_CHKTEST_END ;not enter test mode

;===============================================
E_POI_WAKEUP_BY_CAPSENSOR:
	JSR	S_RAM_RESTORE

	MR_WAKEUP_SET_IO

;-------------------------------------
;	N589 cap wakeup init
;-------------------------------------
	JSR	POR_MODULE_INIT
;	LDA	#2
;	STA	R_WAKEUP_FLAG
	JMP	MAIN_WAKEUP_N589
	
.ELSE ;!=(CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
;------for N588HJ,N567GHK,N588L
;type1 - POR, reset pin
POR_RESETPIN:

;	MR_POI_SET_IO
	JSR	S_IP_STABLE_WAIT
	MR_PWON_SET_IO
;	JSR	L_DELAY10MS;10MS

;-------------------------------------
;	POR init
;-------------------------------------
	JSR	POR_MODULE_INIT
	
.ENDIF ;(CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
	
POR_END:

POR_PCC:

;;===============================
;POR CHECK LVD
;;CHECK LVD before check test mode
;;reserve time for checking LVD / VD of external
;;===============================
.IF ( C_POR_LVD_EN .EQ. 1 )
PORVD_PRE:; check VD
	M_INT_ENABLE FXF15_INT_BIT
	JSR	CHK_LVD_START_SHORT;<50MS
	
	M_SET_CNT1 (1000000H-100*100/C_100GAP_FXF15)
PORVD:
	JSR WAITKEY
PORVD_CHKFG:
	M_CHK_VD	M0SF_VD
	M_CHK_CNT1 PORVD_CNT1
	
	JMP	PORVD
PORVD_CNT1:
	
	M_DET_N589VD_ST
	BEQ	PORVD_CNT1_S10
	
	JMP	M0SF_VD
	
PORVD_CNT1_S10:;PASSED
	M_SET_CNT1 CNT_STOP
	
;	JSR	BK0_VD_SET_PWM

.ENDIF ; C_POR_LVD_EN

POR_PCC_END:
	
;===============================
;CHECK TEST MODE
;if 'C_POR_LVD_EN == 0 ' enter 'POR_CHKTEST_PCC'
;===============================
POR_CHKTEST_PCC:
	JMP	HB_TEST0_CHK
HB_TEST0_CHK_RET:
	
POR_CHKTEST_PCC_END:
	

;========================================
POR_CHKTEST_END:


;not TEST MODE
;========================================
.IF ( C_POR_ENTER_STOP .EQ. 1 )
POR_ENTERSTOP_PCC:


POR_ENTERSTOP_PCC_END:
	
	JMP	L_ENTER_STOP
.ENDIF;( C_POR_ENTER_STOP .EQ. 1 )

PWON_CHK_MODE:
.IF ( C_TMGX_EN .EQ. 1 )
	MR_TMGX_SET
.ENDIF
	M_INT_ENABLE FXF15_INT_BIT

PWON_MODE_JMP:
	.IFDEF C_CHK_MODE_M_EN
	JSR	CHK_MODE_GET_MODE_NO
	JSR	GET_SYS_MODE_NO
	.ELSE
;	STZ	SYS_MODE_NO
	JSR	GET_SYS_MODE_NO1
	.ENDIF
;

	MR_AND_SYS_MODE_NO
	CMP	#0F0H
	BNE	PWON_CHK_MODE_S10
	
;EMPTY
	JMP	L_ENTER_STOP
PWON_CHK_MODE_S10:
	LSR	A
	LSR	A
	LSR	A
	TAX
	JMP	(PWON_MODE_TBL,X)
PWON_MODE_TBL:
	.IF ( C_SYS_MODE_MAX .GT. 0)
	DW	M0S_PWON
	.ENDIF
	.IF ( C_SYS_MODE_MAX .GT. 1)
	DW	M1S_PWON
	.ENDIF




;=========================================================================
; CODE1: WAKEUP
;=========================================================================
;==========================================================================
;--	WAKE UP POINT --
;for all IC body
;==========================================================================
MAIN_WAKEUP: ; wakeup from sleep:N588HJ,N567GKH,N588L,N566GKH

	MR_WAKEUP_SET_IO
;if some IO change to input from output ;->;DELAY1MS
;	JSR	BK0_DELAY1MS
	
MAIN_WAKEUP_N589: ; wakeup point from sleep:N589ABCD
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	EN_ULTRAIO_PIN 1
	EN_ULTRAIO_PIN 2
	EN_ULTRAIO_PIN 3
.ENDIF
MAIN_WAKEUP_PCC:
	JSR	CHK_LVD_START_SHORT; STORE LVD STATUS
MAIN_WAKEUP_PCC_END:

	M_INT_ENABLE FXF15_INT_BIT
.IF ( C_TMGX_EN .EQ. 1 )
	MR_TMGX_SET
.ENDIF

		MR_SET_AUTOCNT1
		
;===========================================================
;===========================================================
.IF ( C_WAKEUP_WKS0_EN .EQ. 1 )
;=======================================
; 	wakeup From key or mode key
;1,CHECK LVD=LOW : GOTO SLEEP
;2,check mode key firstly
;3,check other key wakeup
;=======================================
WKS0_PRE:
	
;	JSR	CHK_LVD_START_SHORT

WKS0:
	JSR	WAITKEY
WKS0_CHKFG:
;	M_CHK_VD	WKS0_VD
	M_CHK_SKEY0 WKS0_SKEY0
	M_CHK_AUTOCNT WKS0_AUTOCNT
	
	JMP	WKS0
;WKS0_VD:
	M_DET_N589VD_ST
	BEQ	WKS0_CHKFG
;
;	JMP	L_ENTER_STOP

WKS0_AUTOCNT: ;re-enter stop
;

	JSR	BK0_AUTOCNT_DET
	BNE	WKS0_AUTOCNT_S10

	JMP	L_ENTER_STOP

WKS0_AUTOCNT_S10:

	MR_SET_AUTOCNT1
	
	JMP	WKS0_CHKFG

	.IF ( C_WKS0_JMPTO_MODE .EQ. 1 )
WKS0_SKEY0:
	JSR	GET_SYS_MODE_NO
	MR_DET_SYS_MODE_NO
	LSR	A
	LSR	A
	LSR	A
	TAX
	JMP	(MKS0_SKEY0_TBL,X)
MKS0_SKEY0_TBL:
	DW	M0S0_SKEY0
	.ELSE
WKS0_SKEY0:
	
WKS0_CHKMODE:
	.ENDIF ; ( C_WKS0_JMPTO_MODE .EQ. 1 )
	
WKS0_ACTION: ;  key wakeup action
	
;==================================================
WKS0_ACTION_PCC:


WKS0_ACTION_PCC_END:
;==================================================

.ENDIF ;( C_WAKEUP_WKS0_EN .EQ. 1 )

;----------------------------------------------------------	
;check any keyX in MODE0_USER_PCC.asm,MODE1_USER_PCC.asm
;========================================
; share CHECK MODE When wakeup
;========================================
MAIN_WAKEUP2_GETMODE_JMP:
	.IFDEF C_CHK_MODE_M_EN
	JSR	CHK_MODE_GET_MODE_NO
	JSR	GET_SYS_MODE_NO
	.ELSE
;	STZ	SYS_MODE_NO
	JSR	GET_SYS_MODE_NO1
	.ENDIF
;-----------------------------------------

MAIN_WAKEUP2_MODE_JMP:
	MR_AND_SYS_MODE_NO
	LSR	A
	LSR	A
	LSR	A
	TAX
	JMP	(WK_MODE_TBL,X)
WK_MODE_TBL:
.IF ( C_SYS_MODE_MAX .GT. 0)
	DW	M0S_WAKEUP
.ENDIF
.IF ( C_SYS_MODE_MAX .GT. 1)
	DW	M1S_WAKEUP
.ENDIF



;================================================
;	NRL_MODE_SWITCH
;================================================
NRL_MODE_SWITCH:
;
	MR_CLR_PWOFF_FG
	
	M_SET_CNT0 CNT_STOP
;	M_SET_CNT1 CNT_STOP
	JSR	BK0_STOP_ALL

;-----------------------------------	
	MR_SET_AUTOCNT2
;	JSR	GET_SYS_MODE_NO

	JMP	MAIN_WAKEUP2_MODE_JMP

;=========================================================================
; CODE2
;=========================================================================


S_CHK_RAM_OV:
;count Ram Use.
;NuIDE V3.07.002
;C_UNUSED_RAM EQU C_AVAILABLE_RAMS-(R_USER_STACK_ST-R_USER_RAM_ST)
	LDA	#.HIGH.DP_ADDR
	BNE	S_CHK_RAM_OV ;direct page addr error

	LDA	#.HIGH.C_AVAILABLE_RAMS
	BNE	POR_RAM_OK; > 256:ok
	SEC
	LDA	#R_USER_STACK_ST
	SBC	#R_USER_RAM_ST
	STA	REG_EA

	LDA	#.LOW.C_AVAILABLE_RAMS
	CMP	REG_EA
	BCC	S_CHK_RAM_OV
	SEC
	SBC	REG_EA
	CMP	#C_RESERVE_BYTE_USER_STACK
	BCS	POR_RAM_OK
;

	BRA	S_CHK_RAM_OV ; reset
	
POR_RAM_OK:
	RTS

;========================================
; for N589
;=======================================
.if (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
S_N589_WAKEUP_N_RESET:
	LDA	!WAKEF
	TAX				; backup chip wakeup and reset source register 
	LDA	#0FFh
	STA	!WAKEF		; clear chip wakeup and reset source register 
	LDA	!RSTF
	TAY				; backup chip reset source register
	LDA	#0FFh
	STA	!RSTF		; clear chip reset source register
;-------------------------- 
; // check chip wakeup and reset source register //
	TXA
	BIT	#WAKEF_RST_SRC
	BNE	S_N589_WAKEUP
S_N589_RESET:
	BIT	#WAKEF_POR
	BNE	S_N589_RESET_POR
	BIT	#WAKEF_LVR
	BNE	S_N589_RESET_LVR
	BIT	#WAKEF_RESETB
	BNE	S_N589_RESET_RESETB	
	TYA
	BIT	#RSTF_WDT
	BNE	S_N589_RESET_WDT
	BIT	#C_BIT0
	BNE	S_N589_RESET_NO_WAKEUP_SRC
	LDX	#C_DEBUGGER_RERUN
	RTS	
S_N589_RESET_NO_WAKEUP_SRC:
	LDX	#C_RESET_NO_WAKEUP_SRC
	RTS
S_N589_RESET_POR:
	LDX	#C_RESET_POR
	RTS
S_N589_RESET_LVR:
	LDX	#C_RESET_LVR
	RTS	
S_N589_RESET_RESETB:
	LDX	#C_RESET_RESETB
	RTS
S_N589_RESET_WDT:
	LDX	#C_RESET_WDT
	RTS
S_N589_WAKEUP:
	BIT	#WAKEF_PORT
	BNE	S_N589_WAKEUP_PORT	
	BIT	#WAKEF_LRC
	BNE	S_N589_WAKEUP_LRC
	BIT	#WAKEF_IRWU
	BNE	S_N589_WAKEUP_IRWU
	BIT	#WAKEF_RESETB
	BNE	S_N589_WAKEUP_RESETB
	LDX	#C_DEBUGGER_RERUN
	RTS
S_N589_WAKEUP_PORT:
	LDX	#C_WAKEUP_PORT
	RTS
S_N589_WAKEUP_LRC:
	LDX	#C_WAKEUP_LRC
	RTS 
S_N589_WAKEUP_IRWU:
	LDX	#C_WAKEUP_IRWU
	RTS
S_N589_WAKEUP_RESETB:
	LDX	#C_WAKEUP_RESETB
	RTS
.ENDIF

;======================================
S_IP_STABLE_WAIT:; 30MS
POR_WAIT_CPU: 
	JSR	BK0_STORE_BPX

	JSR	L_DELAY10MS
	M_WDT_CLR
	JSR	L_DELAY10MS
	M_WDT_CLR
	JSR	L_DELAY10MS
	M_WDT_CLR
	
	
.IF ( C_COM_POR_EN .EQ. 0)
;CHECK AGAIN
.IF ( C_BP0_STATUS_EN .EQ. 1 )
	LDA	!BP0
	CMP	BP0_STATUS
	BNE	S_IP_STABLE_WAIT
.ENDIF
.IF ( C_BP1_STATUS_EN .EQ. 1 )
	LDA	!BP1
	CMP	BP1_STATUS
	BNE	S_IP_STABLE_WAIT
.ENDIF
.IF ( C_BP2_STATUS_EN .EQ. 1 )
	LDA	!BP2
	CMP	BP2_STATUS
	BNE	S_IP_STABLE_WAIT
.ENDIF
.ENDIF ; C_COM_POR_EN
	RTS


;===================================
POR_MODULE_INIT:
.IF	(C_MS1_ENABLE .EQ. 1)
;	EN_GLOBALVOL_VOL_MIDI1
.ENDIF

.IF	(C_SPCH1_ENABLE .EQ. 1)
	.IF ( Speech_Volume_Adjustment .EQ. 1 )
	EN_GLOBALVOL_VOL1
	.ENDIF
.ENDIF
	
.IF	(C_SPCH2_ENABLE .EQ. 1)
	.IF ( Speech_Volume_Adjustment .EQ. 1 )
	EN_GLOBALVOL_VOL2
	.ENDIF	
.ENDIF	
.IF (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
	.IF (VDDSPI_FROM_LDO33 .EQ. 1)
	LDO_ON
	JSR	L_DELAY10MS
	.ENDIF
.ENDIF

	JSR	F_BMA253_Init

;	JSR	F_UART_Port_Init

POR_MODULE_INIT2:

	.IF ( Speech_Volume_Adjustment .EQ. 1 )
	.IF (C_VOL_IDX_EN .EQ. 1)
	LDA	#C_DEFAULT_TPO_IDX|C_DEFAULT_VOL_IDX
	STA	VOL_TPO_IDX
	JSR	BK0_SET_VOL
	.ELSE
	SET_VOL1 128
	.ENDIF
	.ENDIF	

;	.IFDEF C_N589VD_EN
;	JSR	N589VD_INIT
;	.ENDIF
	JSR	INIT_WB_KEYCH
;========================================================
;========================================================
POR_MODULE_PCC:
	JSR	CHK_LVD_START_POI ;STORE LVD STATUS
	.IF ( C_RANDOM_GP_USED .EQ. 1)
	JSR	RANDOM_GP_BUF_INIT
	.ENDIF
;	JSR	F_UART_INIT ;INT
	
	MR_START_PWMX_TM
	JSR	SWPWM_INIT
POR_MODULE_PCC_END:
	RTS

