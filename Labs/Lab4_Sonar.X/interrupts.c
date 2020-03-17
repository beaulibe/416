/**
 * @file   interrupts.c
 * @author Jacob Deschamps
 * @date   Janvier 2019
 * @brief  Traitement des interruptions des timers et du module CCP1
 * @revision 
 */

#include <xc.h>
#include "interrupts.h"

//Variable globale pour l'�cho du sonar
unsigned int g_echo[NB_ECHO] = {0};
int g_compteEcho = 0;

/******************************************************************************/
/* Interrupt Service Routines                                                 */
/******************************************************************************/

/* High-priority interrupt service routine */
void __interrupt(high_priority) high_isr(void)
{
    static unsigned int t1; //Variable statique ui permettra d'enregistrer la valeur du timer 3 une fois le front montant de l'echo d�tect� par le module CCP1
    
    if(INTCONbits.TMR0IF) //Si l'interruption du timer 0 est survenue
    {
        PORTCbits.RC1 = 1; //L'impulsion (signal TRIG) devant �tre envoy�e au sonar commence
       
        for(int i = 0; i < 2; i++) //Cette boucle permet d'offrir un d�lai l�g�rement sup�rieur � 10 us
            NOP();
        
        PORTCbits.RC1 = 0; //L'impulsion (signal TRIG) devant �tre envoy�e est arr�t�e
        
        CCP1CONbits.CCP1M = 0b0101; //Le module CCP1 est utilis� en mode capture pour chaque front descendant du signal d'echo � percevoir
        
        TMR3 = 0; //Avec cette valeur et pour un prescaler de 1:8, on a un d�lai sup�rieur � 130 ms pour le timer 3
        T3CONbits.TMR3ON = 1; //Le timer 3 est red�mar�
        
        INTCONbits.TMR0IF = 0; //On remet � z�ro le flag d'interruption du timer 0
        TMR0H = 0b00010101;
        TMR0L = 0b10100000; //La valeur du timer 0 est recharg�e pour qu'il puisse recommencer � s'�couler � partir de cette valeur
    }
    if (PIR1bits.TMR1IF)
    {
        PORTDbits.RD7 ^= 1; //La DEL rouge clignote � 10 Hz selon la configuration du timer 1
        
        PIR1bits.TMR1IF = 0; //On remet � z�ro le flag d'interruption du timer 1
        TMR1 = 0b0011110010110000; //La valeur du timer 1 est recharg�e pour qu'il puisse recommencer � s'�couler � partir de cette valeur
    }
    if (PIR1bits.CCP1IF)
    {
        if (CCP1CONbits.CCP1M == 0b0101) //Si le module CCP1 est configur� pour d�tecter un front montant
        {
            PORTCbits.RC0 = 1; //La DEL jaune est allum�e d�s que le front montant de l'echo a �t� d�tect�
            t1 = CCPR1; //La valeur du timer 3 qui a �t� captur�e par le module CCP1 est enregistr�e dans la variable t1 
        }
        else //Si le module CCP1 est configur� pour d�tecter un front descendant
        {
            g_echo[g_compteEcho] = CCPR1 - t1; //La diff�rence entre t1 et la nouvelle valeur du timer 3 qui a �t� captur�e par le module CCP1 est enregistr�e dans la variable g_echo
            g_compteEcho++;
            
            if (g_compteEcho > NB_ECHO) //Si le tableau des dur�es d'�cho est rempli
            {
                g_compteEcho = 0; //Le compte des �chos est remis � z�ro
            }
            
			T3CONbits.TMR3ON = 0; //Le timer 3 est arr�t�
            PORTCbits.RC0 = 0; //La DEL jaune est �teinte d�s que le front descendant de l'echo a �t� d�tect�
        }
       
        CCP1CONbits.CCP1M = 0b0100; //Le module CCP1 est utilis� en mode capture pour chaque front descendant du signal d'echo � percevoir
        PIR1bits.CCP1IF = 0; //On remet � z�ro le flag d'interruption du module CCP1
    }
}

/* Low-priority interrupt service routine */
void __interrupt(low_priority) low_isr(void)
{
    //Il n'y a rien � ajouter ici pour le laboratoire 1
}
