
;================================================
; with PWM PATTERN
;		LED PWM CONTROL
;单独控制每个PWMLED 的LEVEL。使用table.更换LEVEL时间同步.
; For PWM pattern
;================================================
;
; TMG_PERIOD * LEVEL = PWM_PRERIOD ; FREQ = 1 / PWM_PRERIOD
;================================================
;
C_PWMS_MAX EQU	1 ; max: 8


C_SWPWM_FADEINOUT_EN	EQU	0

C_SWPWM_PATT_EN	EQU	1
;1: SWPWM AS PATT: (X IN 1 control): PWM_FLAG .0 control
;0: SWPWM control each one: PWM_FLAG .7:.0 control

;--------------------------------------------------------
C_SWPWM_PATT_TBL_BYTE EQU	4;8/4
;--------------------------------------------------------
C_SWPWM_DIV_CTRL_EN	EQU	1
C_SWPWM_PATT_INCDEC_EN	EQU	1

;--------------------------------------
C_PATT_PWM3_MIX_EN EQU	 0
;-----------------------------------


;================================
;----  LED PATT  ----------------
;================================
C_LED_PATT0_IDX		 EQU	0
C_LED_PATT1_IDX		 EQU	1
C_LED_PATT2_IDX    EQU	2
C_LED_PATT3_IDX    EQU	3
C_LED_PATT4_IDX    EQU	4

C_3LED_TABLE0_EN	EQU	0
C_RGB_TABLE_EN	EQU	0


;========================== PWM =================
;>=72HZ,32level,500us/T ; for all pwms

C_MAX_LEVEL	EQU	20;



