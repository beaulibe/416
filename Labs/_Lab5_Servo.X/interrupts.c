/**
 * @file   interrupts.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Ce fichier contient la gestion des différentes interruptions.
 * @version Benoit Beaulieu, février 2020
 */

//#include "commun.h"
#include <xc.h>
#include <stdbool.h>

#define PWM_MIN 9
#define PWM_MAX 0x25


/** valeur à utiliser pour la sortie PWM */
//int valeurPwm_                  = 0;
/** valeur obtenue suite à la conversion A/N */
int g_resAN = 0; //8 bits de poids fort de la conversion A/N
extern int g_etat;  



/**
 * @brief Fonction qui reçoit les appels d'interruptions "high"
 */
void interrupt high_isr(void)
{
    static unsigned char dutyWiper = PWM_MIN;
    static bool sensUp = true;
    static int compte = 0; //pour le timer 0
    
    // ***** conversion A/N ********
    if (PIR1bits.ADIF)     
    {
        g_resAN = ADRESH;  // le résultat de la conversion est configuré comme etant aligné à GAUCHE
        
        PIR1bits.ADIF = false;          // baisser l'indication de l'interruption
        ADCON0bits.GO_DONE = true;      // démarrer une autre conversion
    }
    
    // ***** Tmr0 ******
    if (INTCONbits.TMR0IF)     
    {   

        CCPR1L = dutyWiper;
        if (sensUp)
        {
            dutyWiper++;
            if (dutyWiper >= PWM_MAX)
                sensUp = false;
        }
        else
        {
            dutyWiper--;
            if (dutyWiper <= PWM_MIN)
            {
                if (g_etat >= enumDelaiUn )
                {
                    T0CONbits.TMR0ON = 0; //arrêt du tmr0
                }
                sensUp = true;
            }
        }   

        INTCONbits.TMR0IF = 0;
        TMR0H = 0xE2;
        TMR0L = 0xB4;
    
        
       // ***** Tmr3 ****** 
        if (PIR2bits.TMR3IF)     
        {  

            compte++;
            
            if (g_etat == enumDelaiUn && compte > 10)
            {
                T0CONbits.T0PS = 1; // psc/4 ... On se met en mode moyen
                T0CONbits.TMR0ON = 1; //part le tmr0. Il y aura donc 1 coup de wiper. Le tmr0 se fermera dans l'interruption du tmr 0
                compte = 0;
            }
            
            PIR2bits.TMR3IF = 0;
        } 

        
        
    }


}

