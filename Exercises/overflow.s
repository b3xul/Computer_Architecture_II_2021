AREA asm_func, CODE, READONLY
				EXPORT overflow
					
overflow        MOV r12, sp
				STMFD sp!, {r4-r8, r10-r11, lr}
				
				EOR R4, R4
				EOR R5, R5
loop			TEQ R4, R1
				BEQ clean
				
				LDR R6, [R0]
				ADDS R5, R5, R6
				MOVVS R0, #0
				BVS exit
				MOVCS R0, #1
				BCS exit
				
				ADD R0, R0, #4	;INT=4 Bytes!!!
				ADD R4, R4, #1
				B loop
				
clean			MOV R0, #2

exit			LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END