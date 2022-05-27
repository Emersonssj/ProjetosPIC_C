#include<p18f4520.h>

#define BOTAOM PORTAbits.RA0
#define BOTAOH PORTAbits.RA1
#define BOTAO PORTAbits.RA2
#define BUZZER PORTEbits.RE0

int i;
unsigned char dezena, d_alarme = 0;
unsigned char unidade, u_alarme = 0;
unsigned char unidade_m, um_alarme = 0;
unsigned char dezena_m, dm_alarme = 0;
unsigned char unidade_h, uh_alarme = 0;
unsigned char dezena_h, dh_alarme = 0;
unsigned char aux,aux_alarme,extra = 0;

void contador(void){
    if(++unidade >= 10){
        unidade = 0;
        if(++dezena >= 6){
            dezena = 0;
            unidade_m++;
        }
        if(unidade_m >= 10){
            unidade_m = 0;
            if(++dezena_m >= 6){
                dezena_m = 0;
                unidade_h++;
            }
        }
        if(unidade_h >= 10){
            unidade_h = 0;
            dezena_h++;
        }
        if(dezena_h >= 2 & unidade_h >= 4){
            dezena_h = 0;
            unidade_h = 0;
        }
    }
}

void mostra_contador(){
    unsigned char BCD, BCD_m, BCD_h, aux;
    
    /*
        unidade = 0b00000000;
        dezena = 0b000000101; <<4 0b01010000;
        
        máscara de bits 
        0b01010000 -> 50;
        0b00000000 -> 00;
        ______
        0b01010000 -> 50 bcd
        
    */
    
    
    BCD = (dezena<<4 | unidade);
    LATC = BCD;
    BCD_m = (dezena_m<<4 | unidade_m);
    LATD = BCD_m;
    BCD_h = (dezena_h<<4 | unidade_h);
    LATB= BCD_h;
}

void delay_s(unsigned int segundos){
    unsigned short long i;
    for(i = 0; i < 50000; i++){}
}

void change(void){
	
	if(BOTAOM == 1 && aux_alarme == 0){
			if(unidade_m < 9){
				unidade_m++;
			}
			else if(unidade_m >= 9){
				unidade_m = 0;
				dezena_m++;
			}
			else if(dezena_m >= 9){
				dezena_m = 0;
			}
		}
	
	if(BOTAOH == 1 && aux_alarme == 0){
		if(unidade_h < 9){
			unidade_h++;
		}
		else if(unidade_h >= 9){
			unidade_h = 0;
			dezena_h++;
		}
		else if(dezena_h > 2){
			dezena_h = 0;
		}
	}

	if(BOTAOM == 1 && aux_alarme == 1){
			if(um_alarme < 9){
				um_alarme++;
			}
			else if(um_alarme >= 9){
				um_alarme = 0;
				dm_alarme++;
			}
			else if(dm_alarme >= 9){
				dm_alarme = 0;
			}
		}
	
	if(BOTAOH == 1 && aux_alarme == 1){
		if(uh_alarme < 9){
			uh_alarme++;
		}
		else if(uh_alarme >= 9){
			uh_alarme = 0;
			dh_alarme++;
		}
		else if(dh_alarme > 2){
			dh_alarme = 0;
		}
	}
}

void alarme_config(void){
	LATC = (d_alarme<<4 | u_alarme);
    LATD = (dm_alarme<<4 | um_alarme);
    LATB = (dh_alarme<<4 | uh_alarme);
	extra = 1;
}

void som_alarme(void){
	if (dm_alarme == dezena_m && um_alarme == unidade_m && dh_alarme == dezena_h && uh_alarme == unidade_h && aux_alarme == 0 && extra == 1){
		BUZZER = 1;
	}
}

void main(void){
	ADCON1 = 0b00001111;
	TRISA = 0xFF;
    TRISB = 0b00000000; //Saída B
    TRISC = 0b00000000; //Saída C
    TRISD = 0b00000000; //Saída D
    TRISE = 0b00000000; //Saída E

    while(1){
		contador();
		if(BOTAO == 1){
			delay_s(1);
			delay_s(1);
			if(BOTAO == 1){
				aux_alarme = 1;
		}
			else{aux_alarme = 0;}

	}
		if(aux_alarme == 1){
			alarme_config();
	}
		else{mostra_contador();}
		change();
		som_alarme();
		delay_s(1);
  }
}