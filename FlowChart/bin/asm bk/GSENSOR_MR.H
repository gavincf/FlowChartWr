;====================================================================
; --- F_GSensor_Macro.asm ---
;====================================================================
;
;
;
;
;
;--------------------------------------------------------------------
; --- M_Abs_LargeThan ---
;--------------------------------------------------------------------
;example: 	M_Abs_LargeThan #246,#10
;IN: A
;--------------------------------------------------------------------
M_Abs_LargeThan:	.MACRO	C_Negative,C_Positive
	CMP	C_Negative
	BCS	M_Abs_LargeThan_Fail_#
	CMP	C_Positive
	BRA	M_Abs_LargeThan_Exit_#
M_Abs_LargeThan_Fail_#:
	CLC
M_Abs_LargeThan_Exit_#:
;largethan:BCS
.ENDM
;
;
;--------------------------------------------
;example: 	M_int_Inside_plus #20,#40
;IN: A
;--------------------------------------------
M_int_Inside_plus:	.MACRO	RAM1,C_MIN,C_MAX
	LDA	RAM1
	CMP	C_MIN
	BCC	M_int_Inside_plus_Fail1#
	CMP	C_MAX
	BCC	M_int_Inside_plus_ok#
M_int_Inside_plus_Fail1#:
	LDA	#1 ;BNE:outside
	BRA	M_int_Inside_plus_Fail#
M_int_Inside_plus_ok#:
	LDA	#0 ;BEQ:inside
M_int_Inside_plus_Fail#:
	ENDM
;
;
;
; --- end --- end --- end --- end --- end --- end --- end --- end ---
; --- end --- end --- end --- end --- end --- end --- end --- end ---
