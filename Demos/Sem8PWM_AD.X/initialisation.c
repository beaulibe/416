/**
 * @file   initialisation.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Contient la définition des prototypes de fonctions utilisés pour l'initalisation des différents registres de contrôle du PIC.
 * @version 1.1 Benoit Beaulieu, mars 2015
 *
 */
#ifndef INITIALISATION_H
#define	INITIALISATION_H

#include "commun.h"


/**
 * @brief Fonction utilisée pour configurer le PORTD en sortie.
 */
void initialisation_ConfigurerPortDSortie(void)
{
    TRISD = 0;
}

/**
 * @brief Fonction utilisée pour activer les interruptions (au global les activations spécifiques sont faites ailleurs).
 */
void initialisation_ActiverInterruptions(void)
{
    INTCONbits.PEIE = 1; //permet interruption des périphériques
    INTCONbits.GIE = 1;  //interruptions globales permises
}


/**
 * @brief Configuration du mode Analogique pour AN0
 */
void initialisation_ConfigurerAdc(void)
{
   //Configuration du port analogique
    TRISAbits.TRISA0 = 1; //A0 en entrée
    ANSELbits.ANS0 = 0;  //A0 en mode analogique

    ADCON0bits.ADON = 1; //Convertisseur AN à on
    ADCON1bits.VCFG1 = 0; //Tension de référence V- reliée à VSS
    ADCON1bits.VCFG0 = 0; //Tension de référence V+ reliée à VDD
    ADCON2bits.ADFM = 0; //Alignement à gauche des 10bits de la conversion (8 MSB dasn ADRESH, 2 LSB à gauche dans ADRESL)
    ADCON2bits.ACQT = 7; //20 TAD (on laisse le max de temps au Chold du convertisseur AN pour se charger)
    ADCON2bits.ADCS = 6; //Fosc/64 (Fréquence pour la conversion la plus longue possible)

}

/**
 * @brief Activer l'interruption de fin de conversion du ADC
 */
void initialisation_ActiverIntAdc(void)
{
        //Config AN par interruption
    PIR1bits.ADIF = false; //on reset le flag
    PIE1bits.ADIE = 1; //permet interruptions de l'AD
    ADCON0bits.GO_DONE = 1;  //lance une conversion
}

/**
 * @brief Configuration et activation de la ligne PWM
 */
void initialisation_ActiverPWM(void)
{
    //voir section 11.4.7 (p152) fiches du 18F45K20
    //#1
    TRISCbits.RC1 = 1; //PWM sur RC1

    //#2 ECCP only. Rien à faire car on n'utilise pas le mode enhanced

    //#3 Période PWM
    //Calculs: Période du PWM = (PR2 + 1) x 4 x (1/1MHz) x Prescaler Tmr2 (voir p150 equ 11.1)
    //PR2 = 255 et psc tmr2 = 1 donc Tpwm = 1.024 msec
    //Note: si on veut 1ms pile alors PR2 = 249
    PR2 = 249;
    
    
    //#4
    CCP2CONbits.CCP2M = 0b1111; //mode PWM
    

    //#5 PWM Duty cycle
    CCPR2L = 0x80; //50% 10 bits -> 1024. 50% de 1024 = 512 = (0b1000000000)
    CCP2CONbits.DC2B = 0b00;

    //#6 init du timer 2
    PIR1bits.TMR2IF = false;
    T2CONbits.T2CKPS = 3; //Prescaler 1:16
    T2CONbits.TMR2ON = 1; //Timer2 ON
    
    //#7
    while (PIR1bits.TMR2IF ==0); //Attend 1 overflow du timer2
    TRISCbits.RC1 = 0; //PWM sur broche P1D/RD7
        
}
#endif	/* INITIALISATION_H */

