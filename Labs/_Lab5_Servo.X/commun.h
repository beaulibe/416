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
#define TMR0_VITE 0xF2
#define TMR0_MOYEN 0xED
#define TMR0_LENT 0xE8


#endif