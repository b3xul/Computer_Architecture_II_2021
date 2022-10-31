				AREA asm_functions, CODE, READONLY				
                EXPORT  ASM_divisible
ASM_divisible
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   R12, SP
				; save volatile registers
				PUSH {R4-R8,R10-R11,LR}				
init_loop
				; the use of conditional instructions is strongly advised
				CMP R0, R1
				SUBGE R0, R0, R1
				BGE init_loop

end_asm			
				; restore volatile registers
				POP {R4-R8,R10-R11,PC}
				
                END