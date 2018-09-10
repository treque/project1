/*
 * Nom: transmissionUART.cpp
 * Equipe: 76
 * Description: Fonctions permettant de manipuler les donnees dans la memoire du robot
 */
#include "transmissionUART.h"

/* Fonction permettant d'initialiser les registres pertinents a la manipulation de la memoire */
void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premier registres pour vous éviter des complications

	UBRR0H = 0;

	UBRR0L = 0xCF;

// permettre la reception et la transmission par le UART0

	UCSR0A |= 1 << UDRE0;

	UCSR0B |= ( (1 << TXEN0) | (1 << RXEN0));

// Format des trames: 8 bits, 1 stop bits, none parity

	UCSR0C |= ((1 << UCSZ10)  | (1 << UCSZ00));

}

/* Fonction permettant de transferer des donnees vers la console
 * Param donnee: donnee a transferer 
 */
void transmissionUART ( uint8_t donnee ) {

/* Wait for empty transmit buffer */
	 if( !( UCSR0A & (1<<UDRE0)) );
	 /* Put data into buffer, sends the data */
	 UDR0 = donnee;

}

/* Fonction permettant de lire ce qui se trouve dans la memoire et de le transferer a la console */
void lectureMemoire(){
	uint8_t adresse = 0x01;
	uint8_t* lecture = 0x00;
	Memoire24CXXX memoire;
		
	while(*lecture != 0xFF) {	
		memoire.lecture(adresse, lecture);
		_delay_ms(5);
		transmissionUART ( *lecture );
		adresse++;
	}		
}

unsigned char receptionUART( void )
{
	 /* If no data is received return 0xff */
	 if( !(UCSR0A & (1<<RXC0)) ) {
		 return 0xff;
	 }
	 else {
		/* Get and return received data from buffer */
		return UDR0;
	}
}
