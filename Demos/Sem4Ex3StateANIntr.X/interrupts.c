/**
 * @file   interrupts.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Fonctions pour les interruptions
 * @revision Benoit Beaulieu, janvier 2015, petit ménage et ajout de commentaires
 *
 */


#include "xc.h"
#include "interrupts.h"

extern int g_etat;

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* High-priority service */
void interrupt high_isr(void)
{

    /* Determine which flag generated the interrupt */
    if(INTCONbits.INT0IF)   //interruption du clavier (INT0)
    {
        g_etat++;
        g_etat = g_etat % enumEtatMax; //si atteint max, revient à 0
        PORTD = 0; //On éteind toutes les des lors d'un changement d'etat
        while (PORTBbits.RB0 == 0); //Elimine rebond
        INTCONbits.INT0IF=0;  //reset flag d'intr.
    }
 
}

/* Low-priority interrupt routine */
void low_priority interrupt low_isr(void)
{

}
