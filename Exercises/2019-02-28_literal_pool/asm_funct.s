;int search_in_pool (unsigned int VAR); 
				
				AREA asm_functions, CODE, READONLY				
                EXPORT  search_in_pool
					
search_in_pool	
N				EQU		3
				MOV   	r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}
				MOV		R8,#-1
				MOV		R7,#0
				LDR		R4,=pool
loop			LDRB	R5,[R4],#1
				CMP		R5,R0
				MOVEQ	R8,R7
				BEQ		fine
				ADD		R7,R7,#1
				CMP		R7,#N
				BNE		loop
fine			MOV		R0,R8				
				; setup a value for R0 to return
end 			LDMFD sp!,{r4-r8,r10-r11,pc}
pool			DCB		0x67, 0x86, 0x13				
                END