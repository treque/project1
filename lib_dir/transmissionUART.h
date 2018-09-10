/*
 * Nom: transmissionUART.h
 * Equipe: 76
 * Description: Fonctions permettant de manipuler les donnees dans la memoire du robot
 */
#ifndef UART_H
#define UART_H
#include "constantes.h"
#include "memoire_24.h"

void initialisationUART ( void ) ;
void transmissionUART ( uint8_t donnee );
void lectureMemoire();
unsigned char receptionUART( void );
#endif
