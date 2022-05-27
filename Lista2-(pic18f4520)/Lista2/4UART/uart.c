#include <p18f4520.h>
#pragma config OSC=INTIO67
#define tx PORTCbits.RC0
#define rx PORTCbits.RC1

char dadoE[8];

void delay(){        // (1/1200) = 833,33us - tempo de 1 bit
	 unsigned int i;
	for(i=0; i<10; i++){}
}

void delay_meiobit(){        // (1/1200) = (833,33)/2us - tempo de 0,5 bit
	 unsigned int i;
	for(i=0; i<4; i++){}
}

void transmiti_serial(char dado[]){
	int j;
	
 	tx = 1; // repouso
	delay();
	tx = 0; // start 
	delay();

	for(j=0;j<8;j++){
		tx = dado[j];
		delay();
	}

	tx = 1; // stop
	delay(); 

}

char recebe_serial(void){

	int i;

	while(rx){}
	delay_meiobit();
	delay();
	for(i=0;i<8;i++){

		dadoE[i] = rx;
		delay();
	}
	
	rx = 1;
	delay(); 

	return dadoE;
}

main(){
	TRISCbits.RC0 = 0; //TX - SAIDA
	TRISCbits.RC1 = 1; //RX - ENTRADA


	delay();
	delay_meiobit();

	while(1){
		transmiti_serial(recebe_serial());

	}

}
