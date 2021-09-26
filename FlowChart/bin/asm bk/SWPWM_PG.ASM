


	
;===================================================
; L_PWMS_SOLVE_SUB
; called in 'ISR'
; USE: Y
;T=500US
;===================================================

L_PWM_SOLVE_OFF: ; turn PWMS to OFF
 .IF ( C_PWMS_MAX .GT. 0 )
	M_DET_PWM0_EN
	BEQ	L_PWM_SOLVE_S1110
	LDA	<PWM_LEVEL_CNT
	CMP	<PWM0_LEVEL
	BNE	L_PWM_SOLVE_S1110
	M_PWM0_OFF
L_PWM_SOLVE_S1110:
 .ENDIF
 .IF ( C_PWMS_MAX .GT. 1 )
	M_DET_PWM1_EN
	BEQ	L_PWM_SOLVE_S1120
	LDA	<PWM_LEVEL_CNT
	CMP	<PWM1_LEVEL
	BNE	L_PWM_SOLVE_S1120
	M_PWM1_OFF
L_PWM_SOLVE_S1120
 .ENDIF

	RTS
	
;-----------------------------------
L_PWMS_SOLVE_SUB:
; 
; 0 ; 0 - ( C_SWPWM_MAX_LEVEL-1 )
;	
	INC	<PWM_LEVEL_CNT ; 
	LDA	<PWM_LEVEL_CNT
	CMP	#C_MAX_LEVEL ;20
	BNE	L_PWM_SOLVE_OFF; UP
	STZ	<PWM_LEVEL_CNT
;

;===============================================
L_PWM_SOLVE_FIXED: ;fixed pwm / not patt table
; save CPU mips
;PWM CIRCLE END;-> next level/Table data
.IF (C_SWPWM_DIV_CTRL_EN .EQ. 1)
	DEC	R_SWPWM_DIV_CTRL
	LDA	R_SWPWM_DIV_CTRL
	BEQ	L_PWM_SOLVE_S0101

	JMP	L_PWM_DUTY_ST ;PWM_LEVEL_CNT = 0

L_PWM_SOLVE_S0101: ; pwm circle/1 period reach

;----------------------------------------
	LDA	R_SWPWM_DIV_CTRL_BUF; load new div
	STA	R_SWPWM_DIV_CTRL
;----------------------------------------
.ENDIF	;C_SWPWM_DIV_CTRL_EN
.IF (C_SWPWM_PATT_EN .EQ. 1)
	MR_DET_SWPWM_PATT_EN
	BEQ	L_PWM_SOLVE_S0102
	JSR	LOAD_PWMS_PATT
L_PWM_SOLVE_S0102:
.ENDIF	
		
.IF ( C_SWPWM_FADEINOUT_EN .EQ. 1 )
	MR_SWPWM_FADEINOUT
.ENDIF

;==================================
; PWM SHOW PART
;==================================

	MR_DET_SWPWM_PATT_EN
	BNE	L_PWM_DUTY_ST2; PATT CONTROL 'PWMX_LEVEL'
	JMP	L_PWM_DUTY_ST
	
L_PWM_DUTY_ST2: ;WITHOUT 'PLY'; PATT CONTROL
;======================================
	.IF ( C_PWMS_MAX .GT. 0 )
;if PWM_FLAG1.6 = 0: PWM_FLAG.0 as  as PWM0 ENABLE
;constance(fixed) PWM LEVEL
;	M_DET_PWM0_EN
;	BEQ	L_PWM_SOLVE_S0011
; update level
;BUF CONTROL
;	LDA	<PWM0_LEVEL_BUF
;	STA	<PWM0_LEVEL
;L_PWM_SOLVE_S001:
	LDA	<PWM0_LEVEL
	BNE	L_PWM_SOLVE_S0010
	M_PWM0_OFF
	BRA	L_PWM_SOLVE_S0011
L_PWM_SOLVE_S0010:
	M_PWM0_ON
L_PWM_SOLVE_S0011:
	 .ENDIF;( C_PWMS_MAX .GT. 0 )


	RTS
	
;==================================
; PWM SHOW PART
;==================================
L_PWM_DUTY_ST:

.IF ( C_PWMS_MAX .GT. 0 )
	M_DET_PWM0_EN
	BEQ	L_PWM_SOLVE_S011
	LDA	<PWM0_LEVEL
	BEQ	L_PWM_SOLVE_S010
	M_PWM0_ON
	BRA	L_PWM_SOLVE_S011
L_PWM_SOLVE_S010:
	M_PWM0_OFF
L_PWM_SOLVE_S011:
.ENDIF	;( C_PWMS_MAX .GT. 0 )
.IF ( C_PWMS_MAX .GT. 1 )
	M_DET_PWM1_EN
	BEQ	L_PWM_SOLVE_S111
	LDA	<PWM1_LEVEL
	BEQ	L_PWM_SOLVE_S110
	M_PWM1_ON
	BRA	L_PWM_SOLVE_S111
L_PWM_SOLVE_S110:
	M_PWM1_OFF
L_PWM_SOLVE_S111:
.ENDIF	;( C_PWMS_MAX .GT. 1 )

	RTS


;=============================================
SWPWM_INIT:
.IF ( C_SWPWM_DIV_CTRL_EN .EQ. 1 )
	LDA	#1 
	STA	R_SWPWM_DIV_CTRL
	STA	R_SWPWM_DIV_CTRL_BUF
.ENDIF
	STZ	PWM0_LEVEL
	STZ	PWM0_LEVEL_BUF
;DIS PATT
	MR_SET_SWPWM_PATT_DIS
	RTS

	
;======================================
; other function:reserved
;======================================

;=====================================================
.IF (C_PATT_PWM3_MIX_EN .EQ. 1 )
L_PWM3_SEPERATE: ; seperate solve pwm3
	LDA	#C_BIT3
	BIT	PWM_FLAG
	BEQ	L_PWM3_S200
;new div for pwm3
	DEC	R_SWPWM_DIV_CTRL2
	LDA	R_SWPWM_DIV_CTRL2
	BEQ	L_PWM3_SEPERATE_DIV2
;
	LDA	<PWM3_LEVEL
	BEQ	L_PWM_SOLVE_S040
	M_PWM3_ON
	BRA	L_PWM_SOLVE_S041
L_PWM_SOLVE_S040:
	M_PWM3_OFF
L_PWM_SOLVE_S041:

	JMP	L_PWM3_SEPERATE_RET
L_PWM3_SEPERATE_DIV2: ;div2 end: pwm3
	LDA	#3
	STA	R_SWPWM_DIV_CTRL2
;Level start
;---------------------------------------
;---------------------------------------
;
L_PWM3_LEVEL_START: ;LEVEL restart
	LDA	#C_BIT3
	BIT	PWM_FLAG
	BEQ	L_PWM3_S120
	LDA	<PWM3_LEVEL
	BNE	L_PWM3_S110
	M_PWM3_OFF
	BRA	L_PWM3_S120
L_PWM3_S110:
	M_PWM3_ON
L_PWM3_S120:

L_PWM3_S200:
	JMP	L_PWM3_SEPERATE_RET
.ENDIF ;(C_PATT_PWM3_MIX_EN .EQ. 1 )

	
;=================================================
;要做PWM的渐亮灭，
;亮度为16级以上才平滑。
;500Us作为一个计数
;为不闪，频率应在66以上




