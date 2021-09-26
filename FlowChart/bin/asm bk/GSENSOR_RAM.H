;====================================================================
; --- F_GSensor_RAM.asm ---
;====================================================================
;
C_Gsensor_Y_Vertical	EQU	25	;>25 assume vertical
C_Gsensor_Y_VerticalP	EQU	C_Gsensor_Y_Vertical
C_Gsensor_Y_VerticalN	EQU	((C_Gsensor_Y_Vertical^0FFh)+1)
C_Gsensor_Stomp_IMPACT1	EQU	5	;>15 when impact
C_Gsensor_Stomp_IMPACT1P	EQU	C_Gsensor_Stomp_IMPACT1
C_Gsensor_Stomp_IMPACT1N	EQU	((C_Gsensor_Stomp_IMPACT1^0FFh)+1)
C_Gsensor_Stomp_IMPACT2	EQU	35	;25	;>30 when impact
C_Gsensor_Stomp_IMPACT2P	EQU	C_Gsensor_Stomp_IMPACT2
C_Gsensor_Stomp_IMPACT2N	EQU	((C_Gsensor_Stomp_IMPACT2^0FFh)+1)
C_Gsensor_Stomp_TRIGGER	EQU	3	;at least 3 point to trigger
;
C_Gsensor_Decel_Dn	EQU	FFH	;FDH
C_Gsensor_Accel_Up	EQU	03H
C_Gsensor_Check_Round	EQU	5
;
C_Gsensor_Check_Total	EQU	16	;checking cycle value
;
C_Gsensor_1G_Value	EQU	32
C_Gsensor_Steady_UpThr	EQU	C_Gsensor_1G_Value+5
C_Gsensor_Steady_UpThrP	EQU	C_Gsensor_Steady_UpThr
C_Gsensor_Steady_UpThrN	EQU	((C_Gsensor_Steady_UpThr^0FFh)+1)
C_Gsensor_Steady_LwThr	EQU	C_Gsensor_1G_Value-7
C_Gsensor_Steady_LwThrP	EQU	C_Gsensor_Steady_LwThr
C_Gsensor_Steady_LwThrN	EQU	((C_Gsensor_Steady_LwThr^0FFh)+1)
C_Gsensor_TestSteady_Up	EQU	C_Gsensor_1G_Value+5
C_Gsensor_TestSteady_Lw	EQU	C_Gsensor_1G_Value-5
C_Gsensor_Steady_YP	EQU	8
C_Gsensor_Steady_YN	EQU	F8H
C_Gsensor_Steady_Overshot_P	EQU	12
C_Gsensor_Steady_Overshot_N	EQU	F4H
C_Gsensor_SteadyStable	EQU	3	;at least ? setp = steady
C_Gsensor_MonoInc_Thr	EQU	4	;mono increasing count threshold
C_Gsensor_Swing_Steady	EQU	4	;X,Z steady in Swing check
;
C_Gsensor_Upward_XZ_Limit	EQU	16	;assume half G for X, Z limit
C_Gsensor_Upward_XZ_LimitP	EQU	C_Gsensor_Upward_XZ_Limit
C_Gsensor_Upward_XZ_LimitN	EQU	((C_Gsensor_Upward_XZ_Limit^0FFh)+1)
;
C_Gsensor_Confirm_dir	EQU	3	;3 continuous point confirm moving direction
C_Gsensor_Upward_Threshold	EQU	22;25	;highest point to lowest point threshold
C_Gsensor_Y_UPWARD_STEADY	EQU	20	;>20 assume back to steady
;
C_Gsensor_Wave_normal_Threshold	EQU	50
;C_Gsensor_Wave_Threshold	EQU	20	;25;35;42	;full wave threshold with Y value also change near 0
;C_Gsensor_Wave_Threshold_Lo	EQU	9	;half wave threshold
;C_Gsensor_Wave_Below	EQU	28;25;30	;when X or Z > threshold, other one and Y should below this value
C_Gsensor_Wave_Horizontal	EQU	16	;swing horizontal threshold
C_Gsensor_Wave_YDown	EQU	40	;swing with Y downward
C_Gsensor_Wave_YDown_XZ	EQU	6	;swing with Y downward ,X,Z near 0
C_Gsensor_Yaxis_Downward	EQU	ECH	;-20
C_Gsensor_Confirm_Dn	EQU	FEH
C_Gsensor_Confirm_Up	EQU	2
;
;--------------------------------------------------------------------
; --- RAMs ---
;--------------------------------------------------------------------
;
;-----------------------
R_BMA253_pt		DS	2;EQU	R_ZeroPage_Pt1
R_BMA253_rtn	DS	1;EQU	R_Gsensor_XCurve1
R_BMA253_Xval	DS	1;EQU	R_Gsensor_XCurve2
R_BMA253_Yval	DS	1;EQU	R_Gsensor_XCurve3
R_BMA253_Zval	DS	1;EQU	R_Gsensor_XCurve4
R_BMA253_Cnt	DS	1;EQU	R_Gsensor_XPoint1
R_BMA253_Addr	DS	1;EQU	R_Gsensor_XPoint2
R_BMA253_Data	DS	1;EQU	R_Gsensor_XPoint3
;
;-----------------------
; CANNOT REMOVE
R_Gsensor_SaveP	DS	1	; G sensor saving pointer
R_Gsensor_SaveS	DS	1	; G sensor saving Start position
;
;-----------------------
; CANNOT REMOVE BUT THE SIZE CAN BE CHANGE
C_Gdata_STotal	EQU	32 ;--according to valid ram and gap time of read g-sensor
R_SaveX_Base	DS	C_Gdata_STotal	; X save
R_SaveY_Base	DS	C_Gdata_STotal	; Y save
R_SaveZ_Base	DS	C_Gdata_STotal	; Z save
;
;-----------------------
; --- end --- end --- end --- end --- end --- end --- end --- end ---
; --- end --- end --- end --- end --- end --- end --- end --- end ---
