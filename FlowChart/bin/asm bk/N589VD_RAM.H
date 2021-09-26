




;===================================
;	 take 3 Ram
;===================================

CHK_LVD_DEB_R DS	1
CHK_LVD_DEB_R_BUF DS	1

LVD_ST_BIT EQU 	C_BIT5
LVD_ST_RAM EQU	USER_FLAG20
;save LVD status
;LVD_EVT_REG EQU	DP_USER_FLAG_B
;set LVD event flag
;LVD_EVT_BIT EQU	C_BIT4

SR_VD_REG	EQU	LVDC
;.7:read only
	
C_LVD_DEBUG_IO_EN EQU 0

MR_DEBUG_LVD_W_PIN MACRO
;assume BP0R.1
	LDA	!BP0R
	BIT	#C_BIT0
	
	ENDM

	
	
	
