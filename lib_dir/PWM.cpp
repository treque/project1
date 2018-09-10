/*
 * Nom: PWM.cpp
 * Equipe: 76
 * Description: Implementation des fonctions de PWM
 */

#include "PWM.h"

/* Fonction permettant d'ajuster le ratio du PWM
 * Param pwmA : entier sur 8 bits permettant de regler le ratio pour le PWMA
 */
void ajustementPWMGauche(uint8_t pwmA) {
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
    OCR1A = pwmA;
}

/* Fonction permettant d'ajuster le ratio du PWM
 * Param pwmB : entier sur 8 bits permettant de regler le ratio pour le PWMB
 */
void ajustementPWMDroit(uint8_t pwmB) {
	TCCR1A |=  (1 << COM1B0) | (1 << COM1B1);
    OCR1B = pwmB;
}

