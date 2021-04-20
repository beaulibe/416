/**
 * @file   Commun.h
 * @author Benoit Beaulieu  
 * @date   Février 2020
 * @brief  Définitions communes
 */

#ifndef COMMUN_H
#define COMMUN_H


enum enumModes
{
    enumArret = 0,
    enumDelaiUn,
    enumDelaiDeux,
    enumLent,  
    enumMoyen,   
    enumVite,  
    enumEtatMax
};

#define PWM_MIN 9
#define PWM_MAX 0x25

//Valeurs des 8 bits de poids fort pour la recharge du tmr0. Dicte vitesse du wiper
//Calculs: 1MHz/4/2/3571 = 35Hz -> 65536-61976 = 3571 ->61976=0xF20D
#define TMR0_VITE 0xF2 //    1MHz/4/2/3571 = 35Hz -> 65536-61976 = 3571 ->61976=0xF20D
#define TMR0_MOYEN 0xED  //   1MHz/4/2/4864 = 25Hz -> 65536-60672 = 4864 ->60672=0xF20D
#define TMR0_LENT 0xE8 //     1MHz/4/2/6144 = 20Hz -> 65536-59392 = 6144 ->61976=0xF20D


#endif