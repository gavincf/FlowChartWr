;=======================================
;	<< PROJ_RAM.ASM >>
;===========================================




;===========================================
;C_MAX_VOL_IDX	EQU	0A0H
;C_MAX_TPO_IDX	EQU	0AH
;===========================================
;C_DEFAULT_TPO_IDX	EQU	05H
;C_DEFAULT_VOL_IDX	EQU	90H

;===================================
;
C_PWON_MODE	EQU	00H





;VOL_TPO_IDX	DS	1
;.3:.0:TPO LEVEL
;.7:.4:VOL LEVEL


SYS_MODE_NO	DS	1
;.7:.4:mode
;.3:.0: SUB MODE




USER_FLAG20	DS	1
;.7 = 0/1: SPEECH / EQU
;.6 = 0/1: normal eqution / EVT driver equation
;.5 = 0 / 1: CMPA/VD ;save status
;.4 = 0/1:halt flag clear /halt flag set; share for used:

;.3=0/1: VOL + / -
;.2=1:B_USER_MS1_BUSY
	
;.1:(reserved):=1:POI FLAG
;.0:(reserved):


;R_TOUCH_FLAG	DS	1
;.7=1: TOUCH CHECK ENABLE
;.7=0: TOUCH CHECK DISABLE

;R_WAKEUP_FLAG	DS	1

;T1_BASE		DS	2
;T1_DEVIA DS 	2


;C_FALSE EQU 0
;C_TRUE	EQU	1

R_HITTYPE 	DS 	1;0-1
R_ACCELHIT_FLAG 	DS 1
;0:FALSE
;1:TRUE
	
R_FLESHCOUNT DS 1
R_TURRETCOUNT DS 1
R_ARMORCOUNT	DS 1


R_Gsensor_TmpZ3_set DS 1


R_SWIPE_COUNT DS 1
	
R_SWIPE_FLAG DS 1
;=0
;=1:STEP0: playing swipe sound
;=2:step1: swipe sound played end
;=3:step2: hittype trigger
;=4:step3: hittype playing

R_SWIPE_FLAG1 DS 1
;For forwardstrike

R_SWPWM_PATT_IDX DS 1

R_ACCEHIT_CNT DS 1
