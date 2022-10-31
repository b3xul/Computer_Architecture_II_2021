
extern int ASM_funct(int, int, int, int, int, int);

int main(void){	/*PUSH {R1-R3,LR}*/

	int i=0xFFFFFFFF, j=2, k=3, l=4, m=5, n=6;	/*Compilatore assegna i=R4, j=R5, k=R6, l=R7, m=R8, n=R9 e fa MOV o sMOVS*/
	volatile int r=0;	/*Compilatore assegna r=R0 e fa MOVS r0, 0. N.B. Se non metto volatile il compilatore SOSTITUISCE quell'istruzione e la successiva che usa RO con NOP!!!
										 *Compilatore STR R0,[SP,#0x08]*/
	r = ASM_funct(i, j, k, l, m, n);	/*MOV      r3,r7 	| MOV      r2,r6 | MOV      r1,r5 | MOV      r0,r4
																		*STRD     r8,r9,[sp,#0] CARICA ENTRAMBI I DATI INSIEME SULLO STACK | BL.W     0x00000228 ASM_funct */
	j=r;
	while(1);
}
