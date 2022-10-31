; Calcolare c[i] = 4 *(a[i] + b[i]) e trovare max e min dell'array c

    .data
a: .word16 35, 82, -20, -27, 39, 32, -34, 20, -40, 94, 27, -89, 89, -39, 22, -94, 92, 42, -38, 60, 26, 85, -45, -14, -87, -79, 41, 81, 79, -29
b: .word16 -53, -54, 18, -29, 38, -16, 76, -57, -37, -62, -19, 87, 37, 57, 50, -22, 16, 82, 44, -10, -18, 37, 64, -12, -17, -85, 55, 9, 53, -42
c: .space 120	;Ogni casella deve contenere un valore potenzialmente a 32 bit, quindi devo riservare 4 Bytes * 30 elementi = 120 Bytes
max: .space 4
min: .space 4

    .code
main:
	;***Inizializzo Registri
	daddi r1,r0,0	;r1 puntatore a,b da 0-60
	daddi r2,r0,0	;r2 puntatore c da 0-120
	daddi r3,r0,60	;r3 valore di uscita

	;***Carico variabili dalla memoria ai registri
	lh r4, a(r1)	;r4 = a[i]
	lh r5, b(r1)	;r5 = b[i]
	dadd r6,r4,r5	;r6 = c[i] = (a[i] + b[i])
	dsll r6,r6,2	;r6 *= 4
	sw r6,c(r2)		;c[i] = r6 = 4*(a[i] + b[i])
	
	;***Inizializzo max e min con il primo valore, separandolo dal ciclo vero
	dadd r7,r0,r6	;r7 = max = r6
	dadd r8,r0,r6	;r8 = min = r6
	
	daddi r1,r1,2	;Faccio scorrere puntatore r1
	daddi r2,r2,4	;Faccio scorrere puntatore r2

next:
	;***Carico variabili dalla memoria ai registri
	lh r4, a(r1)	;r4 = a[i]
	lh r5, b(r1)	;r5 = b[i]
	dadd r6,r4,r5	;r6 = c[i] = (a[i] + b[i])
	dsll r6,r6,2	;r6 *= 4
	
	
	;***Valuto se aggiornare max
	slt r9,r7,r6	;if( max<c[i] ) r9=1
	bnez r9,update_max	;if( r9==1 ) update_max
	sw r6,c(r2)		;c[i] = r6 = 4*(a[i] + b[i]) (posso farlo qui se ho delay slot perchè non interferisce con il branch)
	
	;***Valuto se aggiornare min
	slt r10,r6,r8	;if( c[i]<min ) r10=1
	bnez r10,update_min	;if( r10==1 ) update_min
	
	
after_checks:
	daddi r1,r1,2	;Faccio scorrere puntatore r1 (posso farlo qui se ho delay slot perchè non interferisce con il branch)
	bne r1,r3,next	;Ripeto il loop se r1!=r3 (non ho ancora finito di elaborare gli elementi del vettore)
	daddi r2,r2,4	;Faccio scorrere puntatore r2 (posso farlo qui se ho delay slot perchè non interferisce con il branch)
	
	;***Salvo i risultati in memoria
	sw r7,max(r0)	;max=4*(79+53)=528=0x210
	sw r8,min(r0)	;min=4*(-79-85)=-656=0xfd70
	halt	;Termino l'esecuzione

update_max:
	j after_checks
	dadd r7,r0,r6	;(posso farlo qui se ho delay slot perchè non interferisce con il branch)
	
update_min:
	j after_checks
	dadd r8,r0,r6	;(posso farlo qui se ho delay slot perchè non interferisce con il branch)

