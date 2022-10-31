				AREA asm_functions, CODE, READONLY				
                EXPORT  duty_cycle
duty_cycle
;												R0								R1							R2								R3
;extern unsigned char duty_cycle(unsigned char valore_iniziale, unsigned int tempo_totale, unsigned int tempi_variazioni[], unsigned char numero_variazioni);
				;R4=t_a, R5=t_b, R6=index, R7=position, R8=valore_iniziale, return R0=t_1/t_tot
				;if(valore_iniziale==0) At_0=t_var[0]+t_var[2]-t_var[1]...
				;						Bt_1=         t_var[1]-t_var[0]+ t_var[3]-t_var[2]...
				;						
				;if(valore_iniziale==1) At_1=t_var[0]+t_var[2]-t_var[1]...
				;						Bt_0=		 t_var[1]-t_var[0]+ t_var[3]-t_var[2]...

				
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   R12, SP
				; save volatile registers
				PUSH {R4-R8,R10-R11,LR}
				
				CMP R3,#0
				BEQ end_asm
				
				LDR R4, [R2]	;R4=T_A
				
				CMP R3,#1
				BEQ calc
				
				
				EOR R5, R5
				SUB R3,#1
				MOV R6,#1
				MOV R7, R2	;R7=pointer
				MOV R8, R0	;R8=valore_iniziale
				
				
init_loop		
				; the use of conditional instructions is strongly advised
				
				TST R6,#1
				LDRNE R9,[R7, #4]
				ADDNE R5, R9	;t_a+=tv[1,3,5..]
				LDRNE R9, [R7]
				SUBNE R5, R9	;t_a-=tv[0,2,4..]
				
				CMP R6, R3
				ADDNE R6,R6,#1
				ADDNE R7,R7,#4
				BNE init_loop
				
calc			CMP R8,#0	;EQ->VAL_INIZIALE=0 NE->VAL_INIZIALE=1
				MOVEQ R5, R1
				SUBEQ R5, R4
				MOVNE R5, R4
				
				;R5=t_1
				MOV R6, #100
				MUL R5, R5, R6
				UDIV R0, R5, R1
				
				
end_asm			
				; restore volatile registers
				POP {R4-R8,R10-R11,PC}
				
                END