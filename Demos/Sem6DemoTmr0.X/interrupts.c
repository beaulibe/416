/**
 * @file   interrupts.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Fonctions pour les interruptions
 * @revision Benoit Beaulieu, janvier 2020, petit ménage et ajout de commentaires
 *
 */


#include "commun.h"



/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* High-priority service */
void interrupt high_isr(void)
{

    /* Determine which flag generated the interrupt */

       if (INTCONbits.TMR0IF) // timer 0
    {
        INTCONbits.TMR0IF   = 0;    // baisser l'indication de l'interruption
        
        TMR0H               = 0xC2;
        TMR0L               = 0xF6;     // valeur pour forcer le délais d'une seconde

        PORTDbits.RD7 ^= 1; //Toggle del 0
    }

 
}

/* Low-priority interrupt routine */
void low_priority interrupt low_isr(void)
{

}
