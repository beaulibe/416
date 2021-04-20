/**
 * @file   initialisation.c
 * @author Richard Cloutier, Benoit Beaulieu (février 2020)
 *
 */
#ifndef INITIALISATION_H
#define	INITIALISATION_H

//#include "commun.h"
#include <xc.h>
#include <stdbool.h>


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

    ADCON1 = 0; //A0..A5 en mode anal (18F458) V- à VSS et V+ à VDD

    ADCON0bits.ADON = 1; //Convertisseur AN à on
    ADCON1bits.ADFM = 0; //Alignement à gauche des 10bits de la conversion (8 MSB dasn ADRESH, 2 LSB à gauche dans ADRESL)

    
    ADCON0bits.ADCS = 0b10; //Fosc/64 (Fréquence pour la conversion la plus longue possible)
    ADCON1bits.ADCS2 = 1; // 3e bit de ADCS pour Fosc/64

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
    //Étapes pour setup PWM page 129 

    //#1 Période PWM
    //Calculs: Période du PWM = (PR2 + 1) x 4 x (1/16MHz) x Prescaler Tmr2 
    //PR2 = 255 et psc tmr2 = 16 donc Tpwm = 1.024 msec
    //Note: si on veut 1ms pile alors PR2 = 249
    PR2 = 255;
    
    //#2 PWM Duty cycle
    CCPR1L = 0x80; //50% 10 bits -> 1024. 50% de 1024 = 512 = (0b1000000000)
    CCP1CONbits.DC1B = 0b00;


    //#3
    TRISCbits.RC2 = 0; //broche de sortie reliée au moteur
    

    //#4 init du timer 2
    PIR1bits.TMR2IF = false;
    T2CONbits.T2CKPS = 3; //Prescaler 1:16
    T2CONbits.TMR2ON = 1; //Timer2 ON

    
    //#4
    CCP1CONbits.CCP1M = 0b1111; //mode PWM
       
}

/**
 * @brief Configuration Timer 0
 */
void initialisation_ConfigTmr0(void)
{
    T0CONbits.TMR0ON = 0; //à off au début
    T0CONbits.T08BIT = 0; //0=16bits
    T0CONbits.PSA = 0; //0 = on utilise. 1 = on utilise PAS de psc
    T0CONbits.T0CS = 0;
    T0CONbits.T0PS = 0b000; //0b000 = psc/2    
    INTCONbits.TMR0IE = 1;
    
 
   /* //1MHz/4/4/2500 = 25Hz -> 65536-63036 = 2500 ->63036=0xF63C
    TMR0H = 0xF6;
    TMR0L = 0x3C;*/

    //1MHz/4/2/3571 = 35Hz -> 65536-61976 = 3571 ->61976=0xF20D
    TMR0H = 0xF2;
    TMR0L = 0x0D;


}


/**
 * @brief Configuration Timer 3
 */
void initialisation_ConfigTmr3(void)
{
    //1MHz/4/65536 = 3,8Hz -> 260ms
    T3CON = 1; //valeurs par défaut sont tous ok
    PIE2bits.TMR3IE = 1; //interruptions permises
    TRISCbits.RC0 = 0; //en sortie pour voir effet sur del
}





#endif	/* INITIALISATION_H */

