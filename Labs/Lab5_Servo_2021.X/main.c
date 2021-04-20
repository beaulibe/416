/**
 * @file   main.c
 * @author Benoit Beaulieu
 * @date   F�vrier 2020
 * @brief  Le programme utilise un servomoteur pour simuler les mouvents d'un essuie-glace d'automobile.
 * Le programme doit faire bouger le moteur selon la position du potentiom�tre. 
 * Les DEL vertes indiqueront le mode de d�placement du moteur.
    Potentiom�tre 0%-17% : mode arr�t, DEL = �teinte
    Potentiom�tre 17%-33% : mode d�lai 3 sec, DEL = Rouge
    Potentiom�tre 33%-50% : mode d�lai 2 sec, DEL = Vert
    Potentiom�tre 50%-67% : mode vitesse lente, DEL = Jaune
    Potentiom�tre 67%-83% : mode vitesse moyenne, DEL = Bleu
    Potentiom�tre 83%-100% : mode vitesse rapide, DEL = Mauve
 * 
 * @materiel  PIC 18F458, OSCILLATEUR 1MHz, Servo moter sur RC2 (broche 17), 
 * 3 DELs sur RD5 � RD7, potentiom�tre reli� � A0
 
 */

#include <xc.h>
#include "initialisation.h"
#include "commun.h"
#include <stdbool.h>


/****** Constantes ************/
#define _XTAL_FREQ 1000000 //Constante utilis�e par delaisMS(x). Doit = fr�q interne du uC
                           // ********* ON A CHANGER L'OSCILLATEUR DU MONTAGE POUR �TRE PLUS LENT


/****** Var glogales *************/
extern int g_resAN; //8 bits de poids fort de la conversion A/N. Lu par interruption dans interrupts.c
extern unsigned int g_compteurTmr3; //pour les 2 modes d�lais.

int g_etat = enumArret; //defini dans main.c
unsigned char g_chargeTMR0 = TMR0_VITE; //pour dicter et changer le temps entre les interruptions du timer 0


/**
 * @brief Fonction qui sert � g�rer l'initialisation des diff�rents registres et variables.
 */
void initialisation(void)
{
    initialisation_ConfigurerPortDSortie();
    initialisation_ConfigurerAdc();
    initialisation_ActiverIntAdc();
    initialisation_ActiverPWM();
    initialisation_ConfigTmr0(); //Pour rapidit� du wiper
    initialisation_ConfigTmr3(); //Utilis� pour la dur� des //delais des �tats enumDelaiUn � enumDelaiTrois
    initialisation_ActiverInterruptions();
    
}

void main(void)
{
    initialisation();

    CCPR1L = PWM_MIN; //replacer le wiper � 0
    
    // Boucle principale du programme

    while(1)
    {

        //La conversion analogique d�termine l'�tat (g_etat) de la machine � �tat
        g_etat = g_resAN * enumEtatMax / 256; 
        
        PORTD = (~g_etat) << 5; //3LSB g_etat plac� sur les 3 DELs pour voir dans quel �tat on est
                                //On doit inverser avec ~ car la DEL RGB est � annode commune
        
        switch (g_etat)
        {
            case enumArret :
                 //rien � faire, on attend que l'interrupt du tmr0 arr�te le wiper
                 //T0CONbits.TMR0ON = 0; //arr�t du tmr0
                 //CCPR1L = PWM_MIN; //replacer le wiper � 0
                  
            break;

            case enumDelaiUn : 
                if (g_compteurTmr3 > 15) //15 x 260ms 
                {
                    T0CONbits.TMR0ON = 1; //part  tmr0. Sera arr�t� dans interrupt du tmr0
                    g_compteurTmr3 = 0;
                }
                g_chargeTMR0 = TMR0_MOYEN;
             break;

            case enumDelaiDeux : 
                if (g_compteurTmr3 > 11) //12 x 260ms 
                {
                    T0CONbits.TMR0ON = 1; //part  tmr0. Sera arr�t� dans interrupt du tmr0
                    g_compteurTmr3 = 0;
                }
                g_chargeTMR0 = TMR0_MOYEN;
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