				
				
				AREA asm_functions, CODE, READONLY				
                EXPORT  ASM_funct
ASM_funct
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}	;PUSH
				; extract argument 4 and 5 into R4 and R5
				LDR   r4, [r12]
				LDR   r5, [r12,#4]
				
				add	  r5, r4, r5
				; setup a value for R0 to return
				
				MOV	  r0, r5
				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}	;POP
				
                END