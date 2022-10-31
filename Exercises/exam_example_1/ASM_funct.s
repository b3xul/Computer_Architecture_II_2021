				AREA asm_functions, CODE, READONLY				
                EXPORT  ASM_divisible
ASM_divisible
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
init_loop
				; the use of conditional instructions is strongly advised
				cmp r0, r1
				subge r0, r0, r1
				bge init_loop

end_asm			
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END