
.IF ( C_RANDOM_GP_USED .EQ. 1)



T_RANDOM_BUF_MAX:
 DB C_GP_TYPE_MAX

 
 



T_RANDOM_GROUP:

 DW T_GP_TYPE

T_GP_TYPE:
 DB 0
 DB 1



.ENDIF 
