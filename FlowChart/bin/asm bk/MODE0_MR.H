;=========================================================================
; macro
;=========================================================================

M_CHK_EQU_WP1_PATTEND_EVT MACRO L1_EQU_NEXT_INT,L_EQU_WP1_PATTEND
	
	LDA	#C_EQU_EVT_WP1_PATTEND_BIT
	BIT	EQU_EVT_EN_FG
	BNE	3
	JMP	L_EQU_WP1_PATTEND ;no evt
	TSB	EQU_EVT_OV_FG
;
	JSR	L_CHK_EQU_EVT
	BEQ	3
	JMP	L1_EQU_NEXT_INT ;PATT NEXT STEP
;invalid
	ENDM

M_CHK_EQU_EVO1_EVT MACRO LABEL_INT,LABEL_RET
	
	LDA	#C_EQU_EVT_EVO1_BIT
	BIT	EQU_EVT_EN_FG
	BNE	3
	JMP	LABEL_RET ;no evt
	TSB	EQU_EVT_OV_FG
;
	JSR	L_EQU_CHK_EVT
	BEQ	3
	JMP	LABEL_INT ;PATT NEXT STEP
;invalid
	ENDM

M_CHK_EQU_CNT1_EVT MACRO LABEL_INT,LABEL_RET
	
	LDA	#C_EQU_EVT_CNT1_BIT
	BIT	EQU_EVT_EN_FG
	BNE	3
	JMP	LABEL_RET ;no evt
	TSB	EQU_EVT_OV_FG
;
	JSR	L_EQU_CHK_EVT
	BEQ	3
	JMP	LABEL_INT ;PATT NEXT STEP
;invalid
	ENDM


MR_SKEY1_F_JMP MACRO LABLE_JMP
	
	MR_DET_SKEY1_ST_PULLTAB
	BNE	3
	JMP	LABLE_JMP;CLOSED
;open
	ENDM
	
;=================================================
M_EQU_NEXT_JMP MACRO	EQU_NRL_NEXT_JMP,EQU_EVT_NEXT_JMP

	MR_DET_EQU_EVT_NEXT
	BNE	3
	JMP	EQU_NRL_NEXT_JMP
;EVT to next EQU STEP
	LDA	#C_EQU_EVT_EN1_BIT
	TSB	EQU_EVT_EN_FG	;enable int; wait for EVT Trigger
;check the current EVT status

	;.IF (  C_EQU0_EVT_EN  .EQ. 1)
	JSR	L_CHK_EQU_EVT ; check 'C_EQU_EVT_EN1_BIT'+ EQU EVT BIT
	BEQ	3
	JMP	EQU_EVT_NEXT_JMP; EVT TRIGGER
;EVT TO NEXT:NOT REACH
	;.ENDIF;(  C_EQU0_EVT_EN  .EQ. 1)
	ENDM
;=================================================


;----------------------------------------------------------------
;---------------------------------
;	for waitkey loop check
;---------------------------------
M_CHK_EQU_WIPER MACRO L_CHKFG,L_EQUEND_JMP
	JSR	L_CHK_EQU_WIPER
	CMP	#1
	BNE	3
	JMP	L_CHKFG
	CMP	#2
	BNE	3
	JMP	L_EQUEND_JMP
;
	ENDM
	
M_CHK_KEYCH3_JUDGE MACRO L_NECK_L05S,L_NECK_L10S
	JSR	S_CHK_KEYCH3_JUDGE
	CMP	#1
	BNE	3
	JMP	L_NECK_L05S
	CMP	#2
	BNE	3
	JMP	L_NECK_L10S
;0:skip
	ENDM
M_CHK_KEYCH0_JUDGE MACRO L_SHORT,L_DB,L_LONG
	JSR	S_CHK_KEYCH0_JUDGE
	CMP	#1
	BNE	3
	JMP	L_SHORT
	CMP	#2
	BNE	3
	JMP	L_DB
	CMP	#3
	BNE	3
	JMP	L_LONG
;0:skip
	ENDM
