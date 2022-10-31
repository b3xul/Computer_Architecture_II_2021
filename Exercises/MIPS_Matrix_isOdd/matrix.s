; Calcolare v3[i][j] = v1[i][j] * v2[i][j];		v5[i][j] = v3[i][j] * v4[i][j]; con i,j da 0 a 5 (uso solo i e la faccio scorrere da 0 a 25)

    .data
v1: .double 98.24, -87.38, 39.19, 21.16, 0.16
	.double 67.49, 26.33, -4.02, -2.31, 33.76
	.double 35.84, 33.73, -58.06, 12.39, -13.45
	.double 67.05, -51.16, 40.17, 69.95, 90.03
	.double -0.53, 12.93, -29.16, -5.05, -13.27
v2: .double 43.15, -6.06, -82.93, -59.52, -58.61
	.double -45.81, -42.68, -89.14, 74.82, -14.93
	.double -9.22, 19.61, -48.87, -4.97, 35.42
	.double 42.63, -63.28, -34.02, 5.17, -78.54
	.double 25.06, 84.03, -42.9, -85.8, 97.86
v4: .double 82.73, 54.68, 79.37, 44.48, 40.33
	.double 30.86, 79.31, -99.52, -51.18, -0.8
	.double -99.41, -70.41, -23.14, -97.11, -7.01
	.double 40.27, -63.74, -71.12, -12.37, 35.56
	.double -1.95, -74.83, 5.3, -63.41, -3.65
			
v3: .space 200	;senza overflow 64 bit per cella, 8B * (5*5) elementi = 200B
				;Considerando l'overflow ogni casella dovrebbe contenere un valore potenzialmente a 128 bit, quindi dovrei riservare 16 Bytes * (5*5) elementi = 400 Bytes 
v5: .space 200	;Considerando l'overflow ogni casella dovrebbe contenere un valore potenzialmente a 192 bit, quindi dovrei riservare 24 Bytes * (5*5) elementi = 600 Bytes

    .code
main:
	;***Inizializzo Registri
	daddi r6,r0,0	;r6 puntatore v1,v2,v3,v4,v5 da 0-200, incrementando di 8B man mano
	daddi r7,r0,200	;r7 valore di uscita

next:
	;***Carico variabili dalla memoria ai registri
	l.d f1, v1(r6)	;f1 = v1[i]
	l.d f2, v2(r6)	;f2 = v2[i]
	l.d f4, v4(r6)	;f4 = v4[i]
	mul.d f3,f1,f2	;f3 = v3[i] = v1[i]*v2[i]
	s.d f3, v3(r6)
	mul.d f5,f3,f4	;f5 = f5[i] = v3[i]*v4[i]
	s.d f5, v5(r6)
	
	daddi r6,r6,8	;Faccio scorrere puntatore r6
	bne r6,r7,next	;Ripeto il loop se r6!=r7 (non ho ancora finito di elaborare gli elementi del vettore)

	halt	;Termino l'esecuzione
