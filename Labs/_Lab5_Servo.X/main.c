/**
 * @file   main.c
 * @author Benoit Beaulieu
 * @date   Février 2020
 * @brief  PWM pour le servo moteur sur RC2. 
 * @materiel  PIC 18F458, OSCILLATEUR 1MHz, Servo moter sur RC
 
 */

#include <xc.h>
#include "initialisation.h"
#include "commun.h"
#include <stdbool.h>


/****** Constantes ************/
#define _XTAL_FREQ 1000000 //Constante utilisée par delaisMS(x). Doit = fréq interne du uC
                           // ********* ON A CHANGER L'OSCILLATEUR DU MONTAGE POUR ÊTRE PLUS LENT


/****** Var glogales *************/
extern int g_resAN; //8 bits de poids fort de la conversion A/N
int g_etat = enumArret;

/**
 * @brief Fonction qui sert à gérer l'initialisation des différents registres et variables.
 */
void initialisation(void)
{
    initialisation_ConfigurerPortDSortie();
    initialisation_ConfigurerAdc();
    initialisation_ActiverIntAdc();
//    initialisation_ActiverPWM();
  //  initialisation_ActiverTmr0(); //Pour rapidité du wiper
    initialisation_ConfigTmr3(); //Utilisé pour la duré des //delais des états enumDelaiUn à enumDelaiTrois
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
        

        //La conversion analogique détermine l'état (g_etat) de la machine à état
        g_etat = g_resAN * enumEtatMax / 256; 
        
        switch (g_etat)
        {
            case enumArret :
                /****** tester si on arrete avec TMR0ON ou avec INTCONbits.TMR0IE = 0 ??????? *********/
                T0CONbits.TMR0ON = 0; //arrêt du tmr0
            break;
            case enumLent : 
                T0CONbits.T0PS = 2; // psc/8
             //   T0CONbits.TMR0ON = 1; //part du tmr0
            break;
            
            case enumMoyen : 
                T0CONbits.T0PS = 1; // psc/4
              //  T0CONbits.TMR0ON = 1; //part du tmr0
            break;
            case enumVite : 
                T0CONbits.T0PS = 0; // psc/2
              //  T0CONbits.TMR0ON = 1; //part du tmr0
            break;
            case enumDelaiUn : 
           //     T3CONbits.TMR3ON = 1; //part du tmr3
            break;

            
            
               

        }
    }
}