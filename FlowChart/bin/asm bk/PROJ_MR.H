;=========================================================================
; MACRO0
;=========================================================================
	
;==================================
;======================================

MR_TMGX_SET MACRO
;enable
.if (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K') .OR. (CHIPSERIES = 'N588L')
	JSR	BK0_START_TMG1_1MS
.ENDIF
.IF (CHIPSERIES = 'N588H') .OR. (CHIPSERIES = 'N588J')
	JSR	BK0_START_TMG0_05MS_W_CHK
.ENDIF
.if (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
	.IF( C_N589_TOUCH_EN .EQ. 1)
	;USE TMA
	JSR	BK0_START_TMA_045MS
	.ELSE
	JSR	BK0_START_TMG_025MS; for
	.ENDIF
.ENDIF
	ENDM

MR_TMGX_STOP MACRO 
;Disable
.IF (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K') .OR. (CHIPSERIES = 'N588L')
	JSR	BK0_STOP_TMGX
.ENDIF
.IF (CHIPSERIES = 'N588H') .OR. (CHIPSERIES = 'N588J')
	JSR	BK0_STOP_TMGX
.ENDIF
.IF (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
	.IF( C_N589_TOUCH_EN .EQ. 1)
	;USE TMA
	JSR	BK0_STOP_TMA
	.ELSE
	JSR	BK0_STOP_TMGX; for
	.ENDIF
.ENDIF ;(CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
	ENDM


.if (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K') .OR. (CHIPSERIES = 'N588L')
MR_POI_SET_IO MACRO
	LDA	#C_POI_BPD
	STA	!BPD
	LDA	#C_POI_BPM
	STA	!BPM

	LDA	#C_POI_BP0
	STA	!BP0
	LDA	#C_POI_BP1
	STA	!BP1
.if (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K')
	LDA	#C_POI_BP2
	STA	!BP2
.ENDIF
	ENDM
MR_PWON_SET_IO MACRO
	LDA	#C_PWON_BPD
	STA	!BPD
	LDA	#C_PWON_BPM
	STA	!BPM

	LDA	#C_PWON_BP0
	STA	!BP0
	LDA	#C_PWON_BP1
	STA	!BP1
.if (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K')
	LDA	#C_PWON_BP2
	STA	!BP2
.ENDIF
	ENDM
MR_WAKEUP_SET_IO MACRO
	LDA	#C_WAKEUP_BPD
	STA	!BPD
	LDA	#C_WAKEUP_BPM
	STA	!BPM

	LDA	#C_WAKEUP_BP0
	STA	!BP0
	LDA	#C_WAKEUP_BP1
	STA	!BP1
.if (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K')
	LDA	#C_WAKEUP_BP2
	STA	!BP2
.ENDIF
	ENDM
MR_WAKEUP1_SET_IO MACRO
	LDA	#C_WAKEUP1_BPD
	STA	!BPD
	LDA	#C_WAKEUP1_BPM
	STA	!BPM

	LDA	#C_WAKEUP1_BP0
	STA	!BP0
	LDA	#C_WAKEUP1_BP1
	STA	!BP1
.if (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K')
	LDA	#C_WAKEUP1_BP2
	STA	!BP2
.ENDIF
	ENDM
	
	
MR_PWOFF_SET_IO MACRO
	LDA	#C_PWOFF_BPD
	STA	!BPD
	LDA	#C_PWOFF_BPM
	STA	!BPM

	LDA	#C_PWOFF_BP0
	STA	!BP0
	LDA	#C_PWOFF_BP1
	STA	!BP1
.if (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K')
	LDA	#C_PWOFF_BP2
	STA	!BP2
.ENDIF
;.IF ( C_M1_HWPWM_EN .EQ. 1 )
;	JSR	BK0_HWPWM_STOP
;.ENDIF
	ENDM
	
MR_PWOFF_SET_WK MACRO
	LDA	#C_BP0EN_F_PWOFF
	STA	BP0EN_F
	LDA	#C_BP0EN_R_PWOFF
	STA	BP0EN_R
	
	LDA	#C_BP1EN_F_PWOFF
	STA	BP1EN_F
	LDA	#C_BP1EN_R_PWOFF
	STA	BP1EN_R
	
.if (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K')
	LDA	#C_BP2EN_F_PWOFF
	STA	BP2EN_F
	LDA	#C_BP2EN_R_PWOFF
	STA	BP2EN_R
.ENDIF

	ENDM
.ENDIF

.if (CHIPSERIES = 'N588H') .OR. (CHIPSERIES = 'N588J')
MR_PWON_SET_IO MACRO
	LDA	#C_PWON_BP0D
	STA	!BP0D
	LDA	#C_PWON_BP0M_BAK
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	STA	BP0M_BAK
.ELSE
	STA	BP0M_USER
.ENDIF
	ORA	#C_PWON_BP0_OP
	STA	!BP0

	LDA	#C_PWON_BP1D
	STA	!BP1D
	LDA	#C_PWON_BP1M_BAK
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	STA	BP1M_BAK
.ELSE
	STA	BP1M_USER
.ENDIF
	ORA	#C_PWON_BP1_OP
	STA	!BP1

.IF ( C_BP2_EXIST .EQ. 1)
	LDA	#C_PWON_BP2D
	STA	!BP2D
	LDA	#C_PWON_BP2M_BAK
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	STA	BP2M_BAK
.ELSE
	STA	BP2M_USER
.ENDIF
	ORA	#C_PWON_BP2_OP
	STA	!BP2
.ENDIF

	ENDM
MR_WAKEUP_SET_IO MACRO
	
	LDA	#C_WAKEUP_BP0D
	STA	!BP0D
	LDA	#C_WAKEUP_BP0M_BAK
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	STA	BP0M_BAK
.ELSE
	STA	BP0M_USER
.ENDIF
	ORA	#C_WAKEUP_BP0_OP
	STA	!BP0


	LDA	#C_WAKEUP_BP1D
	STA	!BP1D
	LDA	#C_WAKEUP_BP1M_BAK
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	STA	BP1M_BAK
.ELSE
	STA	BP1M_USER
.ENDIF
	ORA	#C_WAKEUP_BP1_OP
	STA	!BP1

.IF ( C_BP2_EXIST .EQ. 1)
	LDA	#C_WAKEUP_BP2D
	STA	!BP2D
	LDA	#C_WAKEUP_BP2M_BAK
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	STA	BP2M_BAK
.ELSE
	STA	BP2M_USER
.ENDIF
	ORA	#C_WAKEUP_BP2_OP
	STA	!BP2
.ENDIF

	ENDM
MR_WAKEUP1_SET_IO MACRO
	
	LDA	#C_WAKEUP1_BP0D
	STA	!BP0D
	LDA	#C_WAKEUP1_BP0M_BAK
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	STA	BP0M_BAK
.ELSE
	STA	BP0M_USER
.ENDIF
	ORA	#C_WAKEUP1_BP0_OP
	STA	!BP0

	LDA	#C_WAKEUP1_BP1D
	STA	!BP1D
	LDA	#C_WAKEUP1_BP1M_BAK
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	STA	BP1M_BAK
.ELSE
	STA	BP1M_USER
.ENDIF
	ORA	#C_WAKEUP1_BP1_OP
	STA	!BP1

.IF ( C_BP2_EXIST .EQ. 1)
	LDA	#C_WAKEUP1_BP2D
	STA	!BP2D
	LDA	#C_WAKEUP1_BP2M_BAK
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	STA	BP2M_BAK
.ELSE
	STA	BP2M_USER
.ENDIF
	ORA	#C_WAKEUP1_BP2_OP
	STA	!BP2
.ENDIF

	ENDM
MR_PWOFF_SET_IO MACRO
	
	LDA	#C_PWOFF_BP0D
	STA	!BP0D
	LDA	#C_PWOFF_BP0M_BAK
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	STA	BP0M_BAK
.ELSE
	STA	BP0M_USER
.ENDIF
	ORA	#C_PWOFF_BP0_OP
	STA	!BP0


	LDA	#C_PWOFF_BP1D
	STA	!BP1D
	LDA	#C_PWOFF_BP1M_BAK
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	STA	BP1M_BAK
.ELSE
	STA	BP1M_USER
.ENDIF
	ORA	#C_PWOFF_BP1_OP
	STA	!BP1

.IF ( C_BP2_EXIST .EQ. 1)
	LDA	#C_PWOFF_BP2D
	STA	!BP2D
	LDA	#C_PWOFF_BP2M_BAK
.IF ( C_ULTRAIO_IO_EN .EQ. 1 )
	STA	BP2M_BAK
.ELSE
	STA	BP2M_USER
.ENDIF
	ORA	#C_PWOFF_BP2_OP
	STA	!BP2
.ENDIF

	ENDM
MR_PWOFF_SET_WK MACRO
	LDA	#C_BP1EN_PWOFF
	STA	BP1EN
	ENDM
	
.ENDIF
;===========================================
.if (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
MR_POI_SET_IO MACRO
;
	LDA	!BP0D
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_POI_BP0D
	STA	!BP0D
;;
	LDA	!BP0M
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_POI_BP0M
	STA	!BP0M
;;
	LDA	!BP0R
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_POI_BP0R
	STA	!BP0R
;
	LDA	!BP1D
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_POI_BP1D
.IF (C_N589_TOUCH_EN .EQ. 1)
	ORA	#C_BIT7;RTP
.ENDIF
	STA	!BP1D
;;
	LDA	!BP1M
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_POI_BP1M
.IF (C_N589_TOUCH_EN .EQ. 1)
	AND	#C_BIT7V;RTP
.ENDIF
	STA	!BP1M
;;
	LDA	!BP1R
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_POI_BP1R
.IF (C_N589_TOUCH_EN .EQ. 1)
	ORA	#C_BIT7;RTP
.ENDIF
	STA	!BP1R
;
	LDA	!BP2D
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_POI_BP2D
	STA	!BP2D
;;
	LDA	!BP2M
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_POI_BP2M
	STA	!BP2M
;;
	LDA	!BP2R
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_POI_BP2R
	STA	!BP2R


.IF(C_BP3_EXIST .EQ. 1 )
	LDA	!BP3D
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_POI_BP3D
	STA	!BP3D
;;
	LDA	!BP3M
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_POI_BP3M
	STA	!BP3M
;;
	LDA	!BP3R
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_POI_BP3R
	STA	!BP3R
.ENDIF
	ENDM

MR_PWON_SET_IO MACRO
;
	LDA	!BP0D
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_PWON_BP0D
	STA	!BP0D
;;
	LDA	!BP0M
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_PWON_BP0M
	STA	!BP0M
;;
	LDA	!BP0R
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_PWON_BP0R
	STA	!BP0R
;
	LDA	!BP1D
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_PWON_BP1D
.IF (C_N589_TOUCH_EN .EQ. 1)
	ORA	#C_BIT7;RTP
.ENDIF
	STA	!BP1D
;;
	LDA	!BP1M
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_PWON_BP1M
.IF (C_N589_TOUCH_EN .EQ. 1)
	AND	#C_BIT7V;RTP
.ENDIF
	STA	!BP1M
;;
	LDA	!BP1R
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_PWON_BP1R
.IF (C_N589_TOUCH_EN .EQ. 1)
	ORA	#C_BIT7;RTP
.ENDIF
	STA	!BP1R
;
	LDA	!BP2D
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_PWON_BP2D
	STA	!BP2D
;;
	LDA	!BP2M
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_PWON_BP2M
	STA	!BP2M
;;
	LDA	!BP2R
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_PWON_BP2R
	STA	!BP2R


.IF(C_BP3_EXIST .EQ. 1 )
	LDA	!BP3D
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_PWON_BP3D
	STA	!BP3D
;;
	LDA	!BP3M
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_PWON_BP3M
	STA	!BP3M
;;
	LDA	!BP3R
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_PWON_BP3R
	STA	!BP3R
.ENDIF
	ENDM

MR_WAKEUP_SET_IO MACRO
;
	LDA	!BP0D
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_WAKEUP_BP0D
	STA	!BP0D
;;
	LDA	!BP0M
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_WAKEUP_BP0M
	STA	!BP0M
;;
	LDA	!BP0R
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_WAKEUP_BP0R
	STA	!BP0R
;
	LDA	!BP1D
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_WAKEUP_BP1D
.IF (C_N589_TOUCH_EN .EQ. 1)
	ORA	#C_BIT7;RTP
.ENDIF
	STA	!BP1D
;;
	LDA	!BP1M
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_WAKEUP_BP1M
.IF (C_N589_TOUCH_EN .EQ. 1)
	AND	#C_BIT7V;RTP
.ENDIF
	STA	!BP1M
;;
	LDA	!BP1R
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_WAKEUP_BP1R
.IF (C_N589_TOUCH_EN .EQ. 1)
	ORA	#C_BIT7;RTP
.ENDIF
	STA	!BP1R
;
	LDA	!BP2D
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_WAKEUP_BP2D
	STA	!BP2D
;;
	LDA	!BP2M
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_WAKEUP_BP2M
	STA	!BP2M
;;
	LDA	!BP2R
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_WAKEUP_BP2R
	STA	!BP2R


.IF(C_BP3_EXIST .EQ. 1 )
	LDA	!BP3D
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_WAKEUP_BP3D
	STA	!BP3D
;;
	LDA	!BP3M
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_WAKEUP_BP3M
	STA	!BP3M
;;
	LDA	!BP3R
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_WAKEUP_BP3R
	STA	!BP3R
.ENDIF
	ENDM


MR_WAKEUP1_SET_IO MACRO
;
	LDA	!BP0D
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_WAKEUP1_BP0D
	STA	!BP0D
;;
	LDA	!BP0M
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_WAKEUP1_BP0M
	STA	!BP0M
;;
	LDA	!BP0R
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_WAKEUP1_BP0R
	STA	!BP0R
;
	LDA	!BP1D
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_WAKEUP1_BP1D
.IF (C_N589_TOUCH_EN .EQ. 1)
	ORA	#C_BIT7;RTP
.ENDIF
	STA	!BP1D
;;
	LDA	!BP1M
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_WAKEUP1_BP1M
.IF (C_N589_TOUCH_EN .EQ. 1)
	AND	#C_BIT7V;RTP
.ENDIF
	STA	!BP1M
;;
	LDA	!BP1R
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_WAKEUP1_BP1R
.IF (C_N589_TOUCH_EN .EQ. 1)
	ORA	#C_BIT7;RTP
.ENDIF
	STA	!BP1R
;
	LDA	!BP2D
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_WAKEUP1_BP2D
	STA	!BP2D
;;
	LDA	!BP2M
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_WAKEUP1_BP2M
	STA	!BP2M
;;
	LDA	!BP2R
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_WAKEUP1_BP2R
	STA	!BP2R


.IF(C_BP3_EXIST .EQ. 1 )
	LDA	!BP3D
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_WAKEUP1_BP3D
	STA	!BP3D
;;
	LDA	!BP3M
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_WAKEUP1_BP3M
	STA	!BP3M
;;
	LDA	!BP3R
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_WAKEUP1_BP3R
	STA	!BP3R
.ENDIF
	ENDM

	
MR_PWOFF_SET_IO MACRO
;
	LDA	!BP0D
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_PWOFF_BP0D
	STA	!BP0D
;;
	LDA	!BP0M
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_PWOFF_BP0M
	STA	!BP0M
;;
	LDA	!BP0R
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_PWOFF_BP0R
	STA	!BP0R
;
	LDA	!BP1D
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_PWOFF_BP1D
.IF (C_N589_TOUCH_EN .EQ. 1)
	ORA	#C_BIT7;RTP
.ENDIF
	STA	!BP1D
;;
	LDA	!BP1M
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_PWOFF_BP1M
.IF (C_N589_TOUCH_EN .EQ. 1)
	AND	#C_BIT7V;RTP
.ENDIF
	STA	!BP1M
;;
	LDA	!BP1R
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_PWOFF_BP1R
.IF (C_N589_TOUCH_EN .EQ. 1)
	ORA	#C_BIT7;RTP
.ENDIF
	STA	!BP1R
;
	LDA	!BP2D
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_PWOFF_BP2D
	STA	!BP2D
;;
	LDA	!BP2M
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_PWOFF_BP2M
	STA	!BP2M
;;
	LDA	!BP2R
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_PWOFF_BP2R
	STA	!BP2R


.IF(C_BP3_EXIST .EQ. 1 )
	LDA	!BP3D
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_PWOFF_BP3D
	STA	!BP3D
;;
	LDA	!BP3M
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_PWOFF_BP3M
	STA	!BP3M
;;
	LDA	!BP3R
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_PWOFF_BP3R
	STA	!BP3R
.ENDIF
	ENDM
	
MR_PWOFF1_SET_IO MACRO
;
	LDA	!BP0D
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_PWOFF1_BP0D
	STA	!BP0D
;;
	LDA	!BP0M
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_PWOFF1_BP0M
	STA	!BP0M
;;
	LDA	!BP0R
	AND	#C_BP0_TOUCH_MASK
	ORA	#C_PWOFF1_BP0R
	STA	!BP0R
;
	LDA	!BP1D
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_PWOFF1_BP1D
.IF (C_N589_TOUCH_EN .EQ. 1)
	ORA	#C_BIT7;RTP
.ENDIF
	STA	!BP1D
;;
	LDA	!BP1M
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_PWOFF1_BP1M
.IF (C_N589_TOUCH_EN .EQ. 1)
	AND	#C_BIT7V;RTP
.ENDIF
	STA	!BP1M
;;
	LDA	!BP1R
	AND	#C_BP1_TOUCH_MASK
	ORA	#C_PWOFF1_BP1R
.IF (C_N589_TOUCH_EN .EQ. 1)
	ORA	#C_BIT7;RTP
.ENDIF
	STA	!BP1R
;
	LDA	!BP2D
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_PWOFF1_BP2D
	STA	!BP2D
;;
	LDA	!BP2M
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_PWOFF1_BP2M
	STA	!BP2M
;;
	LDA	!BP2R
	AND	#C_BP2_TOUCH_MASK
	ORA	#C_PWOFF1_BP2R
	STA	!BP2R


.IF(C_BP3_EXIST .EQ. 1 )
	LDA	!BP3D
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_PWOFF1_BP3D
	STA	!BP3D
;;
	LDA	!BP3M
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_PWOFF1_BP3M
	STA	!BP3M
;;
	LDA	!BP3R
	AND	#C_BP3_TOUCH_MASK
	ORA	#C_PWOFF1_BP3R
	STA	!BP3R
.ENDIF
	ENDM

MR_PWOFF_SET_WK MACRO
	LDA	#C_BP0EN_PWOFF
	STA	BP0EN
	LDA	#C_BP1EN_PWOFF
	STA	BP1EN
	LDA	#C_BP2EN_PWOFF
	STA	BP2EN
.IF(C_BP3_EXIST .EQ. 1 )
	LDA	#C_BP3EN_PWOFF
	STA	BP3EN
.ENDIF
	ENDM

MR_PWOFF1_SET_WK MACRO
	LDA	#C_BP0EN_PWOFF1
	STA	BP0EN
	LDA	#C_BP1EN_PWOFF1
	STA	BP1EN
	LDA	#C_BP2EN_PWOFF1
	STA	BP2EN
.IF(C_BP3_EXIST .EQ. 1 )
	LDA	#C_BP3EN_PWOFF1
	STA	BP3EN
.ENDIF
	ENDM

.ENDIF ;(CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')


;======================================


M_PRESET_ULTRA_IO MACRO
.IF (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K') .OR. (CHIPSERIES = 'N588L')
	LDA	#C_ULTRAIO_BP0
	TSB	BP0
	LDA	#C_ULTRAIO_BP1
	TSB	BP1
	.IF(C_BP2_EXIST .EQ. 1 )
	LDA	#C_ULTRAIO_BP2
	TSB	BP2
	.ENDIF
.ENDIF
.IF (CHIPSERIES = 'N588H') .OR. (CHIPSERIES = 'N588J')
	LDA	#C_ULTRAIO_BP0
	TSB	BP0
	LDA	#C_ULTRAIO_BP1
	TSB	BP1
	.IF(C_BP2_EXIST .EQ. 1 )
	LDA	#C_ULTRAIO_BP2
	TSB	BP2
	.ENDIF
.ENDIF
.IF (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
	LDA	#C_ULTRAIO_BP0
	TSB	BP0R
	LDA	#C_ULTRAIO_BP1
	TSB	BP1R
	LDA	#C_ULTRAIO_BP2
	TSB	BP2R
	.IF(C_BP3_EXIST .EQ. 1 )
	LDA	#C_ULTRAIO_BP3
	TSB	BP3R
	.ENDIF
.ENDIF
	ENDM




