extern unsigned int variance(unsigned int*, unsigned int);

#define N 6

int main(void){

	/*unsigned int V[N]={1,2,2,2,10,4294967286}; -> set carry bit nella somma*/
	/*unsigned int V[N]={1,715827882,715827882,715827882,715827882,715827882}; -> overflow 32 bit nella smull*/
	
	unsigned int V[N]={1,2,2,2,10,20};
	volatile unsigned int varianza=0;
	
	/*varianza = variance(V, 0); -> Divide by zero*/
	varianza = variance(V, N);
	
	while(1);
}
