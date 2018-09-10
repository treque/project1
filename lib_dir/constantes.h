/*
 * Nom: constantes.h
 * Equipe: 76
 * Description: Inclusions, constantes et definitions 
 */

#ifndef CONSTANTES
#define CONSTANTES

using namespace std;

// Definition de la frequence de la carte mere
#define F_CPU 8000000

// Inclusions necessaires 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include <util/twi.h>


// Definitions des couleurs pour la DEL
#define ROUGE 0x02;
#define VERT 0x01;
#define ETEINT 0x00;

// Etats et directions
enum Etat{START, SUIVREDROITE, TOURNERDROITE, SUIVREGAUCHE, TOURNERGAUCHE};
enum Direction{Droite=7,Gauche=6};

// Vitesse des roues
enum Vitesse {LENT = 0, VITE = 1};

// Types de messages pouvant etre lus par le robot
enum MessagesLus {VITESSEROUEGAUCHE = 0xf8, VITESSEROUEDROITE,
					COULEURDEL, REQUETE};
enum CouleursDel { COULEURDELETEINT, COULEURDELVERT, COULEURDELROUGE};
// Type de messages pouvant etre envoyes par le robot
enum MessagesEnvoyes { NOM = 0xf0, NOEQUIPE, NOSECTION, SESSION, COULEURBASE,
						ETATINTERRUPT, DISTANCEGAUCHE, DISTANCEDROITE};

#endif
