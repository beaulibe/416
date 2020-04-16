/**
 * @file   main.c
 * @author Benoit Beaulieu
 * @date   Mars 2020
 * @brief  Exercice 1 - Encore des timers!
 * Réalisez un programme qui lit la valeur du potentiomètre et utilise cette valeur pour faire varier la fréquence de clignotement de la DEL7. 
 * Les contraintes suivantes doivent être respectées pour votre programme :
Conservez seulement les 4 MSB du résultat de la conversion de l'ADC.
Affichez ces quatre bits sur les DEL0 à DEL3.
Faites la lecture du résultat de conversion de l'ADC par interruption.
Utilisez le timer 0 pour faire clignoter la DEL7.
Utilisez le tableau ci-dessous pour moduler la fréquence de clignotement de la DEL7 en fonction du résultat de la conversion de l'ADC :
Résultat de l'ADC	Fréquence de la DEL7
0 ou 1	1 Hz
2	2 Hz
3	3 Hz
...	...
15	15 Hz
 */

#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

extern int g_resAN;

/*********** prototypes *****************/
void initialisation(void);


void main(void)
{
    initialisation();

    
    ADCON0bits.GO_DONE = 1;  //On lance une première conversion de l'ADC
 
    while(1) //Boucle principale du programme
    {
         //La DEL7 clignote selon la fréquence du timer 0 modulée par l'ADC
         PORTD = (PORTD & 0xF0) | (g_resAN >> 4); //Les DEL0 à DEL3 reçoivent les 4 MSB du résultat de conversion de l'ADC
    }
    
}

/**
 * @brief Fonction qui sert à gérer l'initialisation des différents registres et variables.
 */
void initialisation(void)
{
    
    TRISD = 0; //port D en sortie

    
   //Configuration du port analogique
    TRISAbits.TRISA0 = 1; //A0 en entrée
    ANSELbits.ANS0 = 0;  //A0 en mode analogique
    ADCON0bits.ADON = 1; //Convertisseur AN à on
    ADCON1bits.VCFG1 = 0; //Tension de référence V- reliée à VSS
    ADCON1bits.VCFG0 = 0; //Tension de référence V+ reliée à VDD
    ADCON2bits.ADFM = 0; //Alignement à gauche des 10bits de la conversion (8 MSB dasn ADRESH, 2 LSB à gauche dans ADRESL)
    ADCON2bits.ACQT = 7; //20 TAD (on laisse le max de temps au Chold du convertisseur AN pour se charger)
    ADCON2bits.ADCS = 6; //Fosc/64 (Fréquence pour la conversion la plus longue possible)
    //Config AN par interruption
    PIR1bits.ADIF = false; //on reset le flag
    PIE1bits.ADIE = 1; //permet interruptions de l'AD
    ADCON0bits.GO_DONE = 1;  //lance une conversion    
    
    
    
   // configuration timer0
    T0CONbits.TMR0ON    = 1;
    T0CONbits.T08BIT    = 0; // mode 16 bits
    T0CONbits.T0CS      = 0;
    T0CONbits.PSA       = 0; // prescaler enabled
    T0CONbits.T0PS      = 0b011; // 1:16 pre-scaler

    

    // calcul de la valeur à mettre dans les registres pour avoir un délai = 1 seconde
    // FOSC/4 = 1MHz/4 = 250 KHz
    // avec 16 bits on peut avoir une attente maximale = 65535 coups d'horloge
    // avec 8 bits on peut avoir une attente maximale = 255 coups d'horloge
    // dans le cas ici, on active le prescaler à 1:16 => 250 KHz / 16 = 15625 (il est possible de fonctionner en mode 16 bits)
    // 15625 décimal = 0x3D09
    // l'interruption du Timer0 se produit au passage de 0xFFFF à 0x0000, il faut donc soustraire le nombre de coups d'horloge voulu du total
    // 0xFFFF - 0x3D09 = 0xC2F6 !
    
    //Attention, il faut écrire dans le TMR0H avant le TMR0L, car le TMR0H est un buffer
    // avant le vrai registre. Voir section 12.2
    //Lorsqu'on écrit dans TMR0L le valeur de TMR0H est mise dans le vrai registre en même temps.
    TMR0H = 0xC2; 
    TMR0L = 0xF6;
    

    INTCONbits.TMR0IE   = 1;  // timer 0 interrupt enable
    INTCONbits.TMR0IF   = 0; // timer 0 interrupt flag
    
    
    
    //Interruptions générales
    INTCONbits.PEIE = 1; //permet interruption des périphériques
    INTCONbits.GIE = 1;  //interruptions globales permises
}