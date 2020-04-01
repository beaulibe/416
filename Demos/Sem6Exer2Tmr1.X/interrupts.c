/**
 * @file   interrupts.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Fonctions pour les interruptions
 * @revision Benoit Beaulieu, janvier 2015, petit ménage et ajout de commentaires
 *
 */


//#include "commun.h"
#include <xc.h>


/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* High-priority service */
void interrupt high_isr(void)
{

    static unsigned char compteur4bits = 0;
    /* Determine which flag generated the interrupt */

    if (INTCONbits.TMR0IF) // timer 0
    {
        INTCONbits.TMR0IF   = 0;    // baisser l'indication de l'interruption
        
        //TMR0H               = 0xC2;
        //TMR0L               = 0xF6;     // valeur pour forcer le délais d'une seconde
        TMR0 = 0xC2F6; 
        
        PORTDbits.RD0 ^= 1; //Toggle del 0
    }

    if (PIR1bits.TMR1IF) // timer 1
    {
        compteur4bits++;
        PORTD = (compteur4bits << 4) | (0b00001111 & PORTD );
        
        PIR1bits.TMR1IF   = 0;    // baisser l'indication de l'interruption
        TMR1 = 0x3CB0;
        
        //TMR1L = 0xB0;
        //TMR1H = 0x3C;
    }

 
}

/* Low-priority interrupt routine */
void low_priority interrupt low_isr(void)
{

}
