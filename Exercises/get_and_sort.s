				AREA asm_functions, CODE, READONLY				
                EXPORT  get_and_sort

get_and_sort
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   R12, SP
				; save volatile registers
				PUSH {R4-R8,R10-R11,LR}			
				
				
				AND R1, R1, #0x00FF0000
				LSR R1, R1, #16
				SUB R2, R2, #1	;size to index
				EOR R4, R4	;index
				EOR R5, R5	;vett[i]
				EOR R6, R6	;tmp
				EOR R8, R8	;flag piazzato
				
loop			TEQ R4, R3
				BEQ exit
				LDRB R5, [R0, R4]
				
				CMP R1, R5	;VAL>=VETT[i]?
				MOVGE R8, #1
				STRBGE R1, [R0, R4]
				BGE scorri
				ADD R4, R4, #1
				B loop
				
scorri			ADD R4, R4, #1
				LDRB R6, [R0, R4]
				STRB R5, [R0, R4]
				MOV R5, R6
				TEQ R4, R2
				BNE scorri
				
exit			TEQ R8, #0
				STRBEQ R1, [R0, R4]
				
				MOV R1, R0
				; restore volatile registers
				POP {R4-R8,R10-R11,PC}
				
                END