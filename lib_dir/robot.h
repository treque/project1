#include <constantes.h>
#include <moteurs.h>
#include <capteurs.h>
#include <sonorite.h>
#include <DEL.h>

#ifndef ROBOT_H
#define ROBOT_H
class Robot {
	
	public:
	Robot();
	
	void verifierEtat();
	void changerCote(Direction direction);
	void ajuster(Direction dir);
	void verifierDetection();
	
	void arreter();
	void boost();
	void avancer(uint8_t vitesse);
	void reculer(uint8_t vitesse);
	void tournerDroite(Vitesse vitesse);
	void tournerGauche(Vitesse vitesse);
	void faire180(Direction dir);
	
	void modifierEtat(Etat etat);
	Etat obtenirEtat() const;
	uint8_t obtenirDistance(Direction dir);
	
	private:
	Sonorite piezo;
	DEL del;
	Capteur capteurDroit_;
	Capteur capteurGauche_;
	bool peutTourner_;
	Etat etat_;
	Moteur moteur_;
};
#endif
