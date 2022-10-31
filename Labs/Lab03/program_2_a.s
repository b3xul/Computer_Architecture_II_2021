;v5[i] = (v1[i] - v2[i]) * v3[i];	v6[i] = v5[i]*v3[i]; v7[i] =(v6[i] + v4[i]) * v2[i]; per 30 elementi

	.data
v1: .double 98.24, -87.38, 39.19, 21.16, 0.16
	.double 67.49, 26.33, -4.02, -2.31, 33.76
	.double 35.84, 33.73, -58.06, 12.39, -13.45
	.double 67.05, -51.16, 40.17, 69.95, 90.03
	.double -0.53, 12.93, -29.16, -5.05, -13.27
	.double 17.7, 20.52, 37.28, -62.14, 6.94
v2: .double 43.15, -6.06, -82.93, -59.52, -58.61
	.double -45.81, -42.68, -89.14, 74.82, -14.93
	.double -9.22, 19.61, -48.87, -4.97, 35.42
	.double 42.63, -63.28, -34.02, 5.17, -78.54
	.double 25.06, 84.03, -42.9, -85.8, 97.86
	.double -33.84, -7.25, -14.5, -45.55, -37.12
v3: .double 51.5, 54.27, -52.24, 0.6, -54.75
    .double 43.64, -76.8, 43.11, 70.16, 3.55
    .double 77.59, -12.61, -74.67, -42.03, 4.45
    .double 45.12, 0.34, -73.18, 84, 1.58
    .double 57.12, -0.84, -73.04, 62.17, -26.28
	.double 44.86, -15.15, -64.26, 21.72, 21.95
v4: .double 82.73, 54.68, 79.37, 44.48, 40.33
	.double 30.86, 79.31, -99.52, -51.18, -0.8
	.double -99.41, -70.41, -23.14, -97.11, -7.01
	.double 40.27, -63.74, -71.12, -12.37, 35.56
	.double -1.95, -74.83, 5.3, -63.41, -3.65
	.double -54.35, -15.49, 21.17, 24.02, 9.69

v5: .space 240	;No overflow: 8B*30=240B
v6: .space 240
v7: .space 240

; -:RAW s:structural S:WAW

	.code
main:
	daddi r8,r0,0	;r8 puntatore v1,v2,v3,v4,v5,v6,v7 da 0-240, incrementando di 8B man mano FDEMW  5
	daddi r9,r0,240	;r9 valore di uscita                                                       FDEMW 1
	
next:
	l.d f1, v1(r8)	;f1 = v1[i]                   FDEMW                                              1
	l.d f2, v2(r8)	;f2 = v2[i]                    FDEMW                                             1
	l.d f3, v3(r8)	;f3 = v3[i]                     FDEMW                                            1
	;RESCHEDULING: invertito sub.d e l.d f4
	sub.d f5,f1,f2	;f5 = v1[i]-v2[i]                FDaaaaMW                                        4
	l.d f4, v4(r8)	;f4 = v4[i]                       FDEMW                                          0
	mul.d f5,f5,f3 	;f5 = (v1[i]-v2[i])*v3[i]          FD--SmmmmmmmmMW                               9 (winmips 8)
	s.d f5,v5(r8)	;                                   F---DE------sMW                              1
	
	mul.d f6,f5,f3 	;f6 = (v1[i]-v2[i])*v3[i]*v3[i]      ---FD------mmmmmmmmMW                       7
	s.d f6,v6(r8)   ;                                        F------DE------sMW                      1
	
	add.d f7,f6,f4	;f7 = (v6[i]+v4[i])                       ------FD------aaaaMW                   3
	mul.d f7,f7,f2	;f7 = (v6[i]+v4[i])*v2[i]                        F------D---mmmmmmmmMW           8
	s.d f7,v7(r8)   ;                                                 ------F---DE------sMW          1
	
	daddi r8,r8,8   ;                                                        ---FD-------EMW         1
	bne r8,r9,next  ;                                                            F--------DEMW       2
	halt            ;                                                             F--------DEMW      1
                    ;                                                               TOT=6cc+(41cc*30)=1236cc
					;                                                      TOT(winmips)=6cc+(40cc*30)=1206cc
