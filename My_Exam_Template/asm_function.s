				AREA asm_function, CODE, READONLY
				EXPORT count_negative_and_odd
					
count_negative_and_odd
				MOV r12, sp
				STMFD sp!, {r4-r8, r10-r11, lr}
				
				LDR R7, =0x80000001
				EOR R4, R4	;index
				EOR R5, R5	;counter
loop			TEQ R4, R1	;index==n?
				BEQ exit
				
				LDR R6, [R0]	;R6=vett[i]
				AND R8, R6, R7	;test first and last bit -> R6 AND 10..01 ->NE: NEGATIVE AND ODD
				CMP R8, R7
				ADDEQ R5, R5, #1
				
				ADD R0, R0, #4	;INT V[]=4 Bytes!!!
				ADD R4, R4, #1
				B loop

exit			LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END