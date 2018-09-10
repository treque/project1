/*
 * Nom: capteurs.cpp
 * Equipe: 76
 * Description: Implementation de la classe capteurs
 */
#include <capteurs.h>

/* Constructeur d'un capteur
 * Param direction: le cote dont le capteur fait face
 */
Capteur::Capteur(Direction direction): direction_(direction), murDetecte_(false) {}

bool Capteur::obtenirMurDetecte() const {
		return murDetecte_;	
}

/* Methode qui modifie le mur detecte du capteur */
void Capteur::modifierMurDetecte(bool detection) {
		murDetecte_=detection;	
}

/* Methode qui renvoie la distance en cm entre le capteur et l'object capte */
int Capteur::obtenirDistance(){
	int conversion = 0;
	// On fait une moyenne pour s'adapter aux instabilites
	for (int i = 0 ; i < 50 ; i++){
		conversion += (lecture(direction_)>>2);
	}
	conversion = conversion/55;
	// Pour eviter une div/0 ET pour enlever ignorer tout obstacle
	// au-dela d'un seuil.
	if(conversion < 44){
		return 0;
	}
	// Nous retournons la distance en cm
	return round((2649/(conversion-11)-0.42));
}
