




;==========================================================================
;	RAM
;==========================================================================


;================================================
;
;		LED PWM CONTROL
;单独控制每个PWMLED 的LEVEL。使用table.更换LEVEL时间同步.
;
;================================================
;
;================================================

		
PWM_FLAG	DS	1
;.0=1: PWM0 ENABLE
;.1=1: PWM1 ENABLE
;.2=1: PWM2 ENABLE
;.3=1: PWM3 ENABLE
;.4=1: PWM4 ENABLE
;.5=1: PWM5 ENABLE
;.6=1: PWM6 ENABLE
;.7=1: PWM7 ENABLE

PWM_FLAG1	DS	1
;.7=1: check pwm PATT end
;.6=0/1: PATT switch: 0:only pwm control,1:PATT with table
;PWM MODE
;.1:.0=0/1/2/3: PWM0 off,RAISE UP,FALL DOWN,PWM0 ON
;.3:.2=0/1/2/3: PWM1 off,RAISE UP,FALL DOWN,PWM1 ON
;.5:.4=0/1/2/3: PWM2 off,RAISE UP,FALL DOWN,PWM2 ON
	

PWM0_LEVEL	DS	1
PWM0_LEVEL_BUF	DS	1
	.IF ( C_PWMS_MAX .GT. 1 )
PWM1_LEVEL	DS	1
PWM1_LEVEL_BUF	DS	1
	.ENDIF
	.IF ( C_PWMS_MAX .GT. 2 )
PWM2_LEVEL	DS	1
	.ENDIF
	.IF ( C_PWMS_MAX .GT. 3 )
PWM3_LEVEL	DS	1
	.ENDIF
	.IF ( C_PWMS_MAX .GT. 4 )
PWM4_LEVEL	DS	1
	.ENDIF
	.IF ( C_PWMS_MAX .GT. 5 )
PWM5_LEVEL	DS	1
	.ENDIF
	.IF ( C_PWMS_MAX .GT. 6 )
PWM6_LEVEL	DS	1
	.ENDIF
	.IF ( C_PWMS_MAX .GT. 7 )
PWM7_LEVEL	DS	1
	.ENDIF
	
PWM_LEVEL_CNT	DS	1

	.IF( C_SWPWM_DIV_CTRL_EN .EQ. 1)
R_SWPWM_DIV_CTRL	DS	1
R_SWPWM_DIV_CTRL_BUF	DS	1
	.ENDIF
	
.IF (C_PATT_PWM3_MIX_EN .EQ. 1 )
R_SWPWM_DIV_CTRL2	DS	1
.ENDIF	
;================================
;----  LED PATT  ----------------
;================================
.IF ( C_SWPWM_PATT_EN .EQ. 1 )
SWPWM_PATT_CNT	DS	1 ;
SWPWM_PATT_TBL_PT	DS	1
SWPWM_PATT_TBL_PT1	DS	1

R_SWPWM_PATT	DS	1
.ENDIF
.IF (C_SWPWM_PATT_INCDEC_EN .EQ. 1)
R_SWPWM_PATT_INCDEC_TARGET DS 1
.ENDIF

R_SWPWM_PATT_STOP_IDX DS 	1

R_SWPWM_PATT_ADC DS 	1

