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


;	daddi r6,r0,0	;FDEMW                      5
;	daddi r7,r0,30	; FDEMW                     1
;
;for:                                          
;	lb r1, a(r6)	;  FDEMW                    1
;	lb r2, b(r6)	;   FDEMW                   1
;	xor r3,r3,r3	;    FDEMW                  1
;
;while:                                         
;	slt r4,r0,r2	;     FDEMW                 1
;	beqz r4,increment;     F-DEMW               2
;
;	andi r5,r2,1	;       -FDEMW              1
;	beqz r5,common_part	;     F-DEMW            2
;	daddu r3,r3,r1	;          -FDEMW           1
;
;common_part:                                   
;	dsll r1,r1,1	;            FDEMW          1
;	dsrl r2,r2,1	;             FDEMW         1
;	sb r1,a(r6)		;              FDEMW        1
;	sb r2,b(r6)		;               FDEMW       1
;	sb r3,res(r6)	;                FDEMW      1
;	j while			;                 FDEMW     1
;												(1)
;increment:                                     
;	daddi r6,r6,1	;                  FDEMW    1
;	bne r6,r7,for	;                   F-DEMW  2
;
;	halt			;					 -FDEMW	1	
;
; 6cc fissi in preparazione
; for esterno + increment = 7cc*30 iterazioni=210cc
; while interno con b=0 -> 0 volte, b=2,3 -> 2 volte, con b=4 -> 3 volte
; Il numero di while che viene eseguito è 0 per b=0, 2 per b=1, 2 per b=2,3 , 3 per b=4..7, 4 per b=8..15, 5 per b=16..31 etc.
; la slt e la beqz invece vengono eseguite una volta in più rispetto a tutte le istruzioni successive nel while
; Dato che b assume come valori 1 volta 0, 21 volte 2 o 3, 8 volte 4 il while verrà eseguito 0+21*2+8*3=42+24=66 volte
; Mentre la slt e la beqz verranno eseguite 1+21*3+8*4=1+63+32=96 volte
; La daddu verrà eseguita una volta si e una no a seconda se il b[i] in quel momento sia pari o dispari,
; ma dato che in entrambi i casi (branch taken o untaken) si userà 1 cc, è indifferente ai fini del calcolo
; Il while impiegherà quindi 3cc per slt e beqz(96 volte) + 1cc quando viene preso il branch (30 volte) + 10cc per il resto del while (66 volte) + 1cc per il jump (66 volte)
; = 3*96+1*30+10*66+1*66=1044cc
; In totale: 6+210cc+1044cc=1260cc