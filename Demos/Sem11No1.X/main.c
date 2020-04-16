 /**
 * @file   main.c, projet Sem11No1
 * @author Benoit Beaulieu
 * @date   avril  2020
 * @brief  Exam2No1
 * Question 1 Sur votre carte PicKit4, écrivez un programme qui 
a)	Affiche les 4 MSB de la conversion analogique de la lecture du potentiomètre 
  * RP1 sur les DEL 4 à 7.  La conversion AN doit se faire par interruption.
b)	Affiche les 4 LSB d'un compteur sur les DEL 3 à 0. Le compteur s'incrémente 
  * à une vitesse de 16Hz. Le timer 3 du PIC sera utilisé pour incrémenter le timer.

 */

#include "xc.h"

void initialisation(void);



void main(void)
{
    initialisation();
    while(1); // Boucle principale du programme
}


/**
 * @brief Fonction qui sert à gérer l'initialisation des différents regesitres et variables.
 */
void initialisation(void)
{

    TRISD = 0; //Tout le port D en sortie

    ANSELH = 0;  // RB(0:4) en mode digital. Sur le 18F45K20 AN et PortB sont sur les memes broches
    TRISBbits.RB0 = 1;  //RB0 en entree
    
    //Configuration du port analogique
    TRISAbits.TRISA0 = 1; //A0 en entrée
    ANSELbits.ANS0 = 1;  //A0 en mode analogique
    
    ADCON0bits.ADON = 1; //Convertisseur AN à on
    ADCON1bits.VCFG1 = 0; //Tension de référence V- reliée à VSS
    ADCON1bits.VCFG0 = 0; //Tension de référence V+ reliée à VDD
    ADCON2bits.ADFM = 0; //Alignement à gauche des 10bits de la conversion (8 MSB dans ADRESH, 2 LSB dans ADRESL)
    ADCON2bits.ACQT = 7; //20 TAD (on laisse le max de temps au Chold du convertisseur AN pour se charger)
    ADCON2bits.ADCS = 6; //Fosc/64 (Fréquence pour la conversion la plus longue possible)
    //Config AN par interruption
    PIR1bits.ADIF = 0; //on reset le flag
    PIE1bits.ADIE = 1; //permet interruptions de l'AD
    ADCON0bits.GO_DONE = 1;  //lance une conversion AN
    
    
    // configuration timer3
    T3CONbits.RD16 = 1;
    T3CONbits.T3CKPS = 0;
    T3CONbits.TMR3CS = 0;
    T3CONbits.TMR3ON = 1;
    //TMR3 = 0x10;
    PIR2bits.TMR3IF = 0;
    PIE2bits.TMR3IE = 1;
    

    
    INTCONbits.PEIE = 1; //permet interruption des périphériques
    INTCONbits.GIE = 1;  //interruptions globales permises
    
    
    
    
}

