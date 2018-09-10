/*
 * Nom: main.cpp
 * Equipe: 76
 * Description: Reception UART
 */


#include <memoire_24.h>
#include <constantes.h>

int main(){
	
	//initialisations et instanciations
	Memoire24CXXX memoire;
    
	uint8_t NOMROBOT[3] = "BS";
	uint8_t SESSION[5] = "18-1";
	uint8_t NUMEROEQUIPE[3] = "76";
	
	//ecriture en bloc
	uint8_t adresse = 0x00;

	//bool mode logiciel = 0
	memoire.ecriture(adresse++, 0x00);
	
	memoire.ecriture(adresse++, 0xf0);
	_delay_ms(5);
	memoire.ecriture(adresse, NOMROBOT, 2);
	_delay_ms(10);
	adresse += 2;
	
	memoire.ecriture(adresse++, 0xf1);
	_delay_ms(5);
	memoire.ecriture(adresse, NUMEROEQUIPE, 2);
	_delay_ms(10);
	adresse+=2;
		
	memoire.ecriture(adresse++, 0xf2);
	_delay_ms(5);	
	memoire.ecriture(adresse++, 3);
	_delay_ms(5);
	
	memoire.ecriture(adresse++, 0xf3);
	_delay_ms(5);
	memoire.ecriture(adresse, SESSION, 4);
	_delay_ms(20);
	adresse+=4;
	
	memoire.ecriture(adresse++, 0xf4);
	_delay_ms(5);
	memoire.ecriture(adresse++, 1);
	_delay_ms(5);
	
	memoire.ecriture(adresse, 0xff);
	_delay_ms(5);
	
	return 0;
}
