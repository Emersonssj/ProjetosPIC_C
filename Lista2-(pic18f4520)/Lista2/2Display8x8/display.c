#include <p18f4520.h>

int ponteiro;
int coluna;

unsigned char mensagem[] = {

// Espaços
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,

// E
0b11111111,
0b11111111,
0b01111110,
0b01100110,
0b01100110,
0b00000000,
0b00000000,

// M
0b11111111,
0b00000000,
0b11111001,
0b11110011,
0b11110011,
0b11111001,
0b00000000,

// E
0b11111111,
0b01100110,
0b01100110,
0b01100110,
0b00000000,
0b00000000,

// R
0b00111111,
0b00011001,
0b10000110,
0b11100110,
0b11100110,
0b00000000,
0b00000000,

0b11111111,

// S
0b11001101,
0b10000110,
0b00110010,
0b00110010,
0b00110010,
0b00011000,
0b10011100,

// O
0b11111111,
0b00000000,
0b00111100,
0b00111100,
0b00111100,
0b00000000,
0b00000000,

0b11111111,

// N
0b00000000,
0b10011111,
0b11100111,
0b11111001,
0b00000000,
0b11111111,
0b11111111,

// Espaços
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,

};

void delay_varredura(void){

	int i;
	for(i=0;i<800;i++){}
}

void mostrar(void){
	
	for(ponteiro=0;ponteiro < 54; ponteiro++){
			for(coluna=0;coluna < 8; coluna++){
				if(coluna <= 7){
					PORTD = 0b10000000 >> coluna;
				}else{
					PORTD = 0b10000000 >> coluna-6;
				}
				PORTC = (mensagem[ponteiro+coluna+7]);
				PORTB = (mensagem[ponteiro+coluna]);
				delay_varredura();
	 	
			}
	}
}

main(){

	TRISD = 0; // Varredura do painel 1 e 2
	TRISC = 0; // Barramento do painel 1
	TRISB = 0; // Barramento do painel 2
	ADCON1 = 0b00001111;

	while(1){

		mostrar();
	}
}