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
    enumLent,  
    enumMoyen,   
    enumVite,  
    enumDelaiUn,
    enumDelaiDeux,
    enumDelaiTrois,
    enumEtatMax
};

#define PWM_MIN 9
#define PWM_MAX 0x25

#endif