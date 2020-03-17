/**
 * @file   interrupts.c
 * @author Jacob Deschamps
 * @date   Janvier 2019
 * @brief  Traitement des interruptions des timers et du module CCP1
 * @revision 
 */

#include <xc.h>
#include "interrupts.h"

//Variable globale pour l'écho du sonar
unsigned int g_echo[NB_ECHO] = {0};
int g_compteEcho = 0;

/******************************************************************************/
/* Interrupt Service Routines                                                 */
/******************************************************************************/

/* High-priority interrupt service routine */
void __interrupt(high_priority) high_isr(void)
{
    static unsigned int t1; //Variable statique ui permettra d'enregistrer la valeur du timer 3 une fois le front montant de l'echo détecté par le module CCP1
    
    if(INTCONbits.TMR0IF) //Si l'interruption du timer 0 est survenue
    {
        PORTCbits.RC1 = 1; //L'impulsion (signal TRIG) devant être envoyée au sonar commence
       
        for(int i = 0; i < 2; i++) //Cette boucle permet d'offrir un délai légèrement supérieur à 10 us
            NOP();
        
        PORTCbits.RC1 = 0; //L'impulsion (signal TRIG) devant être envoyée est arrêtée
        
        CCP1CONbits.CCP1M = 0b0101; //Le module CCP1 est utilisé en mode capture pour chaque front descendant du signal d'echo à percevoir
        
        TMR3 = 0; //Avec cette valeur et pour un prescaler de 1:8, on a un délai supérieur à 130 ms pour le timer 3
        T3CONbits.TMR3ON = 1; //Le timer 3 est redémaré
        
        INTCONbits.TMR0IF = 0; //On remet à zéro le flag d'interruption du timer 0
        TMR0H = 0b00010101;
        TMR0L = 0b10100000; //La valeur du timer 0 est rechargée pour qu'il puisse recommencer à s'écouler à partir de cette valeur
    }
    if (PIR1bits.TMR1IF)
    {
        PORTDbits.RD7 ^= 1; //La DEL rouge clignote à 10 Hz selon la configuration du timer 1
        
        PIR1bits.TMR1IF = 0; //On remet à zéro le flag d'interruption du timer 1
        TMR1 = 0b0011110010110000; //La valeur du timer 1 est rechargée pour qu'il puisse recommencer à s'écouler à partir de cette valeur
    }
    if (PIR1bits.CCP1IF)
    {
        if (CCP1CONbits.CCP1M == 0b0101) //Si le module CCP1 est configuré pour détecter un front montant
        {
            PORTCbits.RC0 = 1; //La DEL jaune est allumée dès que le front montant de l'echo a été détecté
            t1 = CCPR1; //La valeur du timer 3 qui a été capturée par le module CCP1 est enregistrée dans la variable t1 
        }
        else //Si le module CCP1 est configuré pour détecter un front descendant
        {
            g_echo[g_compteEcho] = CCPR1 - t1; //La différence entre t1 et la nouvelle valeur du timer 3 qui a été capturée par le module CCP1 est enregistrée dans la variable g_echo
            g_compteEcho++;
            
            if (g_compteEcho > NB_ECHO) //Si le tableau des durées d'écho est rempli
            {
                g_compteEcho = 0; //Le compte des échos est remis à zéro
            }
            
			T3CONbits.TMR3ON = 0; //Le timer 3 est arrêté
            PORTCbits.RC0 = 0; //La DEL jaune est éteinte dès que le front descendant de l'echo a été détecté
        }
       
        CCP1CONbits.CCP1M = 0b0100; //Le module CCP1 est utilisé en mode capture pour chaque front descendant du signal d'echo à percevoir
        PIR1bits.CCP1IF = 0; //On remet à zéro le flag d'interruption du module CCP1
    }
}

/* Low-priority interrupt service routine */
void __interrupt(low_priority) low_isr(void)
{
    //Il n'y a rien à ajouter ici pour le laboratoire 1
}
