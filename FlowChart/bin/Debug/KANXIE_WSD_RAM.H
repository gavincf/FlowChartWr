

R_KANXIE_CHK_STEP   DS  1
R_KANXIE_STEP_DLYCNT DS  1
R_KANXIE_CNT DS 1
R_KANXIE_OV_DLYCNT  DS 2
R_KAN_TYPE0 DS 1




R_LAST_HORIZONTAL DS 1

 
MR_SET_KANXIE_IDX MACRO VALUE1,VALUE2

 LDA #VALUE1
 STA R_KANXIE_STEP_DLYCNT
 LDA #VALUE2
 STA R_KANXIE_CHK_STEP
 ENDM
 
MR_SET_KANXIE_OV MACRO
 LDA #.LOW.(1000000H-800*100/C_100GAP_FXF15) 
 STA R_KANXIE_OV_DLYCNT
 
 ENDM
MR_STOP_KANXIE_DLYCNT MACRO
 STZ R_KANXIE_OV_DLYCNT
 ENDM
 
