


;=========================================================================
; macro
;=========================================================================

	
M_DET_SKEY0_ST MACRO
	LDA	#B_SKEY0
	BIT	<R_SKEY0_STATUS
	ENDM
M_DET_SKEY0 MACRO
	LDA	SR_SKEY0_PORT
	BIT	#B_SKEY0
	ENDM


;=========================================================================
; code
;=========================================================================

;----------------------------------------
	
BK0_CHKSKEY:
	
	
;=================================
;=================================
; check single / io direct key
;=================================
;check SKEY0
.IF(C_SKEY0_EN .EQ. 1)
CHKSKEY0: 
	.IF(C_SKEY0DUTY_EN .EQ. 1)
	JMP	CHKSKEY0DUTY
CHKSKEY0DUTY_RET:
	JMP	CHKSKEY0_QUIT
	.ENDIF
;---------------------------------- 20 intrutions*3 cycles
	LDA	#B_SKEY0
	BIT	!SR_SKEY0_PORT
	BNE	CHKSKEY0_HIGH
;fall
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY0_DEB
	BEQ	CHKSKEY0_LOW_S01
	STZ	R_SKEY0_DEB
CHKSKEY0_LOW_S01:
	LDA	#B_SKEY0
	BIT	<R_SKEY0_STATUS
	BEQ	CHKSKEY0_QUIT
	LDA	<R_SKEY0_DEB
	BEQ	CHKSKEY0_LOW_S10
;	BIT	#C_BIT7
;	BNE	CHKSKEY0_LOW_S10 ;RESTART
	DEC	<R_SKEY0_DEB
	LDA	<R_SKEY0_DEB
	BNE	CHKSKEY0_QUIT_J1
;reach
	LDA	#B_SKEY0
	TRB	<R_SKEY0_STATUS
	JMP	SKEY0_F
	
CHKSKEY0_LOW_S10:
	LDA	#C_SKEY0_DEB_F
	STA	R_SKEY0_DEB
CHKSKEY0_QUIT_J1:
	JMP	CHKSKEY0_QUIT
	
CHKSKEY0_HIGH:;rise
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY0_DEB
	BNE	CHKSKEY0_HIGH_S01
	LDA	#C_BIT7
	STA	R_SKEY0_DEB
CHKSKEY0_HIGH_S01:
	LDA	#B_SKEY0
	BIT	<R_SKEY0_STATUS
	BNE	CHKSKEY0_QUIT
;
	LDA	<R_SKEY0_DEB
;	BIT	#C_BIT7
;	BEQ	CHKSKEY0_HIGH_S10 ;RESTART
	AND	#7FH
	BEQ	CHKSKEY0_HIGH_S10
	DEC	<R_SKEY0_DEB
	LDA	<R_SKEY0_DEB
	AND	#7FH
	BNE	CHKSKEY0_QUIT
;reach
	LDA	#B_SKEY0
	TSB	<R_SKEY0_STATUS
	JMP	SKEY0_R
	
CHKSKEY0_HIGH_S10:
	LDA	#C_SKEY0_DEB_R+C_BIT7
	STA	R_SKEY0_DEB
	JMP	CHKSKEY0_QUIT
	
SKEY0_F_RET:
SKEY0_R_RET:
CHKSKEY0_QUIT:

.ENDIF
.IF(C_SKEY1_EN .EQ. 1)
CHKSKEY1: 
	.IF(C_SKEY1DUTY_EN .EQ. 1)
	JMP	CHKSKEY1DUTY
CHKSKEY1DUTY_RET:
	JMP	CHKSKEY1_QUIT
	.ENDIF
;
	LDA	#B_SKEY1
	BIT	!SR_SKEY1_PORT
	BNE	CHKSKEY1_HIGH
;fall
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY1_DEB
	BEQ	CHKSKEY1_LOW_S01
	STZ	R_SKEY1_DEB
CHKSKEY1_LOW_S01:
	LDA	#B_SKEY1
	BIT	<R_SKEY1_STATUS
	BEQ	CHKSKEY1_QUIT
	LDA	<R_SKEY1_DEB
	BEQ	CHKSKEY1_LOW_S10
;	BIT	#C_BIT7
;	BNE	CHKSKEY1_LOW_S10 ;RESTART
	DEC	<R_SKEY1_DEB
	LDA	<R_SKEY1_DEB
	BNE	CHKSKEY1_QUIT_J1
;reach
	LDA	#B_SKEY1
	TRB	<R_SKEY1_STATUS
	JMP	SKEY1_F
	
CHKSKEY1_LOW_S10:
	LDA	#C_SKEY1_DEB_F
	STA	R_SKEY1_DEB
CHKSKEY1_QUIT_J1:
	JMP	CHKSKEY1_QUIT
	
CHKSKEY1_HIGH:;rise
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY1_DEB
	BNE	CHKSKEY1_HIGH_S01
	LDA	#C_BIT7
	STA	R_SKEY1_DEB
CHKSKEY1_HIGH_S01:
	LDA	#B_SKEY1
	BIT	<R_SKEY1_STATUS
	BNE	CHKSKEY1_QUIT
;
	LDA	<R_SKEY1_DEB
;	BIT	#C_BIT7
;	BEQ	CHKSKEY1_HIGH_S10 ;RESTART
	AND	#7FH
	BEQ	CHKSKEY1_HIGH_S10
	DEC	<R_SKEY1_DEB
	LDA	<R_SKEY1_DEB
	AND	#7FH
	BNE	CHKSKEY1_QUIT
;reach
	LDA	#B_SKEY1
	TSB	<R_SKEY1_STATUS
	JMP	SKEY1_R
	
CHKSKEY1_HIGH_S10:
	LDA	#C_SKEY1_DEB_R+C_BIT7
	STA	R_SKEY1_DEB
	JMP	CHKSKEY1_QUIT
	
SKEY1_F_RET:
SKEY1_R_RET:
CHKSKEY1_QUIT:

.ENDIF
.IF(C_SKEY2_EN .EQ. 1)
CHKSKEY2: 
	.IF(C_SKEY2DUTY_EN .EQ. 1)
	JMP	CHKSKEY2DUTY
CHKSKEY2DUTY_RET:
	JMP	CHKSKEY2_QUIT
	.ENDIF
;
	LDA	#B_SKEY2
	BIT	!SR_SKEY2_PORT
	BNE	CHKSKEY2_HIGH
;fall
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY2_DEB
	BEQ	CHKSKEY2_LOW_S01
	STZ	R_SKEY2_DEB
CHKSKEY2_LOW_S01:
	LDA	#B_SKEY2
	BIT	<R_SKEY2_STATUS
	BEQ	CHKSKEY2_QUIT
	LDA	<R_SKEY2_DEB
	BEQ	CHKSKEY2_LOW_S10
;	BIT	#C_BIT7
;	BNE	CHKSKEY2_LOW_S10 ;RESTART
	DEC	<R_SKEY2_DEB
	LDA	<R_SKEY2_DEB
	BNE	CHKSKEY2_QUIT_J1
;reach
	LDA	#B_SKEY2
	TRB	<R_SKEY2_STATUS
	JMP	SKEY2_F
	
CHKSKEY2_LOW_S10:
	LDA	#C_SKEY2_DEB_F
	STA	R_SKEY2_DEB
CHKSKEY2_QUIT_J1:
	JMP	CHKSKEY2_QUIT
	
CHKSKEY2_HIGH:;rise
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY2_DEB
	BNE	CHKSKEY2_HIGH_S01
	LDA	#C_BIT7
	STA	R_SKEY2_DEB
CHKSKEY2_HIGH_S01:
	LDA	#B_SKEY2
	BIT	<R_SKEY2_STATUS
	BNE	CHKSKEY2_QUIT
;
	LDA	<R_SKEY2_DEB
;	BIT	#C_BIT7
;	BEQ	CHKSKEY2_HIGH_S10 ;RESTART
	AND	#7FH
	BEQ	CHKSKEY2_HIGH_S10
	DEC	<R_SKEY2_DEB
	LDA	<R_SKEY2_DEB
	AND	#7FH
	BNE	CHKSKEY2_QUIT
;reach
	LDA	#B_SKEY2
	TSB	<R_SKEY2_STATUS
	JMP	SKEY2_R
	
CHKSKEY2_HIGH_S10:
	LDA	#C_SKEY2_DEB_R+C_BIT7
	STA	R_SKEY2_DEB
	JMP	CHKSKEY2_QUIT
	
SKEY2_F_RET:
SKEY2_R_RET:
CHKSKEY2_QUIT:

.ENDIF
.IF(C_SKEY3_EN .EQ. 1)
CHKSKEY3: 
	.IF(C_SKEY3DUTY_EN .EQ. 1)
	JMP	CHKSKEY3DUTY
CHKSKEY3DUTY_RET:
	JMP	CHKSKEY3_QUIT
	.ENDIF
;
	LDA	#B_SKEY3
	BIT	!SR_SKEY3_PORT
	BNE	CHKSKEY3_HIGH
;fall
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY3_DEB
	BEQ	CHKSKEY3_LOW_S01
	STZ	R_SKEY3_DEB
CHKSKEY3_LOW_S01:
	LDA	#B_SKEY3
	BIT	<R_SKEY3_STATUS
	BEQ	CHKSKEY3_QUIT
	LDA	<R_SKEY3_DEB
	BEQ	CHKSKEY3_LOW_S10
;	BIT	#C_BIT7
;	BNE	CHKSKEY3_LOW_S10 ;RESTART
	DEC	<R_SKEY3_DEB
	LDA	<R_SKEY3_DEB
	BNE	CHKSKEY3_QUIT_J1
;reach
	LDA	#B_SKEY3
	TRB	<R_SKEY3_STATUS
	JMP	SKEY3_F
	
CHKSKEY3_LOW_S10:
	LDA	#C_SKEY3_DEB_F
	STA	R_SKEY3_DEB
CHKSKEY3_QUIT_J1:
	JMP	CHKSKEY3_QUIT
	
CHKSKEY3_HIGH:;rise
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY3_DEB
	BNE	CHKSKEY3_HIGH_S01
	LDA	#C_BIT7
	STA	R_SKEY3_DEB
CHKSKEY3_HIGH_S01:
	LDA	#B_SKEY3
	BIT	<R_SKEY3_STATUS
	BNE	CHKSKEY3_QUIT
;
	LDA	<R_SKEY3_DEB
;	BIT	#C_BIT7
;	BEQ	CHKSKEY3_HIGH_S10 ;RESTART
	AND	#7FH
	BEQ	CHKSKEY3_HIGH_S10
	DEC	<R_SKEY3_DEB
	LDA	<R_SKEY3_DEB
	AND	#7FH
	BNE	CHKSKEY3_QUIT
;reach
	LDA	#B_SKEY3
	TSB	<R_SKEY3_STATUS
	JMP	SKEY3_R
	
CHKSKEY3_HIGH_S10:
	LDA	#C_SKEY3_DEB_R+C_BIT7
	STA	R_SKEY3_DEB
	JMP	CHKSKEY3_QUIT
	
SKEY3_F_RET:
SKEY3_R_RET:
CHKSKEY3_QUIT:

.ENDIF
.IF(C_SKEY4_EN .EQ. 1)
CHKSKEY4: 
	.IF(C_SKEY4DUTY_EN .EQ. 1)
	JMP	CHKSKEY4DUTY
CHKSKEY4DUTY_RET:
	JMP	CHKSKEY4_QUIT
	.ENDIF
;
	LDA	#B_SKEY4
	BIT	!SR_SKEY4_PORT
	BNE	CHKSKEY4_HIGH
;fall
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY4_DEB
	BEQ	CHKSKEY4_LOW_S01
	STZ	R_SKEY4_DEB
CHKSKEY4_LOW_S01:
	LDA	#B_SKEY4
	BIT	<R_SKEY4_STATUS
	BEQ	CHKSKEY4_QUIT
	LDA	<R_SKEY4_DEB
	BEQ	CHKSKEY4_LOW_S10
;	BIT	#C_BIT7
;	BNE	CHKSKEY4_LOW_S10 ;RESTART
	DEC	<R_SKEY4_DEB
	LDA	<R_SKEY4_DEB
	BNE	CHKSKEY4_QUIT_J1
;reach
	LDA	#B_SKEY4
	TRB	<R_SKEY4_STATUS
	JMP	SKEY4_F
	
CHKSKEY4_LOW_S10:
	LDA	#C_SKEY4_DEB_F
	STA	R_SKEY4_DEB
CHKSKEY4_QUIT_J1:
	JMP	CHKSKEY4_QUIT
	
CHKSKEY4_HIGH:;rise
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY4_DEB
	BNE	CHKSKEY4_HIGH_S01
	LDA	#C_BIT7
	STA	R_SKEY4_DEB
CHKSKEY4_HIGH_S01:
	LDA	#B_SKEY4
	BIT	<R_SKEY4_STATUS
	BNE	CHKSKEY4_QUIT
;
	LDA	<R_SKEY4_DEB
;	BIT	#C_BIT7
;	BEQ	CHKSKEY4_HIGH_S10 ;RESTART
	AND	#7FH
	BEQ	CHKSKEY4_HIGH_S10
	DEC	<R_SKEY4_DEB
	LDA	<R_SKEY4_DEB
	AND	#7FH
	BNE	CHKSKEY4_QUIT
;reach
	LDA	#B_SKEY4
	TSB	<R_SKEY4_STATUS
	JMP	SKEY4_R
	
CHKSKEY4_HIGH_S10:
	LDA	#C_SKEY4_DEB_R+C_BIT7
	STA	R_SKEY4_DEB
	JMP	CHKSKEY4_QUIT
	
SKEY4_F_RET:
SKEY4_R_RET:
CHKSKEY4_QUIT:

.ENDIF
.IF(C_SKEY5_EN .EQ. 1)
CHKSKEY5: 
	.IF(C_SKEY5DUTY_EN .EQ. 1)
	JMP	CHKSKEY5DUTY
CHKSKEY5DUTY_RET:
	JMP	CHKSKEY5_QUIT
	.ENDIF
;
	LDA	#B_SKEY5
	BIT	!SR_SKEY5_PORT
	BNE	CHKSKEY5_HIGH
;fall
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY5_DEB
	BEQ	CHKSKEY5_LOW_S01
	STZ	R_SKEY5_DEB
CHKSKEY5_LOW_S01:
	LDA	#B_SKEY5
	BIT	<R_SKEY5_STATUS
	BEQ	CHKSKEY5_QUIT
	LDA	<R_SKEY5_DEB
	BEQ	CHKSKEY5_LOW_S10
;	BIT	#C_BIT7
;	BNE	CHKSKEY5_LOW_S10 ;RESTART
	DEC	<R_SKEY5_DEB
	LDA	<R_SKEY5_DEB
	BNE	CHKSKEY5_QUIT_J1
;reach
	LDA	#B_SKEY5
	TRB	<R_SKEY5_STATUS
	JMP	SKEY5_F
	
CHKSKEY5_LOW_S10:
	LDA	#C_SKEY5_DEB_F
	STA	R_SKEY5_DEB
CHKSKEY5_QUIT_J1:
	JMP	CHKSKEY5_QUIT
	
CHKSKEY5_HIGH:;rise
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY5_DEB
	BNE	CHKSKEY5_HIGH_S01
	LDA	#C_BIT7
	STA	R_SKEY5_DEB
CHKSKEY5_HIGH_S01:
	LDA	#B_SKEY5
	BIT	<R_SKEY5_STATUS
	BNE	CHKSKEY5_QUIT
;
	LDA	<R_SKEY5_DEB
;	BIT	#C_BIT7
;	BEQ	CHKSKEY5_HIGH_S10 ;RESTART
	AND	#7FH
	BEQ	CHKSKEY5_HIGH_S10
	DEC	<R_SKEY5_DEB
	LDA	<R_SKEY5_DEB
	AND	#7FH
	BNE	CHKSKEY5_QUIT
;reach
	LDA	#B_SKEY5
	TSB	<R_SKEY5_STATUS
	JMP	SKEY5_R
	
CHKSKEY5_HIGH_S10:
	LDA	#C_SKEY5_DEB_R+C_BIT7
	STA	R_SKEY5_DEB
	JMP	CHKSKEY5_QUIT
	
SKEY5_F_RET:
SKEY5_R_RET:
CHKSKEY5_QUIT:

.ENDIF
.IF(C_SKEY6_EN .EQ. 1)
CHKSKEY6: 
	.IF(C_SKEY6DUTY_EN .EQ. 1)
	JMP	CHKSKEY6DUTY
CHKSKEY6DUTY_RET:
	JMP	CHKSKEY6_QUIT
	.ENDIF
;
	LDA	#B_SKEY6
	BIT	!SR_SKEY6_PORT
	BNE	CHKSKEY6_HIGH
;fall
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY6_DEB
	BEQ	CHKSKEY6_LOW_S01
	STZ	R_SKEY6_DEB
CHKSKEY6_LOW_S01:
	LDA	#B_SKEY6
	BIT	<R_SKEY6_STATUS
	BEQ	CHKSKEY6_QUIT
	LDA	<R_SKEY6_DEB
	BEQ	CHKSKEY6_LOW_S10
;	BIT	#C_BIT7
;	BNE	CHKSKEY6_LOW_S10 ;RESTART
	DEC	<R_SKEY6_DEB
	LDA	<R_SKEY6_DEB
	BNE	CHKSKEY6_QUIT_J1
;reach
	LDA	#B_SKEY6
	TRB	<R_SKEY6_STATUS
	JMP	SKEY6_F
	
CHKSKEY6_LOW_S10:
	LDA	#C_SKEY6_DEB_F
	STA	R_SKEY6_DEB
CHKSKEY6_QUIT_J1:
	JMP	CHKSKEY6_QUIT
	
CHKSKEY6_HIGH:;rise
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY6_DEB
	BNE	CHKSKEY6_HIGH_S01
	LDA	#C_BIT7
	STA	R_SKEY6_DEB
CHKSKEY6_HIGH_S01:
	LDA	#B_SKEY6
	BIT	<R_SKEY6_STATUS
	BNE	CHKSKEY6_QUIT
;
	LDA	<R_SKEY6_DEB
;	BIT	#C_BIT7
;	BEQ	CHKSKEY6_HIGH_S10 ;RESTART
	AND	#7FH
	BEQ	CHKSKEY6_HIGH_S10
	DEC	<R_SKEY6_DEB
	LDA	<R_SKEY6_DEB
	AND	#7FH
	BNE	CHKSKEY6_QUIT
;reach
	LDA	#B_SKEY6
	TSB	<R_SKEY6_STATUS
	JMP	SKEY6_R
	
CHKSKEY6_HIGH_S10:
	LDA	#C_SKEY6_DEB_R+C_BIT7
	STA	R_SKEY6_DEB
	JMP	CHKSKEY6_QUIT
	
SKEY6_F_RET:
SKEY6_R_RET:
CHKSKEY6_QUIT:

.ENDIF
.IF(C_SKEY7_EN .EQ. 1)
CHKSKEY7: 
	.IF(C_SKEY7DUTY_EN .EQ. 1)
	JMP	CHKSKEY7DUTY
CHKSKEY7DUTY_RET:
	JMP	CHKSKEY7_QUIT
	.ENDIF
;
	LDA	#B_SKEY7
	BIT	!SR_SKEY7_PORT
	BNE	CHKSKEY7_HIGH
;fall
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY7_DEB
	BEQ	CHKSKEY7_LOW_S01
	STZ	R_SKEY7_DEB
CHKSKEY7_LOW_S01:
	LDA	#B_SKEY7
	BIT	<R_SKEY7_STATUS
	BEQ	CHKSKEY7_QUIT
	LDA	<R_SKEY7_DEB
	BEQ	CHKSKEY7_LOW_S10
;	BIT	#C_BIT7
;	BNE	CHKSKEY7_LOW_S10 ;RESTART
	DEC	<R_SKEY7_DEB
	LDA	<R_SKEY7_DEB
	BNE	CHKSKEY7_QUIT_J1
;reach
	LDA	#B_SKEY7
	TRB	<R_SKEY7_STATUS
	JMP	SKEY7_F
	
CHKSKEY7_LOW_S10:
	LDA	#C_SKEY7_DEB_F
	STA	R_SKEY7_DEB
CHKSKEY7_QUIT_J1:
	JMP	CHKSKEY7_QUIT
	
CHKSKEY7_HIGH:;rise
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY7_DEB
	BNE	CHKSKEY7_HIGH_S01
	LDA	#C_BIT7
	STA	R_SKEY7_DEB
CHKSKEY7_HIGH_S01:
	LDA	#B_SKEY7
	BIT	<R_SKEY7_STATUS
	BNE	CHKSKEY7_QUIT
;
	LDA	<R_SKEY7_DEB
;	BIT	#C_BIT7
;	BEQ	CHKSKEY7_HIGH_S10 ;RESTART
	AND	#7FH
	BEQ	CHKSKEY7_HIGH_S10
	DEC	<R_SKEY7_DEB
	LDA	<R_SKEY7_DEB
	AND	#7FH
	BNE	CHKSKEY7_QUIT
;reach
	LDA	#B_SKEY7
	TSB	<R_SKEY7_STATUS
	JMP	SKEY7_R
	
CHKSKEY7_HIGH_S10:
	LDA	#C_SKEY7_DEB_R+C_BIT7
	STA	R_SKEY7_DEB
	JMP	CHKSKEY7_QUIT
	
SKEY7_F_RET:
SKEY7_R_RET:
CHKSKEY7_QUIT:

.ENDIF
.IF(C_SKEY8_EN .EQ. 1)
CHKSKEY8: 
	.IF(C_SKEY8DUTY_EN .EQ. 1)
	JMP	CHKSKEY8DUTY
CHKSKEY8DUTY_RET:
	JMP	CHKSKEY8_QUIT
	.ENDIF
;
	LDA	#B_SKEY8
	BIT	!SR_SKEY8_PORT
	BNE	CHKSKEY8_HIGH
;fall
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY8_DEB
	BEQ	CHKSKEY8_LOW_S01
	STZ	R_SKEY8_DEB
CHKSKEY8_LOW_S01:
	LDA	#B_SKEY8
	BIT	<R_SKEY8_STATUS
	BEQ	CHKSKEY8_QUIT
	LDA	<R_SKEY8_DEB
	BEQ	CHKSKEY8_LOW_S10
;	BIT	#C_BIT7
;	BNE	CHKSKEY8_LOW_S10 ;RESTART
	DEC	<R_SKEY8_DEB
	LDA	<R_SKEY8_DEB
	BNE	CHKSKEY8_QUIT_J1
;reach
	LDA	#B_SKEY8
	TRB	<R_SKEY8_STATUS
	JMP	SKEY8_F
	
CHKSKEY8_LOW_S10:
	LDA	#C_SKEY8_DEB_F
	STA	R_SKEY8_DEB
CHKSKEY8_QUIT_J1:
	JMP	CHKSKEY8_QUIT
	
CHKSKEY8_HIGH:;rise
;clear accerary
	LDA	#C_BIT7
	BIT	<R_SKEY8_DEB
	BNE	CHKSKEY8_HIGH_S01
	LDA	#C_BIT7
	STA	R_SKEY8_DEB
CHKSKEY8_HIGH_S01:
	LDA	#B_SKEY8
	BIT	<R_SKEY8_STATUS
	BNE	CHKSKEY8_QUIT
;
	LDA	<R_SKEY8_DEB
;	BIT	#C_BIT7
;	BEQ	CHKSKEY8_HIGH_S10 ;RESTART
	AND	#7FH
	BEQ	CHKSKEY8_HIGH_S10
	DEC	<R_SKEY8_DEB
	LDA	<R_SKEY8_DEB
	AND	#7FH
	BNE	CHKSKEY8_QUIT
;reach
	LDA	#B_SKEY8
	TSB	<R_SKEY8_STATUS
	JMP	SKEY8_R
	
CHKSKEY8_HIGH_S10:
	LDA	#C_SKEY8_DEB_R+C_BIT7
	STA	R_SKEY8_DEB
	JMP	CHKSKEY8_QUIT
	
SKEY8_F_RET:
SKEY8_R_RET:
CHKSKEY8_QUIT:

.ENDIF

	RTS
;=========================================================================
; code1
;=========================================================================
;==============================
;=================================
;=================================


;
;===============================
RESET_SKEY0_DEB:
	LDA	#B_SKEY0
	BIT	R_SKEY0_STATUS
	BNE	RESET_SKEY0_DEB_H
	STZ	R_SKEY0_DEB
	RTS
RESET_SKEY0_DEB_H:
	LDA	#C_BIT7
	STA	R_SKEY0_DEB
	RTS


