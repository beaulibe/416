 /**
 * @file   main.c
 * @author Benoit Beaulieu
 * @date   10 mars 2020
 * @brief  Programme démo de la semaine 6 du cours 247-416
  *        Exemple d'utilisation des timers
 * @version 1.0
 * Environnement:
 *     Développement: MPLAB X IDE (version 5.30)
 *     Compilateur: XC8 (version 2.10)
 *     Matériel: Carte démo du Pickit3. PIC 18F45K20
 */

#include "commun.h"


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

    INTCONbits.PEIE = 1; //permet interruption des périphériques
    INTCONbits.GIE = 1;  //interruptions globales permises


}

