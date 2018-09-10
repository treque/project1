/*
 * Nom: capteurs.h
 * Equipe: 76
 * Description: Definition de la classe capteurs
 */
#include <constantes.h>
#include <can.h>
#ifndef CAPTEURS_H
#define CAPTEURS_H
class Capteur : public can {
	
	public:
		Capteur(Direction direction);
		bool obtenirMurDetecte() const;
		int obtenirDistance();
		void modifierMurDetecte(bool detection);
	
	private:
		Direction direction_;
		bool murDetecte_;
};
#endif
