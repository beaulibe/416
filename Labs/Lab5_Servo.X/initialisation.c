/**
 * @file   initialisation.c
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Contient la d�finition des prototypes de fonctions utilis�s pour l'initalisation des diff�rents registres de contr�le du PIC.
 * @version 1.1 Benoit Beaulieu, mars 2015
 *
 */
#ifndef INITIALISATION_H
#define	INITIALISATION_H

//#include "commun.h"
#include <xc.h>
#include <stdbool.h>


/**
 * @brief Fonction utilis�e pour configurer le PORTD en sortie.
 */
void initialisation_ConfigurerPortDSortie(void)
{
    TRISD = 0;
}

/**
 * @brief Fonction utilis�e pour activer les interruptions (au global les activations sp�cifiques sont faites ailleurs).
 */
void initialisation_ActiverInterruptions(void)
{
    INTCONbits.PEIE = 1; //permet interruption des p�riph�riques
    INTCONbits.GIE = 1;  //interruptions globales permises
}


/**
 * @brief Configuration du mode Analogique pour AN0
 */
void initialisation_ConfigurerAdc(void)
{
   //Configuration du port analogique
    TRISAbits.TRISA0 = 1; //A0 en entr�e

    ADCON1 = 0; //A0..A5 en mode anal (18F458) V- � VSS et V+ � VDD

    ADCON0bits.ADON = 1; //Convertisseur AN � on
    ADCON1bits.ADFM = 0; //Alignement � gauche des 10bits de la conversion (8 MSB dasn ADRESH, 2 LSB � gauche dans ADRESL)

    
    ADCON0bits.ADCS = 0b10; //Fosc/64 (Fr�quence pour la conversion la plus longue possible)
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
    //�tapes pour setup PWM page 129 

    //#1 P�riode PWM
    //Calculs: P�riode du PWM = (PR2 + 1) x 4 x (1/16MHz) x Prescaler Tmr2 
    //PR2 = 255 et psc tmr2 = 16 donc Tpwm = 1.024 msec
    //Note: si on veut 1ms pile alors PR2 = 249
    PR2 = 255;
    
    //#2 PWM Duty cycle
    CCPR1L = 0x80; //50% 10 bits -> 1024. 50% de 1024 = 512 = (0b1000000000)
    CCP1CONbits.DC1B = 0b00;


    //#3
    TRISCbits.RC0 = 1; //met RC0 en entr� car on va y shorter RC2 pour voir effet sur la DEL jaune
    TRISCbits.RC2 = 0;
    

    //#4 init du timer 2
    PIR1bits.TMR2IF = false;
    T2CONbits.T2CKPS = 3; //Prescaler 1:16
    T2CONbits.TMR2ON = 1; //Timer2 ON

    
    //#4
    CCP1CONbits.CCP1M = 0b1111; //mode PWM


    //#7 �tape 7 du 45k20
    while (PIR1bits.TMR2IF ==0); //Attend 1 overflow du timer2
    TRISCbits.RC1 = 0; //PWM sur broche P1D/RD7
       
}

/**
 * @brief Configuration et activation de la ligne PWM
 */
void initialisation_ActiverTmr0(void)
{
    T0CONbits.TMR0ON = 1;
    T0CONbits.PSA = 0; //on utilise un psc
    T0CONbits.T0CS      = 0;
    INTCONbits.TMR0IE = 1;
    TMR0H = 0xE2;
    TMR0L = 0xB4;
}


#endif	/* INITIALISATION_H */

