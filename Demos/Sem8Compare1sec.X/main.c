 /**
 * @file   main.c, projet Capture
 * @author Benoit Beaulieu
 * @date   13 mars. 2018
 * @brief  Programme démo de la semaine 8 du cours 247-416
 *         Question 2 : Comment feriez-vous pour utiliser le mode '''''Compare'''' 
  * pour faire clignoter la DEL aux secondes?
  * Réponse : On ajoute une fonction d'interruption. Dans l'interruption on met 
  * la valeur du timer 1 + la valeur de temps équivalent à 1 seconde dans le 
  * registre CCPR2. Calculs: 1 seconde = (1/1MHz)*4*8*31250  donc l'instruction 
  * dans la fonction d'interruption serait CCP2R = TMR1+31250;
 
 */

#include <xc.h>

void initialisation(void);

void main(void)
{
  
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

    TRISD = 0xFF; //Tout le port D en entrée car on reliera RC1 sur une DEL pour voir l'état de RC1

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
   // PIR1bits.TMR1IF = 0;
   // PIE1bits.TMR1IE = 1;

    //Configuration du CCP2 en mode Compar. RC1 est lié à TMR1
    CCP2CONbits.CCP2M = 0b0010; //Compare mode, toggle output on match (CCP2IF bit is set)
    TRISCbits.RC1 = 0; //RC1 en sortie
    T3CONbits.T3CCP1 = 0; //TMR1 lié à CCP1 et CCP2 (bit 6))
    T3CONbits.T3CCP2 = 0; //TMR1 lié à CCP1 et CCP2 (bit 3))
    CCPR2 = 0xAABB;  //0xAABB est la valeur de comparaison de CCPR2 à tmr1
    //intr de CCP2
    PIR2bits.CCP2IF = 0;
    PIE2bits.CCP2IE = 1; //interruptions permises
    
    INTCONbits.PEIE = 1; //permet interruption des périphériques
    INTCONbits.GIE = 1;  //interruptions globales permises


}

