/*
 * Nom: sonorite.cpp
 * Equipe: 76
 * Description: Fonctions permettant de manipuler la présence d'un son 
 */
 #include "sonorite.h"

 /* Fonction-constructeur qui initialise le port qui sera utilise pour manipuler le son (port B) */
Sonorite::Sonorite(){
	sonAllume_= false;
}
 /* Fonction qui permet de jouer un son selon la note passée par paramètre */
void Sonorite::jouerSonorite(double note){
	if(note > 44 && note < 82){
		sonAllume_ = true;
		TCNT0 = 0;
		double frequence = pow(2,(note-69)/12)*440;
		//se referer a la formule pour la frequence dans la documentation
		OCR0A = round((8000000/(2*frequence*256))-1);
		//toggle on compare match, CTC mode
		TCCR0A |= (1 << COM0A0) | (1 << WGM01) ;
	}
}
 /* Fonction qui arrête un son si un son est allumé*/
void Sonorite::arreterSonorite(){
	if(sonAllume_){
		sonAllume_ = false;
		TCCR0A = 0;
	}
}
