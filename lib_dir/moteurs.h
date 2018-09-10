/*
 * Nom: moteurs.h
 * Equipe: 76
 * Description: Definition de la classe moteur
 */

#include <PWM.h>
#include "constantes.h"

#ifndef MOTEURS_H
#define MOTEURS_H
class Moteur {
	
	public:
	Moteur();

	void arreter();
	void avancer(uint8_t vitesse);
	void reculer(uint8_t vitesse);
	void boost();
	void tournerDroite(Vitesse vitesse);
	void tournerGauche(Vitesse vitesse);
	void faire180(Direction direction);
	
};
#endif
