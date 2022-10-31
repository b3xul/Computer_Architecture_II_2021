; Calcolare while (b[i] > 0) {if (isOdd(b[i])) {res[i] = res[i] + a[i];}	a[i] = a[i] * 2; 	b[i] = b[i] / 2;}

    .data
a: .byte 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 0
b: .byte 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 0, 3

res: .space 30	;Senza considerare overflow ogni casella dovrebbe contenere un valore potenzialmente a 8 bit, quindi dovrei riservare 1 Byte * 30 elementi = 30 Bytes 

    .code
main:
	;***Inizializzo Registri
	daddi r6,r0,0	;r6 puntatore a,b incrementato di 1B ogni volta
	daddi r7,r0,30	;r7 valore di uscita

for:
	;***Carico variabili dalla memoria ai registri
	lb r1, a(r6)	;r1 = a[i]
	lb r2, b(r6)	;r2 = b[i]
	xor r3,r3,r3	;r3 = res[i]
					
while:
	slt r4,r0,r2	;if( b[i]>=0 ) r4=1 (r4 = 1 -> continuo nel while)
	beqz r4,increment
	
	andi r5,r2,1	;r5=r2 AND 0000 0001 (r5 = isOdd)
	beqz r5,common_part	;Se isOdd=0 non aggiorno res[i]
	daddu r3,r3,r1	;update r3
	
common_part:
	dsll r1,r1,1	;r1 = r1*2
	dsrl r2,r2,1	;r2 = r2/2
	sb r1,a(r6)
	sb r2,b(r6)
	sb r3,res(r6)
	j while

increment:
	daddi r6,r6,1	;Faccio scorrere puntatore r6
	bne r6,r7,for	;Ripeto il loop se r6!=r7 (non ho ancora finito di elaborare gli elementi del vettore)

	halt	;Termino l'esecuzione