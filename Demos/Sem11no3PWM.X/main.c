/**
 * @file   main.c
 * @author Benoit Beaulieu
 * @date   Avril 2020
 * @brief  Sem11No3
 * Question 3 Sur votre carte PicKit4, �crivez un programme qui g�n�re un signal 
 * MLI sur la broche RC1. 
 *	La p�riode du signal = 500uSec
 *	Le temporisateur (timer) associ� au CCP2 sera le Timer2.
 *	Le cycle (duty cycle) varie entre 10% et 90%. Il augmente de 10% � chaque 
 * fois qu?on appuie sur SW1. Apr�s 90%, il revient � 10%.
 * Note : Aucune m�thode d?interruption n?est requise pour ce programme

 */

#include "xc.h"          /* Include generaux au programme */

void initialisation(void);



void main(void)
{
    int MLIpourCent =  10;
    initialisation();
    

    // Boucle principale du programme
    //On affichera sur la Del7 la sortie du PWM
    while(1)
    {
        if (PORTBbits.RB0 == 0)  //sw1 appuy�
        {
            while (PORTBbits.RB0 == 0); //on attend que sw1 soit relach�
            MLIpourCent += 10;
            if (MLIpourCent == 100)
                MLIpourCent = 10;
            
        }
        CCPR2L = (MLIpourCent * 124 / 100); // on change le duty cycle du PWM
    }
}

/**
 * @brief Fonction qui sert � g�rer l'initialisation des diff�rents registres et variables.
 */
void initialisation(void)
{
    /****** SW1 *******/
    TRISBbits.TRISB0    = 1;    // PORTB bit 0 en entree
    ANSELH              = 0; // RB(0:4) en mode digital. Sur le 18F45K20 AN et PortB sont sur les memes broches

    
    /******** PWM ***********/
    //voir section 11.4.7 (p152) fiches du 18F45K20
    //#1
    TRISCbits.RC1 = 1; //PWM sur RC1

    //#2 ECCP only

    //#3 P�riode PWM
    //Calculs: P�riode du PWM = (PR2 + 1) x 4 x (1/1MHz) x Prescaler Tmr2 (voir p150 equ 11.1)
    //PR2 = 124 et psc tmr2 = 1 donc Tpwm = 500 usec
    PR2 = 124;
    
    
    //#4
    CCP2CONbits.CCP2M = 0b1111; //mode PWM
    

    //#5 PWM Duty cycle
    CCPR2L = 12; //10% = x/4*(124+1) -> x = 50 -> 0b110010 
    CCP2CONbits.DC2B = 0b00;

    //#6 init du timer 2
    PIR1bits.TMR2IF = 0;
    T2CONbits.T2CKPS = 0; //Prescaler 1:16
    T2CONbits.TMR2ON = 1; //Timer2 ON
    
    //#7
    while (PIR1bits.TMR2IF ==0); //Attend 1 overflow du timer2
    TRISCbits.RC1 = 0; //PWM sur broche P1D/RD7



}
