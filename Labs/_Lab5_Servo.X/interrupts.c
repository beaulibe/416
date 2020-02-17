/**
 * @file   interrupts.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Ce fichier contient la gestion des diff�rentes interruptions.
 * @version Benoit Beaulieu, f�vrier 2020
 */

//#include "commun.h"
#include <xc.h>
#include <stdbool.h>
#include "commun.h"



/** valeur � utiliser pour la sortie PWM */
//int valeurPwm_                  = 0;
/** valeur obtenue suite � la conversion A/N */
int g_resAN = 0; //8 bits de poids fort de la conversion A/N
unsigned int g_compteurTmr3 = 0;
extern unsigned char g_chargeTMR0;
extern int g_etat;  



/**
 * @brief Fonction qui re�oit les appels d'interruptions "high"
 */
//void interrupt high_isr(void)
void __interrupt(high_priority) high_isr(void)
{
    static unsigned char dutyWiper = PWM_MIN;
    static bool sensUp = true;
    static int compte = 0; //pour le timer 0
    
    // ***** conversion A/N ********
    if (PIR1bits.ADIF)     
    {
        g_resAN = ADRESH;  // le r�sultat de la conversion est configur� comme etant align� � GAUCHE
        
        PIR1bits.ADIF = false;          // baisser l'indication de l'interruption
        ADCON0bits.GO_DONE = true;      // d�marrer une autre conversion
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
                if (g_etat <= enumDelaiDeux )
                {
                    T0CONbits.TMR0ON = 0; //arr�t du tmr0
                    //g_compteurTmr3 = 0;
                    
                }
                sensUp = true;
            }
        }   

       // PORTDbits.RD7 = PORTDbits.RD7 ^ 1; //DEL rouge toggle
        INTCONbits.TMR0IF = 0;

        //1MHz/4/2/3571 = 35Hz -> 65536-61976 = 3571 ->61976=0xF20D
    //    TMR0H = 0xF2;
    //    TMR0L = 0x0D;
 
        TMR0H = g_chargeTMR0;
        //TMR0H = 0xF2;
        TMR0L = 0x00;
        

        
    }
        
    // ***** Tmr3 ****** 
     if (PIR2bits.TMR3IF)     
     {  
        g_compteurTmr3++;

        PORTCbits.RC0 = PORTCbits.RC0 ^ 1; //DEL  toggle
        PIR2bits.TMR3IF = 0;
     } 


        
    


}

