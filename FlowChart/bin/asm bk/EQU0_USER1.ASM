
;================================
; EQU0 table ASM define
;================================
;2020/5/12 15:39:02
	
T_EQU_TBL:
	DW	T_EQU_000


;========================================;
;---------------------------------------;
;use X byte for 1 section;
;----------------------------------------;
;1st byte: COMMAND: .7:.6:command;
;----------------------------------------;
;C_EQU_EVT_BIT EQU	80H ; C_EQU_EVT_BIT,C_EQU_EVT_WP1_PATTEND_INT: should with Action together.for check action end
;with .7 = 0: EQU_NRL:SP / EQU_DLY END to next section.
;with .7 = 1: EQU_EVT trigger next section::if with EQU_DLY+1:EQU_DLY,'EQU_DLY+1:EQU_DLY'can be 0,0;
;.6=0;
;C_EQU_SP EQU	00H;
;.6=1;
;C_EQU_DLY EQU	40H;
;C_EQU_LOOP	EQU	FEH,IDX:XX
;C_EQU_END	EQU	FFH;
;----------------------------------------;
;.5:.0 -- added action idx;
;EQU ACTION LIST: fill it;
; if = C_WP1PATT_XXX, can use 'C_WP1PATT_XXX' for EQU table
;----------------------------------------;
;C_EQU_ACT_SEL0	EQU	32; selection;
;C_EQU_ACT_SEL1	EQU	33; selection;
;C_EQU_ACT_SEL2	EQU	34; selection;
;C_EQU_ACT_SEL3	EQU	35; selection;
;C_EQU_ACT_SEL4	EQU	36; selection;
;C_EQU_ACT_SEL5	EQU	37; selection;
;---------------------------------------;
;ACT=62;reserved for 'C_EQU_LOOP';
;ACT=63;reserved for 'C_EQU_END';
;-----------------------------------;
;2nd byte: EVT IDX/SP_H/.HIGH.DLYCNT ;
;3rd byte: SP_H/SP_L/.HIGH.DLYCNT /.LOW.DLYCNT ;
;4th byte: SP_L/.LOW.DLYCNT;
;DLYCNT+1:DLYCNT:  MAX: 209sec
;----------------------------------;
;DB C_EQU_DLY|C_EQU_ACT1|C_EQU_EVT_BIT,C_EQU_EVT_XX_IDX,0,0,C_EQU_SP,.HIGH.CS_SG3_10_LITTLEYAWN_BIT16_10K,.LOW.CS_SG3_10_LITTLEYAWN_BIT16_10K
;DB C_EQU_SP|C_EQU_ACT2,.HIGH.CS_SG1_00_BABA_BIT16_10K,.LOW.CS_SG1_00_BABA_BIT16_10K
;DB	C_EQU_DLY,.HIGH.(1000000H-250*100/C_100GAP_FXF15),.LOW.(1000000H-250*100/C_100GAP_FXF15)
;
;========================================
; reference
;========================================
;	DB	C_EQU_DLY|C_EQU_ACT1,0,0  ; wait C_EQU_ACT1 end to next
;	DB	C_EQU_END


;========================================
T_EQU_000:

	
	
	


