

;=========================================================================
; CODE0
;=========================================================================
;note:
;	JMP	PWOFF_LOOP_WAITSP
;	MR_SET_AUTOCNT1_1B ; --------------- not directly to enter sleep 

;==================================================

;=========================================================================
; CONST
;=========================================================================
C_M0_MODE EQU	00H
C_M0S0_MODE EQU	00H
C_M0S1_MODE EQU	01H
C_M0S2_MODE EQU	02H
C_M0S3_MODE EQU	03H


;=========================================
;		M0S
;=========================================


;=========================================
M0S_WAKEUP: ;WAKEUP ENTER

	BRA	M0S_PWON
	
	M_SET_CNT0 CNT_STOP


	JMP	M0S0_PRE2
M0S_PWON: ; POWER ON ENTER

	LDA	RANDOM0
	AND	#C_BIT0
	STA	R_HITTYPE
	
	MR_PLAY_SPCH1_GROUP_NOP CS_ULTIMATE


;===================================
M0S0_PRE2:
	
	M_SET_MODE_NO C_M0S0_MODE
	
	JSR	CHK_LVD_START_LONG
	
	MR_STOP_AUTOCNT
	
	STZ	R_ACCEHIT_CNT

	LDA	#0FFH
	STA	R_SWPWM_PATT
	
M0S0_PRE_GETTYPE:

	LDA	#C_FALSE
	STA	R_ACCELHIT_FLAG
	
M0S0_PRE_RESTART: ;INSERT
	MR_RESET_IDLE0
	
	MR_START_SWPWM_PATT 3 ;LOOP

;
;--------------------------------------------
M0S0:
	JSR WAITKEY
M0S0_CHKFG:
	M_CHK_SKEY0 M0S0_SKEY0
	M_CHK_KEYCH0 M0S0_KEYCH0;trig
	M_CHK_SPCH1 M0S0_SPCH1
	M_CHK_CNT0 M0S0_CNT0_IDLE
;	M_CHK_AUTOCNT M0S0_AUTOCNT
	M_CHK_SWPWM_PATT M0S0_SWPWM_PATT
	M_CHK_VD M0S0_VD
	JMP	M0S0
	
M0S0_SPCH1:

	LDA	SOUND_NO
	CMP	#CS_ULTIMATE
	BEQ	M0S0_SPCH1_S100
	CMP	#CS_TURRET3
	BEQ	M0S0_SPCH1_S200

	MR_RESET_IDLE0; CNT0

M0S0_SPCH1_ENDCHECK:
;check flag/cnt
;
	JMP	M0S0_PRE_RESTART

M0S0_SPCH1_S000:
;
	MR_RESET_IDLE0; CNT0

	JMP	M0S0_SPCH1_ENDCHECK
M0S0_SPCH1_IDLE_TIME:
	MR_RESET_IDLE0_TIME
	
	JMP	M0S0_SPCH1_ENDCHECK
M0S0_SPCH1_S100:

	JMP	M0S0_PRE_RESTART
M0S0_SPCH1_S200:
	MR_START_SWPWM_PATT 4
	MR_PLAY_SPCH1_GROUP_NOP CS_ULTIMATE
	JMP	M0S0_PRE_RESTART

	
M0S0_AUTOCNT:

M0S0_AUTOCNT_PCC:
M0S0_AUTOCNT_PCC_END:
	JSR	BK0_AUTOCNT_DET
	BNE	M0S0_AUTOCNT_S10

	JMP	L_ENTER_STOP

M0S0_AUTOCNT_S10:

	MR_SET_AUTOCNT1
	
	JMP	M0S0_CHKFG
	
M0S0_SWPWM_PATT:
	;return to default patt 
	
	JMP	M0S0_PRE_RESTART

	
M0S0_SKEY0:;debug
;g-sensor detect
;	JSR	F_UART_Send_Data

	JMP	M0S0_CHKFG
	
M0S0_KEYCH0:
;trig
	JSR	L_STOP_IDLE;CNT0
	
;	LDA	#C_TRUE
;	STA	R_ACCELHIT_FLAG	;
	
	LDA	R_ACCEHIT_CNT
	ASL	A
	TAX
	INC	R_ACCEHIT_CNT
	JMP	(M0S0_KEYCH0_TBL,X)
M0S0_KEYCH0_TBL:
	DW	M0S0_KEYCH0_0
	DW	M0S0_KEYCH0_1
	DW	M0S0_KEYCH0_2
	DW	M0S0_KEYCH0_3
	DW	M0S0_KEYCH0_4
	DW	M0S0_KEYCH0_5
	DW	M0S0_KEYCH0_6
	DW	M0S0_KEYCH0_7
	DW	M0S0_KEYCH0_8
;
M0S0_KEYCH0_0:
	MR_PLAY_SPCH1_GROUP_NOP CS_FLESH1
	BRA	M0S0_KEYCH0_S100

M0S0_KEYCH0_1:
	MR_PLAY_SPCH1_GROUP_NOP CS_FLESH2
	BRA	M0S0_KEYCH0_S100

M0S0_KEYCH0_2:
	MR_PLAY_SPCH1_GROUP_NOP CS_FLESH3
	BRA	M0S0_KEYCH0_S100

M0S0_KEYCH0_3:
	MR_PLAY_SPCH1_GROUP_NOP CS_ARMOR1
	BRA	M0S0_KEYCH0_S100

M0S0_KEYCH0_4:
	MR_PLAY_SPCH1_GROUP_NOP CS_ARMOR2
	BRA	M0S0_KEYCH0_S100

M0S0_KEYCH0_5:
	MR_PLAY_SPCH1_GROUP_NOP CS_ARMOR3
	BRA	M0S0_KEYCH0_S100

M0S0_KEYCH0_6:
	MR_PLAY_SPCH1_GROUP_NOP CS_TURRET1
	BRA	M0S0_KEYCH0_S100

M0S0_KEYCH0_7:
	MR_PLAY_SPCH1_GROUP_NOP CS_TURRET2
	BRA	M0S0_KEYCH0_S100

M0S0_KEYCH0_8:
	MR_PLAY_SPCH1_GROUP_NOP CS_TURRET3
	STZ	R_ACCEHIT_CNT
	
	BRA	M0S0_KEYCH0_S100
	
M0S0_KEYCH0_S100:
	
	JSR	L_STOP_IDLE;CNT0
;
	LDA	R_SWPWM_PATT_IDX
	BNE	M0S0_KEYCH0_1_S05B
	
;	LDA	#3
;	STA	REG_EA
;	JSR	BK0_GET_RANDOM0
;	LDA	REG_EA
	
	MR_START_SWPWM_PATT 0
	INC	R_SWPWM_PATT_IDX
	JMP	M0S0_CHKFG

M0S0_KEYCH0_1_S05B:
	CMP	#1
	BNE	M0S0_KEYCH0_1_S05C
	MR_START_SWPWM_PATT 1
	INC	R_SWPWM_PATT_IDX
	JMP	M0S0_CHKFG
	
M0S0_KEYCH0_1_S05C:
	MR_START_SWPWM_PATT 2
	STZ	R_SWPWM_PATT_IDX
	JMP	M0S0_CHKFG
	
M0S0_CNT0_IDLE:;4sec

	MR_RESET_IDLE0
	
	STZ	R_ACCEHIT_CNT
;
;	MR_START_SWPWM_PATT 4
;	MR_PLAY_SPCH1_GROUP_NOP CS_ULTIMATE
	
	JMP	M0S0_CHKFG
	
	LDA	#C_FALSE
	CMP	R_ACCELHIT_FLAG
	BEQ	M0S0_CNT0_FALSE
;TRUE->false
	STA	R_ACCELHIT_FLAG
	
;reset
	LDA	#0
	STA	R_FLESHCOUNT
	STA	R_TURRETCOUNT
	STA	R_ARMORCOUNT
	
	STZ	R_RANDOM_GP_NO
	JSR	L_GET_RANDOM_GP
	JSR	L_GET_RANDOM_GP_DATA
	STA	R_HITTYPE
	
M0S0_CNT0_FALSE:
	
	JMP	M0S0_CHKFG
;=============================================================
L_CHK_PLAY_HITTYPE:
	LDA	R_SWIPE_FLAG
	CMP	#1
	BEQ	L_PLAY_HITTYPE
	LDA	R_SWIPE_FLAG1
	CMP	#1
	BEQ	L_PLAY_HITTYPE
	RTS
L_PLAY_HITTYPE:
	LDA	#4
	STA	R_SWIPE_FLAG
	
	LDA	R_HITTYPE
	BNE	L_PLAY_HITTYPE_S100
;=0
	JSR	BK0_TURRET_SOUND

	INC	R_TURRETCOUNT
	LDA	R_TURRETCOUNT
	CMP	#3
	BCC	L_PLAY_HITTYPE_S010
	STZ	R_TURRETCOUNT
L_PLAY_HITTYPE_S010:
	RTS

L_PLAY_HITTYPE_S100:

	JSR	BK0_ARMOR_SOUND
	INC	R_ARMORCOUNT
	LDA	R_ARMORCOUNT
	CMP	#3
	BCC	L_PLAY_HITTYPE_S110
	STZ	R_ARMORCOUNT
L_PLAY_HITTYPE_S110:
	RTS
	
;================================
BK0_FLESH_SOUND:
	LDA	R_FLESHCOUNT
	ASL	A
	TAX
	JMP	(BK0_FLESH_SOUND_TBL,X)
BK0_FLESH_SOUND_TBL:
	DW	BK0_FLESH_SOUND_0
	DW	BK0_FLESH_SOUND_1
	DW	BK0_FLESH_SOUND_2
	
BK0_FLESH_SOUND_0:
	MR_PLAY_SPCH1_GROUP_NOP CS_FLESH1
	MR_START_SWPWM_PATT 0
	RTS
BK0_FLESH_SOUND_1:
	MR_PLAY_SPCH1_GROUP_NOP CS_FLESH2
	MR_START_SWPWM_PATT 1
	RTS

BK0_FLESH_SOUND_2:
	MR_PLAY_SPCH1_GROUP_NOP CS_FLESH3
	MR_START_SWPWM_PATT 2
	RTS

BK0_TURRET_SOUND:
	LDA	R_TURRETCOUNT
	ASL	A
	TAX
	JMP	(BK0_TURRET_SOUND_TBL,X)
BK0_TURRET_SOUND_TBL:
	DW	BK0_TURRET_SOUND_0
	DW	BK0_TURRET_SOUND_1
	DW	BK0_TURRET_SOUND_2
	
BK0_TURRET_SOUND_0:
	MR_PLAY_SPCH1_GROUP_NOP CS_TURRET1
	MR_START_SWPWM_PATT 0
	RTS
BK0_TURRET_SOUND_1:
	MR_PLAY_SPCH1_GROUP_NOP CS_TURRET2
	MR_START_SWPWM_PATT 1
	RTS

BK0_TURRET_SOUND_2:
	MR_PLAY_SPCH1_GROUP_NOP CS_TURRET3
	MR_START_SWPWM_PATT 2
	RTS

BK0_ARMOR_SOUND:
	LDA	R_ARMORCOUNT
	ASL	A
	TAX
	JMP	(BK0_ARMOR_SOUND_TBL,X)
BK0_ARMOR_SOUND_TBL:
	DW	BK0_ARMOR_SOUND_0
	DW	BK0_ARMOR_SOUND_1
	DW	BK0_ARMOR_SOUND_2
	
BK0_ARMOR_SOUND_0:
	MR_PLAY_SPCH1_GROUP_NOP CS_ARMOR1
	MR_START_SWPWM_PATT 0
	RTS
BK0_ARMOR_SOUND_1:
	MR_PLAY_SPCH1_GROUP_NOP CS_ARMOR2
	MR_START_SWPWM_PATT 1
	RTS

BK0_ARMOR_SOUND_2:
	MR_PLAY_SPCH1_GROUP_NOP CS_ARMOR3
	MR_START_SWPWM_PATT 2
	RTS

M0S0_VD:
	MR_STOP_SWPWM_PATT
	JSR	BK0_STOP_ALL
	
M0S0_VD_LOOP:
	
	M_WDT_CLR
	
	BRA	M0S0_VD_LOOP
	
;===================================
;===================================
