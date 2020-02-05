/**
 * @file   main.c
 * @author Benoit Beaulieu
 * @date   Janvier F�vrier 2020
 * @brief  PWM pour le servo moteur sur RC2. 
 
 */

#include <xc.h>
#include "initialisation.h"
#include <stdbool.h>

/****** Constantes ************/
#define _XTAL_FREQ 1000000 //Constante utilis�e par delaisMS(x). Doit = fr�q interne du uC

#define PWM_MIN 9
#define PWM_MAX 0x25
extern int g_resAN;

/**
 * @brief Fonction qui sert � g�rer l'initialisation des diff�rents registres et variables.
 */
void initialisation(void)
{
    initialisation_ConfigurerPortDSortie();
    initialisation_ConfigurerAdc();
    initialisation_ActiverIntAdc();
    initialisation_ActiverPWM();
    initialisation_ActiverTmr0(); //Pour rapidit� du wiper
    initialisation_ActiverInterruptions();
    
}

void main(void)
{
    unsigned char dutyWiper = PWM_MIN;
    bool sensUp = true;
    
    initialisation();

    // Boucle principale du programme
    //On affichera sur la Del7 la sortie du PWM
    while(1)
    {
        //nous permet de voir si conversion analog fonctionne
        if (g_resAN > 128)
            PORTDbits.RD7 = 1; //DEL rouge on
        else
            PORTDbits.RD7 = 0; //DEL rouge off
         
//        CCPR1L = g_resAN; // on change le duty cycle du PWM
        
/*        CCPR1L = dutyWiper;
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
                sensUp = true;
        }   
        __delay_ms(30);
*/
    }
}