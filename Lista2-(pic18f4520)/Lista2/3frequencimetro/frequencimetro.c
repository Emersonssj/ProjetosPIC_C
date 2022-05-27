#include <p18f4520.h>

#define sinal PORTAbits.RA6 

unsigned char converte_BCD [100] = {
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,
	0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,
	0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,
	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,
};

char delay(void){

	unsigned int i;
	for(i=0;i<4;i++){}
}


int mede_periodo(void){

	int contador=0;
	while(sinal){} //sem receber nada
	while(!sinal){} //sem receber nada
	while(sinal){ // recebendo algum valor
		
		delay();
		contador++;
	}
	while(!sinal){ //recebendo algum valor
		
		delay();
		contador++;
	}
	return contador;
}

int calcula_freq(int contador){
    double a = 1;
    double b = (double)contador;
    double calc = ((a / b)* 10000);
    int calculo = (int)calc;
	return calculo;
}

char mostrar(char freq){
	if(freq > 99){
		PORTC = 0xEE;
	}else if(freq <= 10){
		PORTC = converte_BCD[10];
	}else{
		PORTC = converte_BCD[freq];
	}
}
main(){

	ADCON1 = 0x0F; // Desliga portas anal�gicas
	TRISC = 0b00000000;  // Display 7 segmentos como sa�da nas portas C
	TRISAbits.RA6 = 1; 
	delay();
	while(1){
		mostrar(calcula_freq(mede_periodo()));
	}
}