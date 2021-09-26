
;==========================================
;Module version: V01I;2018/11/12 ÐÇÆÚÒ» ÏÂÎç 1:45:50
;==========================================

C_DEBUGGER_RERUN		EQU	000h
C_RESET_NO_WAKEUP_SRC	EQU	008h
C_RESET_POR				EQU	006h
C_RESET_LVR				EQU	004h
C_RESET_RESETB			EQU	002h
C_RESET_WDT				EQU	00Ah
C_WAKEUP_PORT			EQU	00Ch
C_WAKEUP_RESETB			EQU	012h
C_WAKEUP_IRWU			EQU	010h
C_WAKEUP_LRC			EQU	00Eh


C_POR_ENTER_STOP EQU	0

;================================
C_WAKEUP_WKS0_EN	EQU	0 ; for LVD/MODE SWITCH
.IF (C_WAKEUP_WKS0_EN .EQ. 1)
C_WKS0_JMPTO_MODE	EQU	0
	;0:WAKEUP KEY TO MODE START
	;1:JMP INTO MODE
.ENDIF
;with LVD detect
C_POR_LVD_EN	EQU	0 ; BEFORE TESTMODE; for external LVD detect
;================================

C_COM_POR_EN	EQU	0; avoid the communicate in POR,not check the IO stable
