/**
 * @file   main.c
 * @author Benoit Beaulieu
 * @date   Février 2020
 * @brief  Le programme utilise un servomoteur pour simuler les mouvents d'un essuie-glace d'automobile.
 * Le programme doit faire bouger le moteur selon la position du potentiomètre. 
 * Les DEL vertes indiqueront le mode de déplacement du moteur.
 * Potentiomètre 0%-15% : mode arrêt, DEL = 000 (tous éteintes) 
 * Potentiomètre 15%-30% : mode délai 3 sec, DEL = 001 (DEL0 allumées, les autres éteintes) 
 * Potentiomètre 30%-45% : mode délai 2 sec, DEL = 010 
 * Potentiomètre 45%-60% : mode vitesse lente, DEL = 011 
 * Potentiomètre 60%-75% : mode vitesse moyenne, DEL = 100 
 * Potentiomètre 75%-100% : mode vitesse rapide, DEL = 101
 * 
 * @materiel  PIC 18F458, OSCILLATEUR 1MHz, Servo moter sur RC2 (broche 17), 
 * 3 DELs sur RD5 à RD7, potentiomètre relié à A0
 
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
extern unsigned int g_compteurTmr3;

int g_etat = enumArret;
unsigned char g_chargeTMR0 = TMR0_VITE; //défini dans commun.h


/**
 * @brief Fonction qui sert à gérer l'initialisation des différents registres et variables.
 */
void initialisation(void)
{
    initialisation_ConfigurerPortDSortie();
    initialisation_ConfigurerAdc();
    initialisation_ActiverIntAdc();
    initialisation_ActiverPWM();
    initialisation_ConfigTmr0(); //Pour rapidité du wiper
    initialisation_ConfigTmr3(); //Utilisé pour la duré des //delais des états enumDelaiUn à enumDelaiTrois
    initialisation_ActiverInterruptions();
    
}

void main(void)
{
    unsigned char dutyWiper = PWM_MIN;
    
    initialisation();
    //T0CONbits.TMR0ON = 1;
    CCPR1L = PWM_MIN; //replacer le wiper à 0
    
    // Boucle principale du programme

    while(1)
    {

        //La conversion analogique détermine l'état (g_etat) de la machine à état
        g_etat = g_resAN * enumEtatMax / 256; 
        PORTD = g_etat << 5; //3LSB g_etat placé sur les 3 DELs pour voir dans quel état on est
        
        switch (g_etat)
        {
            case enumArret :
                 //rien à faire, on attend que l'interrupt du tmr0 arrête le wiper
                 //T0CONbits.TMR0ON = 0; //arrêt du tmr0
                 //CCPR1L = PWM_MIN; //replacer le wiper à 0
                  
            break;

            case enumDelaiUn : 
                if (g_compteurTmr3 > 15) //15 x 260ms 
                {
                    //__delay_ms(2000);
                    g_chargeTMR0 = TMR0_MOYEN;
                    T0CONbits.TMR0ON = 1; //part  tmr0. Sera arrêté dans interrupt du tmr0
                    g_compteurTmr3 = 0;
                }
             break;

            case enumDelaiDeux : 
                if (g_compteurTmr3 > 11) //12 x 260ms 
                {
                    g_chargeTMR0 = TMR0_MOYEN;
                    T0CONbits.TMR0ON = 1; //part  tmr0. Sera arrêté dans interrupt du tmr0
                    g_compteurTmr3 = 0;
                }
            break;
            
            case enumLent : 
                g_chargeTMR0 = TMR0_LENT;
                T0CONbits.TMR0ON = 1; //part tmr0
            break;
            
            case enumMoyen : 
                g_chargeTMR0 = TMR0_MOYEN;
                T0CONbits.TMR0ON = 1; //part  tmr0
            break;

            case enumVite : 
                g_chargeTMR0 = TMR0_VITE;
                T0CONbits.TMR0ON = 1; //part  tmr0
            break;
                
            
        }
    }
}