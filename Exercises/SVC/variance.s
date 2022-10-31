				AREA asm_functions, CODE, READONLY				
                EXPORT  variance
variance				
				; save volatile registers
				PUSH {R4-R8,R10-R11,LR}

				;R0=ADDR(V)
				;R1=N
				
				;Controllo DIVIDE by ZERO
				CMP R1, #0
				MOVEQ R0, #0xFFFF
				BEQ fine
				
				EOR R4, R4 ;R4=contatore da 0 a N-1
				EOR R6, R6 ;R6=accumulatore media
media			LDR R5, [R0, R4, LSL #2]	;R5=V[i]

				ADDS R6, R6, R5
				;Controllo che la somma unsigned non faccia scattare il flag di carry, ossia che il risultato non superi i 32 bit
				MOVCS R0, #0xFFFF
				BCS fine
				
				ADD R4, #1
				CMP R4, R1
				BNE media
				
				UDIV R6, R6, R1 ;R6=totale/N=media
				
				EOR R4, R4 ;R4=contatore da 0 a N-1
				EOR R8, R8 ;R8=accumulatore varianza
varianza		LDR R5, [R0, R4, LSL #2]	;R5=V[i]

				SUB R7, R5, R6	;R7=(V[i]-media)
				SMULL R7, R9, R7, R7	;R7=(V[i]-media)*(V[i]-media)
				;Controllo che il prodotto signed non faccia scattare il flag di overflow, ossia che il risultato non superi i 32 bit
				CMP R9, #0
				MOVNE R0, #0xFFFF
				BNE fine
				
				ADDS R8, R8, R7
				;Controllo che la somma unsigned non faccia scattare il flag di carry, ossia che il risultato non superi i 32 bit
				MOVCS R0, #0xFFFF
				BCS fine
				
				ADD R4, #1
				CMP R4, R1
				BNE varianza
				
				UDIV R8, R8, R1 ;R8=varianza
			
				MOV R0, R8	;Valore di ritorno
				
				; restore volatile registers
fine			POP {R4-R8,R10-R11,PC}
				
                END