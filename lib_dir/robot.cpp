#include "robot.h"

/* Constructeur par defaut du robot */
Robot::Robot() : capteurDroit_(Droite),
				 capteurGauche_(Gauche),
				 peutTourner_(true),
				 etat_(START)				 
{
	moteur_ = Moteur();
}

/* Methode qui met a jour les capteurs du robot et ses etats */
void Robot::verifierEtat() {
	verifierDetection();
	// Premiere iteration: etat START
	if (etat_ == START){
		if(capteurDroit_.obtenirMurDetecte()) {
			etat_=SUIVREDROITE;
			moteur_.boost();
		}
		else if(capteurGauche_.obtenirMurDetecte()) {
			etat_= SUIVREGAUCHE;
			moteur_.boost();
		}
	} 
	// Si robot suit le mur GAUCHE 
	else if(etat_ == SUIVREGAUCHE) {
		//S'il ne detecte pas de mur a droite, il a le droit de tourner
		if (!capteurDroit_.obtenirMurDetecte()){
			peutTourner_ = true;
		}
		//Si le robot a le droit de tourner et qu'il detecte un mur a 
		// droite, il tourne et n'a plus le droit de tourner par la suite
		else if(capteurDroit_.obtenirMurDetecte() && peutTourner_){
			etat_ = TOURNERDROITE;
			peutTourner_ = false;
		}
	}
	// Si robot suit le mur DROIT
	else if(etat_ == SUIVREDROITE) {
		//S'il ne detecte pas de mur a gauche, il a le droit de tourner
		if (!capteurGauche_.obtenirMurDetecte()){
			peutTourner_ = true;
		}
		//Si le robot a le droit de tourner et qu'il detecte un mur a 
		// gauche, il tourne et n'a plus le droit de tourner par la suite
		else if(capteurGauche_.obtenirMurDetecte() && peutTourner_) {
			etat_ = TOURNERGAUCHE;
			peutTourner_ = false;
		}
	}
}

/* Methode qui permet au robot de changer de cote
 * Param direction : direction vers laquelle le robot change de cote
 */
void Robot::changerCote(Direction direction) {
	del.afficherRouge();
	if(direction==Droite){
		while(capteurDroit_.obtenirDistance() > 25) {
			tournerDroite(VITE);
			_delay_ms(50);
			avancer(190);
			_delay_ms(80);
			arreter();
			_delay_ms(10);
			tournerGauche(VITE);
			_delay_ms(30);
		}
		etat_=SUIVREDROITE;
	}
	else if(direction==Gauche) {
		while(capteurGauche_.obtenirDistance() > 25){
			tournerGauche(VITE);
			_delay_ms(50);
			avancer(190);
			_delay_ms(80);
			arreter();
			_delay_ms(10);
			tournerDroite(VITE);
			_delay_ms(30);
		}
		etat_=SUIVREGAUCHE;
	}
}

/* Methode qui arrete les moteurs du robot */
void Robot::arreter() {
	moteur_.arreter();
}

void Robot::boost(){
	moteur_.boost();
}

/* Methode qui fait avancer le robot
 * Param direction : vitesse a laquelle
 */
void Robot::avancer(uint8_t vitesse) {
	moteur_.avancer(vitesse);
}

/* Methode qui arrete les moteurs du robot */
void Robot::reculer(uint8_t vitesse) {
	moteur_.reculer(vitesse);
}

/* Methode qui permet au robot d'effectuer un virage vers la droite
 * Param vitesse : vitesse a laquelle le robot tourne
 */
void Robot::tournerDroite(Vitesse vitesse) {
	moteur_.tournerDroite(vitesse);
}

/* Methode qui permet au robot d'effectuer un virage vers la gauche
 * Param vitesse : vitesse a laquelle le robot tourne
 */
void Robot::tournerGauche(Vitesse vitesse) {
	moteur_.tournerGauche(vitesse);
}

/* Methode qui permet au robot d'effectuer un virage de 180 degres
 * Param dir: direction du virage
 */
void Robot::faire180(Direction dir) {
	moteur_.faire180(dir);
}

/* Methode qui retourne l'etat du robot */
Etat Robot::obtenirEtat() const {
	return etat_;
}

/* Methode qui modifie l'etat du robot
 * Param etat: nouvel etat du robot
 */
void Robot::modifierEtat(Etat etat){
	etat_= etat;
}

/* Methode qui retourne la distance des capteurs du robot
  * Param dir: cote du capteur dont on veut obtenir la distance
 */
uint8_t Robot::obtenirDistance(Direction dir) {
	if(dir == Droite){
		return capteurDroit_.obtenirDistance();
	}
	else{
		return capteurGauche_.obtenirDistance();
	}
}

/* Methode qui ajuste le robot par rapport au mur qu'il suit
 * Param dir: le cote du mur qu'il suit
 */
void Robot::ajuster(Direction dir){
	verifierDetection();
	if (dir == Gauche){
		if(capteurGauche_.obtenirMurDetecte()) {
			if(obtenirDistance(Gauche) < 22) {
				del.afficherRouge();
				tournerDroite(LENT);	
				_delay_ms(25);
			}
			else if(obtenirDistance(Gauche) > 30 && obtenirDistance(Gauche) < 60) {
				del.afficherRouge();
				tournerGauche(LENT);
				_delay_ms(25);
			}
			else {
				del.afficherVert();
				avancer(150);
				_delay_ms(25);
			}
		}
		// Si le robot ne detecte pas le mur qu'il suit
		else {
			tournerGauche(VITE);
		}
	}
	else{
		// Si robot est plus proche que 12 cm du mur, il tourne
		// a gauche pour s'ajuster
		if(capteurDroit_.obtenirMurDetecte()) {
			if(obtenirDistance(Droite) < 22) {
				del.afficherRouge();
				tournerGauche(LENT);
				_delay_ms(25);
			}
			// Si le robot est plus loin que 25 cm du mur, il tourne
			// a droite pour s'ajuster
			else if(obtenirDistance(Droite) > 30 && obtenirDistance(Droite) < 60) {
				del.afficherRouge();
				tournerDroite(LENT);
				_delay_ms(25);
			} 
			// A une distance adequate du mur, le robot avance.
			//else {
			else{
				del.afficherVert();
				avancer(150);
				_delay_ms(25);
			}
		}
		// Si le robot ne voit pas le mur qu'il suit
		else {
			tournerDroite(VITE);
		}
	
	}
}

/* Methode qui verifie la detection de chaque cote du robot */
void Robot::verifierDetection() {
	uint8_t distance1Droite, distance1Gauche, distance2Droite, distance2Gauche;
	//premieres mesures
	distance1Droite = capteurDroit_.obtenirDistance();
	distance1Gauche = capteurGauche_.obtenirDistance();
	_delay_ms(450);
	//deuxiemes mesures
	distance2Droite = capteurDroit_.obtenirDistance();
	distance2Gauche = capteurGauche_.obtenirDistance();
	
	//VERIFICATION A DROITE
	if(distance1Droite < 65 && distance1Droite > 11) {
		// troisieme facteur de la condition -- pour s'assurer de la 
		// stabilite des deux distances lues
		if((distance2Droite < 65) && (distance2Droite > 11) && 
		(sqrt(pow((distance1Droite-distance2Droite), 2)) < 15)) {
			capteurDroit_.modifierMurDetecte(true);
		}
		else {
			capteurDroit_.modifierMurDetecte(false);
			if(etat_==SUIVREGAUCHE) {
				for(int i = 0; i < 3 ; i++ ) {
					piezo.jouerSonorite(78);
					_delay_ms(200);
					piezo.arreterSonorite();
					_delay_ms(100);
				}
			}
		}
	}
	else {
		capteurDroit_.modifierMurDetecte(false);
	}
	
	//VERIFICATION A GAUCHE
	if(distance1Gauche < 60 && distance1Gauche > 11) {
		// troisieme facteur de la condition -- pour s'assurer de la 
		// stabilite des deux distances lues
		if((distance2Gauche < 60) && (distance2Gauche > 11)
		&& (sqrt(pow((distance1Gauche-distance2Gauche), 2)) < 15)) {
			capteurGauche_.modifierMurDetecte(true);
		}
		else {
			capteurGauche_.modifierMurDetecte(false);
			if(etat_==SUIVREDROITE) {
				for(int i = 0; i < 3 ; i++ ) {
					piezo.jouerSonorite(78);
					_delay_ms(200);
					piezo.arreterSonorite();
					_delay_ms(100);
				}
			}
		}
	}
	else {
		capteurGauche_.modifierMurDetecte(false);
	}
	
}
