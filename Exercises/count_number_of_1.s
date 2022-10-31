				AREA asm_functions, CODE, READONLY				
                EXPORT  ASM_function

ASM_function
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   R12, SP
				; save volatile registers
				PUSH {R4-R8,R10-R11,LR}				

				MOV R4, R0
				MOV R5, #1
				EOR R6, R6
		
init_loop		TST R4, R5			;R4 AND R5 != 0 THEN BIT=1
				ADDNE R6, R6, #1
				LSL R5, #1
				
				TEQ R5, #0
				BNE init_loop

				MOV R0, R6
end_asm			
				; restore volatile registers
				POP {R4-R8,R10-R11,PC}
				
                END