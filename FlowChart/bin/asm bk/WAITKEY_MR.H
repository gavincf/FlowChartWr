
;=========================================================================
; MACRO
;=========================================================================
M_CLOSE_SPK MACRO

	.IF (CHIPSERIES = 'W567BS')
;	STZ	S0EN
	.ENDIF

	.if (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K')
;	STZ	SPEN
	.ENDIF
	.IF (CHIPSERIES = 'N588L')
;	STZ	SPEN
	.ENDIF
	.if (CHIPSERIES = 'N588H') .OR. (CHIPSERIES = 'N588J')
;	STZ	SPEN
	.ENDIF
	.IF (CHIPSERIES = 'W588AS')
	STZ	S0EN
	.ENDIF
	.IF (CHIPSERIES = 'W588CD')
	STZ	SPEN
	.ENDIF
	.IF (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
	.ENDIF
	ENDM
M_SET_SPK MACRO
	.IF (CHIPSERIES = 'W567BS')
	SET_SPEAKER_OUTPUT_TYPE_TO DAC_5mA	;USER S OPTION (DAC_5mA/ DAC_3mA/ PWM)
	.ENDIF
	.IF (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K')
;	SET_SPEAKER_OUTPUT_TYPE_TO DAC_5mA	;USER S OPTION (DAC_5mA/ DAC_3mA/ PWM)
	.ENDIF
	.IF (CHIPSERIES = 'N588L')
;	SET_SPEAKER_OUTPUT_TYPE_TO DAC_5mA	;USER S OPTION (DAC_5mA/ DAC_3mA/ PWM)
	.ENDIF
	.IF (CHIPSERIES = 'N588H') .OR. (CHIPSERIES = 'N588J')
;	SET_SPEAKER_OUTPUT_TYPE_TO DAC_5mA	;USER S OPTION (DAC_5mA/ DAC_3mA/ PWM)
	.ENDIF
	.IF (CHIPSERIES = 'W588AS')
	SET_SPEAKER_OUTPUT_TYPE_TO DAC_5mA	;USER S OPTION (DAC_5mA/ DAC_3mA/ PWM)
	.ENDIF
	.IF (CHIPSERIES = 'W588CD')
	NOP
	.ENDIF
	.IF (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
	.ENDIF
	ENDM

M_WDT_CLR MACRO
	.if (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K')
	LDA #CTL_CPU_WDT
	TSB !CTL_CPU
	.ENDIF
	.if (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
	LDA #WDTC_CLR
	STA !WDTC
	.ENDIF
	.if (CHIPSERIES = 'N588L')
.IFDEF C_CHK_LVD_EN
	LDA #CTL_CPU_WDT
	TSB !CTL_CPU
.ELSE
	LDA #CTL_CPU_WDT
	TSB !CTL_CPU
.ENDIF
	.ENDIF
	.if (CHIPSERIES = 'N588H') .OR. (CHIPSERIES = 'N588J')
	WDT
	.ENDIF
	ENDM
M_MCU_STOP MACRO
	.if (CHIPSERIES = 'N567G') .OR. (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K')
	LDA #CTL_CPU_STOP
	TSB !CTL_CPU
	.ENDIF
	.if (CHIPSERIES = 'N588L')
	LDA #CTL_CPU_STOP
	TSB !CTL_CPU
	.ENDIF
	.IF (CHIPSERIES = 'N588H') .OR. (CHIPSERIES = 'N588J')
	ENTER_STOP
	.ENDIF
	.if (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
	STOP
	.ENDIF
	ENDM
M_INT_ENABLE MACRO VALUE
	.if (CHIPSERIES = 'N588H') .OR. (CHIPSERIES = 'N588J')
	LDA	#.LOW.VALUE
	TSB	!IEF0
	.ENDIF
	.if (CHIPSERIES = 'N588L')
	LDA	#.LOW.VALUE
	TSB	!IEF0
	.ENDIF
	.IF (CHIPSERIES = 'N567G')
	LDA	#.LOW.VALUE
	TSB	!IEF0
	.ENDIF	
	.IF (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K')
	LDA	#.LOW.VALUE
	TSB	!IEF0
	LDA	#.HIGH.VALUE
	TSB	!IEF1
	.ENDIF	
	.if (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
	LDA	#.LOW.VALUE
	TSB	!IEF0
	LDA	#.HIGH.VALUE
	TSB	!IEF1
	.ENDIF	
	ENDM
M_INT_DISABLE MACRO VALUE
	.if (CHIPSERIES = 'N588H') .OR. (CHIPSERIES = 'N588J')
	LDA	#.LOW.VALUE
	TRB	!IEF0
	.ENDIF
	.if (CHIPSERIES = 'N588L')
	LDA	#.LOW.VALUE
	TRB	!IEF0
	.ENDIF
	.IF (CHIPSERIES = 'N567G') 
	LDA	#.LOW.VALUE
	TRB	!IEF0
	.ENDIF	
	.IF (CHIPSERIES = 'N567H') .OR. (CHIPSERIES = 'N567K')
	LDA	#.LOW.VALUE
	TRB	!IEF0
	LDA	#.HIGH.VALUE
	TRB	!IEF1
	.ENDIF	
	.if (CHIPSERIES = 'N589A') .OR. (CHIPSERIES = 'N589B') .OR. (CHIPSERIES = 'N589C') .OR. (CHIPSERIES = 'N589D')
	LDA	#.LOW.VALUE
	TRB	!IEF0
	LDA	#.HIGH.VALUE
	TRB	!IEF1
	.ENDIF	

	ENDM
	
M_SET_CNT0 MACRO VALUE
	LDA	#.LOW.VALUE
	STA	DLYCNT0
	LDA	#.HIGH.VALUE
	STA	DLYCNT0+1
	LDA	#C_CNT0_BIT

	TRB	<DP_USER_FLAG_B
	ENDM
	
M_SET_CNT0_IDX MACRO VALUE,IDX
	LDA	#.LOW.VALUE
	STA	DLYCNT0
	LDA	#.HIGH.VALUE
	STA	DLYCNT0+1
	LDA	#C_CNT0_BIT
	TRB	<DP_USER_FLAG_B
	LDA	#IDX
	STA	DLYCNT0_IDX
	
	ENDM

M_SET_CNT1 MACRO VALUE
	LDA	#.LOW.VALUE
	STA	DLYCNT1
	LDA	#.HIGH.VALUE
	STA	DLYCNT1+1
	LDA	#C_CNT1_BIT

	TRB	<DP_USER_FLAG_B
	ENDM

M_SET_CNT1_IDX MACRO VALUE,IDX
	LDA	#.LOW.VALUE
	STA	DLYCNT1
	LDA	#.HIGH.VALUE
	STA	DLYCNT1+1
	LDA	#C_CNT1_BIT
	TRB	<DP_USER_FLAG_B
	LDA	#IDX
	STA	DLYCNT1_IDX
	ENDM

M_SET_CNT2 MACRO VALUE
	LDA	#.LOW.VALUE
	STA	DLYCNT2
	LDA	#.HIGH.VALUE
	STA	DLYCNT2+1
	LDA	#C_CNT2_BIT
	TRB	<DP_USER_FLAG_B
	ENDM

M_SET_CNT2_IDX MACRO VALUE,IDX
	LDA	#.LOW.VALUE
	STA	DLYCNT2
	LDA	#.HIGH.VALUE
	STA	DLYCNT2+1
	LDA	#C_CNT2_BIT
	TRB	<DP_USER_FLAG_B
	LDA	#IDX
	STA	DLYCNT2_IDX
	ENDM

M_SET_CNT3 MACRO VALUE
	LDA	#.LOW.VALUE
	STA	DLYCNT3
	LDA	#.HIGH.VALUE
	STA	DLYCNT3+1
	LDA	#C_CNT3_BIT

	TRB	<DP_USER_FLAG_B
	ENDM

M_SET_CNT3_IDX MACRO VALUE,IDX
	LDA	#.LOW.VALUE
	STA	DLYCNT3
	LDA	#.HIGH.VALUE
	STA	DLYCNT3+1
	LDA	#C_CNT3_BIT
	TRB	<DP_USER_FLAG_B
	LDA	#IDX
	STA	DLYCNT3_IDX
	ENDM

	
MR_SET_GAPTIME_FLAG MACRO
	LDA	#C_BIT3
	TSB	<USER_INT_FLAG0
	ENDM
MR_CLR_GAPTIME_FLAG MACRO
	LDA	#C_BIT3
	TRB	<USER_INT_FLAG0
	ENDM
MR_TEST_GAPTIME_FLAG MACRO
	LDA	#C_BIT3
	BIT	<USER_INT_FLAG0
	ENDM
MR_SET_TMGX_GAP_FLAG MACRO
	LDA #C_BIT2
	TSB <USER_INT_FLAG0
	ENDM
MR_CLR_TMGX_GAP_FLAG MACRO
	LDA	#C_BIT2
	TRB	<USER_INT_FLAG0
	ENDM
MR_TEST_TMGX_GAP_FLAG MACRO
	LDA	#C_BIT2
	BIT	<USER_INT_FLAG0
	ENDM

MR_USER_TMGX_ISR MACRO
	MR_SET_TMGX_GAP_FLAG
	JMP	USER_TMGX_ISR
USER_TMGX_ISR_RET:
	ENDM

MR_CHK_SPCH1_EN MACRO
	LDA	#C_CHK_SPCH1_BIT
	TSB	USER_FLAG10
	LDA	#C_SPCH1_BIT
	TRB	DP_USER_FLAG_A
	ENDM
MR_CHK_SPCH1_DIS MACRO
	LDA	#C_CHK_SPCH1_BIT
	TRB	USER_FLAG10
	LDA	#C_SPCH1_BIT
	TRB	DP_USER_FLAG_A
	ENDM
M_MIX_SPCH1MS_EN MACRO
	LDA	#C_BIT4
	TSB	USER_FLAG10
	ENDM
M_MIX_SPCH1MS_DIS MACRO
	LDA	#C_BIT4
	TRB	USER_FLAG10
	ENDM
M_DET_MIX_SPCH1MS_EN MACRO
	LDA	#C_BIT4
	BIT	USER_FLAG10
	ENDM

MR_CHK_SPCH1_MS_EN MACRO
	LDA	#C_CHK_SPCH1_BIT
	TSB	USER_FLAG10
	LDA	#C_SPCH1_BIT
	TRB	DP_USER_FLAG_A
	M_MIX_SPCH1MS_EN
	ENDM
MR_CHK_SPCH1_NMS_EN MACRO
	LDA	#C_CHK_SPCH1_BIT
	TSB	USER_FLAG10
	LDA	#C_SPCH1_BIT
	TRB	DP_USER_FLAG_A
	M_MIX_SPCH1MS_DIS
	ENDM
MR_CHK_SPCH1_MS_DIS MACRO
	LDA	#C_CHK_SPCH1_BIT
	TRB	USER_FLAG10
	LDA	#C_SPCH1_BIT
	TRB	<DP_USER_FLAG_A
	M_MIX_SPCH1MS_DIS
	ENDM
;MR_CHK_SPCH1_NMS_DIS MACRO
;	LDA	#C_CHK_SPCH1_BIT
;	TRB	USER_FLAG10
;	LDA	#C_SPCH1_BIT
;	TRB	<DP_USER_FLAG_A
;	M_MIX_SPCH1MS_DIS
;	ENDM
MR_CHK_SPCH2_EN MACRO
	LDA	#C_CHK_SPCH2_BIT
	TSB	USER_FLAG10
	LDA	#C_SPCH2_BIT
	TRB	<DP_USER_FLAG_A
	ENDM
MR_CHK_MS1_EN MACRO
	LDA	#C_CHK_MS1_BIT
	TSB	USER_FLAG10
	LDA	#C_MS1_BIT
	TRB	<DP_USER_FLAG_A
	ENDM
MR_CHK_EVO1_EN MACRO
	LDA	#C_CHK_EVO1_BIT
	TSB	USER_FLAG10
	LDA	#C_EVO1_BIT
	TRB	<DP_USER_FLAG_A
	ENDM

MR_CHK_SPMD_EN MACRO
	LDA	#C_CHK_SPMD_BIT
	TSB	USER_FLAG10
	LDA	#C_SPMD_BIT
	TRB	<DP_USER_FLAG_A
	ENDM

MR_CHK_SPCH2_DIS MACRO
	LDA	#C_CHK_SPCH2_BIT
	TRB	USER_FLAG10
	LDA	#C_SPCH2_BIT
	TRB	<DP_USER_FLAG_A
	ENDM
MR_CHK_MS1_DIS MACRO
	LDA	#C_CHK_MS1_BIT
	TRB	USER_FLAG10
	LDA	#C_MS1_BIT
	TRB	<DP_USER_FLAG_A
	ENDM
MR_CHK_EVO1_DIS MACRO
	LDA	#C_CHK_EVO1_BIT
	TRB	USER_FLAG10
	LDA	#C_EVO1_BIT
	TRB	<DP_USER_FLAG_A
	ENDM

MR_CHK_SPMD_DIS MACRO
	LDA	#C_CHK_SPMD_BIT
	TRB	USER_FLAG10
	LDA	#C_SPMD_BIT
	TRB	<DP_USER_FLAG_A
	ENDM



;========================================



M_CHK_KEYCH0 MACRO VALUE
	LDA	#C_KEYCH0_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_KEYCH1 MACRO VALUE
	LDA	#C_KEYCH1_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A
	JMP	VALUE
	ENDM
M_CHK_KEYCH2 MACRO VALUE
	LDA	#C_KEYCH2_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_KEYCH3 MACRO VALUE
	LDA	#C_KEYCH3_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_NOTECH0 MACRO VALUE
	LDA	#C_NOTECH0_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_NOTECH1 MACRO VALUE
	LDA	#C_NOTECH1_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JMP	VALUE
	ENDM


M_CHK_SPCH1 MACRO VALUE
	LDA	#C_SPCH1_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SPCH2 MACRO VALUE
	LDA	#C_SPCH2_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_MS1 MACRO VALUE
	LDA	#C_MS1_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SPCH3 MACRO VALUE
	LDA	#C_SPCH3_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_CASI MACRO 	VALUE
	LDA	#C_CASI_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_EVO1 MACRO VALUE
	LDA	#C_EVO1_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_CNT0 MACRO VALUE
	LDA	#C_CNT0_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_CNT1 MACRO VALUE
	LDA	#C_CNT1_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_CNT2 MACRO VALUE
	LDA	#C_CNT2_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_CNT3 MACRO VALUE
	LDA	#C_CNT3_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_VD MACRO VALUE
	LDA	#C_VD_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_WIPER_PATT_DLYCNT MACRO VALUE
	LDA	#C_WIPER_PATT_DLYCNT_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JMP	VALUE
	ENDM


M_CHK_SWPWM_PATT MACRO VALUE
	LDA	#C_SWPWM_PATT_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_WIPER_PATTEND MACRO VALUE
	LDA	#C_WIPER_PATTEND_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_EQU_NEXT MACRO VALUE
	LDA	#C_EQU_NEXT_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_AUTOCNT MACRO VALUE
	LDA	#C_AUTOCNT_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JMP	VALUE
	ENDM


M_CHK_SKEY0 MACRO VALUE
	LDA	#C_SKEY0_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY1 MACRO VALUE
	LDA	#C_SKEY1_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY2 MACRO VALUE
	LDA	#C_SKEY2_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY3 MACRO VALUE
	LDA	#C_SKEY3_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY4 MACRO VALUE
	LDA	#C_SKEY4_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY5 MACRO VALUE
	LDA	#C_SKEY5_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY6 MACRO VALUE
	LDA	#C_SKEY6_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY7 MACRO VALUE
	LDA	#C_SKEY7_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY8 MACRO VALUE
	LDA	#C_SKEY8_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY9 MACRO VALUE
	LDA	#C_SKEY9_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY10 MACRO VALUE
	LDA	#C_SKEY10_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY11 MACRO VALUE
	LDA	#C_SKEY11_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY12 MACRO VALUE
	LDA	#C_SKEY12_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY13 MACRO VALUE
	LDA	#C_SKEY13_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY14 MACRO VALUE
	LDA	#C_SKEY14_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JMP	VALUE
	ENDM
M_CHK_SKEY15 MACRO VALUE
	LDA	#C_SKEY15_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JMP	VALUE
	ENDM
;===========================================
M_CHK_KEYCH0_JSRBK MACRO L_SUB
	LDA	#C_KEYCH0_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_KEYCH1_JSRBK MACRO L_SUB
	LDA	#C_KEYCH1_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_KEYCH2_JSRBK MACRO L_SUB
	LDA	#C_KEYCH2_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_KEYCH3_JSRBK MACRO L_SUB
	LDA	#C_KEYCH3_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_NOTECH0_JSRBK MACRO L_SUB
	LDA	#C_NOTECH0_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_NOTECH1_JSRBK MACRO L_SUB
	LDA	#C_NOTECH1_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JSR L_SUB
	ENDM


M_CHK_SPCH1_JSRBK MACRO L_SUB
	LDA	#C_SPCH1_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SPCH2_JSRBK MACRO L_SUB
	LDA	#C_SPCH2_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_MS1_JSRBK MACRO L_SUB
	LDA	#C_MS1_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SPCH3_JSRBK MACRO L_SUB
	LDA	#C_SPCH3_BIT
	BIT	<DP_USER_FLAG_A
	BEQ	5
	TRB	<DP_USER_FLAG_A;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_CNT0_JSRBK MACRO L_SUB
	LDA	#C_CNT0_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_CNT1_JSRBK MACRO L_SUB
	LDA	#C_CNT1_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_CNT2_JSRBK MACRO L_SUB
	LDA	#C_CNT2_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_CNT3_JSRBK MACRO L_SUB
	LDA	#C_CNT3_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_VD_JSRBK MACRO L_SUB
	LDA	#C_VD_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_WIPER_PATT_DLYCNT_JSRBK MACRO L_SUB
	LDA	#C_WIPER_PATT_DLYCNT_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JSR L_SUB
	ENDM


M_CHK_SWPWM_PATT_JSRBK MACRO L_SUB
	LDA	#C_SWPWM_PATT_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_WIPER_PATTEND_JSRBK MACRO L_SUB
	LDA	#C_WIPER_PATTEND_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_EQU_NEXT_JSRBK MACRO L_SUB
	LDA	#C_EQU_NEXT_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_AUTOCNT_JSRBK MACRO L_SUB
	LDA	#C_AUTOCNT_BIT
	BIT	<DP_USER_FLAG_B
	BEQ	5
	TRB	<DP_USER_FLAG_B;2 BYTE
	JSR L_SUB
	ENDM


M_CHK_SKEY0_JSRBK MACRO L_SUB
	LDA	#C_SKEY0_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY1_JSRBK MACRO L_SUB
	LDA	#C_SKEY1_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY2_JSRBK MACRO L_SUB
	LDA	#C_SKEY2_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY3_JSRBK MACRO L_SUB
	LDA	#C_SKEY3_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY4_JSRBK MACRO L_SUB
	LDA	#C_SKEY4_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY5_JSRBK MACRO L_SUB
	LDA	#C_SKEY5_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY6_JSRBK MACRO L_SUB
	LDA	#C_SKEY6_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY7_JSRBK MACRO L_SUB
	LDA	#C_SKEY7_BIT
	BIT	<DP_SKEY_FLAG0
	BEQ	5
	TRB	<DP_SKEY_FLAG0;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY8_JSRBK MACRO L_SUB
	LDA	#C_SKEY8_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY9_JSRBK MACRO L_SUB
	LDA	#C_SKEY9_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY10_JSRBK MACRO L_SUB
	LDA	#C_SKEY10_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY11_JSRBK MACRO L_SUB
	LDA	#C_SKEY11_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY12_JSRBK MACRO L_SUB
	LDA	#C_SKEY12_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY13_JSRBK MACRO L_SUB
	LDA	#C_SKEY13_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY14_JSRBK MACRO L_SUB
	LDA	#C_SKEY14_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JSR L_SUB
	ENDM
M_CHK_SKEY15_JSRBK MACRO L_SUB
	LDA	#C_SKEY15_BIT
	BIT	<DP_SKEY_FLAG1
	BEQ	5
	TRB	<DP_SKEY_FLAG1;2 BYTE
	JSR L_SUB
	ENDM



;===========================================
M_PAUSE_WAITKEY_CNT0TO3 MACRO
	LDA	#C_BIT3	
	TSB	USER_FLAG10
	ENDM
M_RESUME_WAITKEY_CNT0TO3 MACRO
	LDA	#C_BIT3	
	TRB	USER_FLAG10
	ENDM







