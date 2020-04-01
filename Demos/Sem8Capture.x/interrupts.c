/**
 * @file   interrupts.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Fonctions pour les interruptions
 * @revision Benoit Beaulieu, janvier 2015, petit ménage et ajout de commentaires
 *
 */

#include <xc.h>


/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* High-priority service */
void __interrupt() high_isr(void)
{

    /* Determine which flag generated the interrupt */

//    if (PIR1bits.TMR1IF) // timer 1
//    {
//        PIR1bits.TMR1IF   = 0;    // baisser l'indication de l'interruption
//
//        PORTDbits.RD0 ^= 1; //Toggle DEL 
//    }
//    
    
    /*interruption du CCP2 pin RC1*/
    if (PIR2bits.CCP2IF) // CCP2
    {
        PIR2bits.CCP2IF = 0; //reset flag
        PORTD = CCPR2H; //On affiche les 8 LSB de la capture (lié à tmr1 lors de la configuration)
    }

 
}

