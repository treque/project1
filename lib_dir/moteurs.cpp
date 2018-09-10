/*
 * Nom: moteurs.cpp
 * Equipe: 76
 * Description: Implementation des methodes de la classe moteur 
 */

#include "moteurs.h"

/* Constructeur par defaut de la classe Moteur
 */
Moteur::Moteur(){
}

void Moteur::boost(){
		ajustementPWMDroit(57);
		ajustementPWMGauche(57);
		_delay_ms(45);
}

/* Methode qui arrete les moteurs
 */
 void Moteur::arreter(){
		ajustementPWMDroit(255);
		ajustementPWMGauche(255);
}
	
	
/* Methode qui fait marcher les moteurs (le robot avance)
 * param vitesse : uint8_t indiquant la vitesse desiree
 */
void Moteur::avancer(uint8_t vitesse){
		PORTD &= 0x3f;
		boost();
		ajustementPWMDroit(vitesse);
		ajustementPWMGauche(vitesse);
}
	
/* Methode qui fait marcher les moteurs (le robot recule)
 * param vitesse : uint8_t indiquant la vitesse desiree
 */
void Moteur::reculer(uint8_t vitesse){
		PORTD |= (1<<6) | (1<<7);
		ajustementPWMDroit(vitesse);
		ajustementPWMGauche(vitesse);
}
	
/* Methode qui permet au robot a effectuer un virage de 90 degre a droite
 */
void Moteur::tournerDroite(Vitesse vitesse){
	PORTD &= 0x3f;
	if(vitesse == VITE){
		ajustementPWMGauche(125);
		ajustementPWMDroit(175);
	}
	else{
		ajustementPWMGauche(145);
		ajustementPWMDroit(180);
	}
}
	
/* Methode qui permet au robot a effectuer un virage de 90 degre a gauche
 */
void Moteur::tournerGauche(Vitesse vitesse){
	PORTD &= 0x3f;
	if(vitesse == VITE){
		ajustementPWMGauche(175);
		ajustementPWMDroit(125);
	}
	else{
		ajustementPWMGauche(180);
		ajustementPWMDroit(145);
	}
		
}

void Moteur::faire180(Direction direction) {
	if(direction == Droite) {
		ajustementPWMGauche(100);
		ajustementPWMDroit(220);
		_delay_ms(2000);
	}
	else {
		ajustementPWMGauche(220);
		ajustementPWMDroit(100);
		_delay_ms(2000);
	}
}
