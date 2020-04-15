 /**
 * @file   main.c, projet Capture
 * @author Benoit Beaulieu
 * @date   13 mars. 2018
 * @brief  Programme démo de la semaine 8 du cours 247-416
 *         Exemple d'utilisation d'un capture du module CCP 
 
 */

#include <xc.h>

void initialisation(void);

void main(void)
{
    int i;

    initialisation();
    //PORTD = 0xC1;  //D7,D6 et D0 allumées
     
    while(1) // Boucle principale du programme
    {
    }
}


/**
 * @brief Fonction qui sert à gérer l'initialisation des différents regesitres et variables.
 */
void initialisation(void)
{

    TRISD = 0; //Tout le port D en sortie

    ANSELH = 0;  // RB(0:4) en mode digital. Sur le 18F45K20 AN et PortB sont sur les memes broches
    TRISBbits.RB0 = 1;  //RB0 en entree

    
    // configuration timer1
    //Calcul: 1MHz/4/8/65536 = 0,477Hz -> 2.1 secondes
    T1CONbits.RD16 = 1; 
    //T1CONbits.T1RUN = 1;  //bit en lecture seule
    T1CONbits.T1CKPS = 3; //psc = 8
    T1CONbits.TMR1CS = 0; //fosc/4
    T1CONbits.TMR1ON = 1; //
    //int de trm1
    //PIR1bits.TMR1IF = 0;
    //PIE1bits.TMR1IE = 1;

    //Configuration du CCP2 sur RC1 et lié à TMR1
    CCP2CONbits.CCP2M = 0b0101; //Capture mode, every rising edge
    TRISCbits.RC1 = 1; //RC1 en entrée
    T3CONbits.T3CCP1 = 0; //TMR1 lié à CCP2 (bit 6))
    T3CONbits.T3CCP2 = 0; //TMR1 lié à CCP2 (bit 3))
    //intr de CCP2
    PIR2bits.CCP2IF = 0;
    PIE2bits.CCP2IE = 1; //permet les interruptions
    
    
    
    INTCONbits.PEIE = 1; //permet interruption des périphériques
    INTCONbits.GIE = 1;  //interruptions globales permises


}

