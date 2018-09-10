/*
 * Nom: DEL.cpp
 * Equipe: 76
 * Description: Fonctions permettant de manipuler l'affichage de la DEL 
 */
 
 #include <DEL.h>
 
 /* Fonction qui initialise le port qui sera utilise pour manipuler la DEL (port A) */
 DEL::DEL () {
 }
 
 /* Fonction qui permet d'afficher la couleur rouge sur la DEL */
 void DEL::afficherRouge() {
	PORTA = ROUGE;
 }
 
 /* Fonction qui permet d'afficher la couleur verte sur la DEL */
 void DEL::afficherVert() {
	PORTA = VERT;
 }
 
/* Fonction qui permet d'eteindre la DEL */
void DEL::eteindre() {
	PORTA = ETEINT;
}
