

;only for speech random table

;==============================================
C_RANDOM_GP_USED EQU 1
;for random table
;RANDOM_USER2.ASM
; JSR	RANDOM_GP_BUF_INIT
;
;	JSR	L_GET_RANDOM_GP
;	JSR	L_GET_RANDOM_GP_DATA
;	STA	SPCH1_NO
;	JSR	L_PLAY_SPCH1
;
;==============================================
C_GP_TYPE_IDX EQU	0
;=========================================
C_GP_TYPE_MAX	EQU	2



.IF ( C_RANDOM_GP_USED .EQ. 1 )
;
R_RANDOM_GP_NO DS	1
C_RANDOM_GP_CNT EQU	1 ;C_GP_XXX_IDX+1
R_RANDOM_GP_BUF DS C_RANDOM_GP_CNT ;1-X
	
.ENDIF
	
