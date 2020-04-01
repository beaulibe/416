/**
 * @file   main.c
 * @author Richard Cloutier, rev. Benoit Beaulieu
 * @date   Janvier 2014
 * @brief  PWM sur RC1. Mettre une Del + r�sistance sur RC1 pour voir l'effet.
 *         Le duty cycle du PWM est dict� par RP1 du pickit board.
 *         Affiche aussi le resultat de AN sur les del.
 
 */

#include "commun.h"          /* Include generaux au programme */

extern int g_resAN;

/**
 * @brief Fonction qui sert � g�rer l'initialisation des diff�rents registres et variables.
 */
void initialisation(void)
{
    //initialisation_ConfigurerPortDSortie();
    initialisation_ConfigurerAdc();
    initialisation_ActiverIntAdc();
    initialisation_ActiverPWM();
    initialisation_ActiverInterruptions();
}

void main(void)
{
    TRISD = 0xFF; //port D en entr�e
    initialisation();

    // Boucle principale du programme
    //On affichera sur la Del7 la sortie du PWM
    while(1)
    {
        
       // PORTD = g_resAN; //affiche 8 bits de poids fort sur DEL
        CCPR2L = g_resAN; // on change le duty cycle du PWM

    }
}