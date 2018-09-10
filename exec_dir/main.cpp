/*
 * Nom: main
 * Equipe: 76
 * Description: Gestionnaire logiciel et parcours
 */

#include <memoire_24.h>
#include <transmissionUART.h>
#include <constantes.h>
#include <robot.h>

volatile bool interrupt = false;
volatile bool logiciel = true;


void initialisation ( void ) {

	// Pour empecher les interruptions
	cli();
	
	// MOTEURS : timer1
    DDRD = 0xF0;
    PORTD &= 0x3f;
    // comparateurs a 0
    OCR1A = 0;
    OCR1B = 0;
    // mode phase correct 8 bit
    TCCR1A |= (1 << WGM10);
    // prescaler a 8
    TCCR1B |= (1 << CS11);
    // timer a 0
    TCNT1 = 0;
    // force output compare on channel sur les deux MSB
    TCCR1C = 0;
    
    
    // PIEZO : timer0
    DDRB = 0xFF;
    PORTB = 0xF0;
    // comparateur a 0
    OCR0A = 0;
    // mode
    TCCR0A = 0;
    // prescaler a 256
    TCCR0B |= (1 << CS02);
    // timer a 0
    TCNT0 = 0;
    
	// DEL & CAPTEURS
	DDRA = 0x0F;
	
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC01) | (1 << ISC00);
	
	// Pour permettre les interruptions
	sei();
	
}

// C'est une routine d'interruption qui change la variable interrupt
// pour effectuer un virage de 180 degres.
ISR (INT0_vect) {
	if(!logiciel)
		interrupt = true;
}

int main(){
	
	initialisation();
	initialisationUART();	
	
	Memoire24CXXX memoire;	
	uint8_t* logicielLu = 0x00;
	memoire.lecture(0x00, logicielLu);
	_delay_ms(5);
	
	// A l'adresse 0x00 se trouvent les octets qui determinent
	// si nous sommes dans le mode logiciel (0x00) ou parcours (0x01)
	if(*logicielLu == 0x00) {
		logiciel = true;
		memoire.ecriture(0x00, 0x01);
		_delay_ms(5);
	}
	else if (*logicielLu == 0x01) {
		logiciel = false;
		memoire.ecriture(0x00, 0x00);
		_delay_ms(5);
	}

	//changement de mode 
	//Mode Logiciel diagnostic
	if(logiciel) {	
		
		DEL del;
		Capteur capteurDroite(Droite);
		Capteur capteurGauche(Gauche);
		uint8_t commande, operande, dataRecu;
		bool instructionValide = false;
		int compteur = 0; 
		bool interruptionRelachee = true;
		
		while(1) {
			//Mise a jour des distances des capteurs gauche et droit, et de
			//l'etat du bouton de l'interruption
			//Il faut separer la transmission des informations, ou la transmission
			//ne se fait pas
			//Chaque information se transmet a tous les 10 ms
			if(compteur == 10) {
				//Distance du capteur gauche
				transmissionUART(DISTANCEGAUCHE);
				transmissionUART(capteurGauche.obtenirDistance());
				
			}
			else if(compteur == 20) {
				//Distance du capteur droit
				transmissionUART(DISTANCEDROITE);
				transmissionUART(capteurDroite.obtenirDistance());
				
			}
			else if(compteur == 30) {
				//Etat du bouton Interrupt
				if(PIND & 0x04) {
					interruptionRelachee = false;
				}
				else {
					interruptionRelachee = true;
				}
				transmissionUART(ETATINTERRUPT);
				transmissionUART(interruptionRelachee);
				//Reinitialisation du compteur
				compteur = 0;
			} 
					
			//Verification de l'instruction
			dataRecu = receptionUART();
			if(dataRecu >= 0xf8 && dataRecu <= 0xfb) {
				//les commandes etant toujours entre cette intervalle
				commande = dataRecu;
			}
			else if(dataRecu !=0xff) {
				//0xff etant un retour bidon, qui nous est donne lorsque le 
				//logiciel ne nous envoie rien (voir fonction receptionUART())
				operande = dataRecu;
				//pour nous permettre de rentrer dans le switch-case
				instructionValide = true;
			}
			

			
			if(instructionValide) {
				instructionValide = false;
				switch (commande){
					//Changer la vitesse de la roue gauche		
					case VITESSEROUEGAUCHE:
						if ( operande >> 7 ) { 		//si la vitesse est negative,
													//alors le premier bit est un 1
							PORTD |= (1<<7);		//on inverse le sens
							operande = ~(operande - 1);		// valeur absolue
															//de l'operande
						}
						else {
							PORTD &= 0x7F;					
						}
						switch (operande) {
							case 0:
								ajustementPWMGauche(255);
								break;
							case 25:
								ajustementPWMGauche(192);
								break;
							case 50:
								ajustementPWMGauche(128);
								break;
							case 75:
								ajustementPWMGauche(64);
								break;
							case 100:
								ajustementPWMGauche(0);
								break;
						}
						break;
					//Changer la vitesse de la roue droite
					case VITESSEROUEDROITE:
						if ( operande >> 7 ) { 		//si la vitesse est negative
							PORTD |= (1<<6);
							operande = ~(operande -1);		
						}
						else {
							PORTD &= 0xBF;
						}
						
						switch (operande) {
							case 0:
								ajustementPWMDroit(255);
								break;
							case 25:
								ajustementPWMDroit(192);
								break;
							case 50:
								ajustementPWMDroit(128);
								break;
							case 75:
								ajustementPWMDroit(64);
								break;
							case 100:
								ajustementPWMDroit(0);
								break;
						}	
						break;
					//Changer la couleur de la DEL
					case COULEURDEL:
						switch (operande){
							case COULEURDELETEINT:
								del.eteindre();
								break;
							case COULEURDELVERT:
								del.afficherVert();
								break;
							case COULEURDELROUGE:
								del.afficherRouge();
								break;
						}
						break;
					//Envoyer les infos
					case REQUETE:
						lectureMemoire(); //infos d'identification dans la memoire du robot
						break;		
				}
			}
			_delay_us(500);
			compteur++;
		}
	}
	
	//Mode parcours
	else {
		Robot robot;
		
		while(true) {
			
			robot.verifierEtat();
			if(interrupt) {
				if(robot.obtenirEtat() == SUIVREDROITE) {
					robot.faire180(Gauche);
					robot.arreter();
					robot.modifierEtat(SUIVREGAUCHE);
					robot.boost();
				}
				else if(robot.obtenirEtat() == SUIVREGAUCHE) {
					robot.faire180(Droite);
					robot.arreter();
					robot.modifierEtat(SUIVREDROITE);
					robot.boost();
				}
				interrupt = false;
			}
			else {
				switch(robot.obtenirEtat()) {
					case START:
						break;
						
					case TOURNERDROITE:
						robot.changerCote(Droite);
						break;
					
					case SUIVREDROITE:
						robot.ajuster(Droite);
						break;
					
					case TOURNERGAUCHE:
						robot.changerCote(Gauche);
						break;
			
					case SUIVREGAUCHE:
						robot.ajuster(Gauche);
						break;
				}
			}
		}
	}
	
	return 0;					
}

