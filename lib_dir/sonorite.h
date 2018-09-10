/*
 * Nom: sonorite.h
 * Equipe: 76
 * Description: Classe contenant les fonctions permettant de manipuler la présence d'un son
 */
 
#include <constantes.h>
#ifndef SONORITE_H
#define SONORITE_H

class Sonorite{
	public:
		Sonorite();
		void jouerSonorite(double note);
		void arreterSonorite();
	private:
		bool sonAllume_;
};

#endif
