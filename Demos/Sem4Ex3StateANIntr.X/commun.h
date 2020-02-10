/**
 * @file   Commun.h
 * @author Richard Cloutier
 * @date   Janvier 2014
 * @brief  Fichier qui contient les "includes" nécessaires pour le projet. 
 *         Les définitions des fonctions partagées et des variables globales
 *         entre les différents fichiers.c sont faites ici.
 *
 */

#ifndef COMMUN_H
#define COMMUN_H

#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */



//variables globales
int etat_ = 0; //pour conserver l'état de la machine à états finis

/** Énumération utilisée pour définir les différents modes d'opération */
enum
{
    enumEtat0 = 0,
    enumEtat1,
    enumEtat2,
    enumEtat3,
    enumEtatMax
};


/**
 * @brief Fonction utilitaire pour permettre de gérer des délais fixe (CODE BLOQUANT!!!)
 * @param delai_ms valeur en ms du delai voulu
 */
void commun_delaiMS(uint16_t delai_ms);

#endif