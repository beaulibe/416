/**
 * @file   main.c, projet Sem4Ex3StateAN
 * @author Benoit Beaulieu
 * @date   26 Janvier 2015
 * @brief  Exercice sur d'une machine à états finis. Sw1 nous permet de changer
 *         d'état. Les DEL servent à savoir dans quel état on est.
 *              État0 = Les del affichent le code binaire d'une variable qui s'incrémente à toutes les 250ms.
 *              État1 = Deux dels se déplacent de D0 à D7 à toutes les 250ms.
 *              État2 = Une del éteinte (les autres étant allumées) se déplace de D7 à D0 à toutes les 250ms.
 *              État3 = On affiche le résultat de la converaions AN (8 bits de poids fort) du pot sur les DELS
 
 */

#include "xc.h"
#include "interrupts.h"

 #define _XTAL_FREQ 1000000 // Definition pour utiliser les fonctions de délais.

int g_etat = 0;

//Prototypes des fonctions
void initialisation(void);


void main(void)
{
    

    initialisation();

    PORTD = 0;  //on éteind toutes les dels au départ


    while(1) // Boucle principale du programme
    {

         switch(g_etat)  //on branche sur l'état actuel
        {
            case    enumEtat0:  //Les dels s'incrémentent aux 250ms
                PORTD++;
                break;
                
            case    enumEtat1: //Deux dels se déplacent de D0 à D7 à toutes les 250ms.
            
                if (PORTD == 0 ) //viens d'arriver à l'état 1
                    PORTD = 3;  //allumne d0 et d1
                
                PORTD = PORTD << 1;  //on décale vers la gauche

                if (PORTD == 0b10000000)  //1ère del arrivée à d7,
                    PORTD =  0b10000001;  //on doit la remettre à d0
                
                if (PORTD == 0b00000010) //2e del arrivée à d7
                    PORTD =  0b00000011;  //on doit la remettre à D0
                break;
                
            case    enumEtat2: //Une del éteinte (les autres étant allumées) se déplace de D7 à D0 à toutes les 250ms.
                
                if (PORTD == 0 ) //viens d'arriver à l'état 2
                    PORTD = 0x7F; //juste d7 d'éteinte
                
                PORTD = PORTD >> 1; //décale vers la droite
                if (PORTD != 0x7F)  // si ce n'est pas d7 qui est éteinte
                    PORTDbits.RD7 = 1;  //on doit ralumer d7, car a été éteinte lors du décalage à droite
                break;
                
            case    enumEtat3: //On affiche le résultat de la converaions AN (8 bits de poids faible) du pot sur les DELS
                ADCON0bits.GO_DONE = 1;  //lance une conversion
                while (ADCON0bits.GO_DONE == 1); //attend fin de la conversion
                PORTD = ADRESL; //on afficher seulement les 8 LSB.

                break;

             default:
                break;
        }

        
         if (g_etat < enumEtat3)  //pas de délais à l'état 3
             __delay_ms(250);

    }
}


/**
 * @brief Fonction qui sert à gérer l'initialisation des différents regesitres du Pic
 */
void initialisation(void)
{
    //initialisation pour Int0
    INTCON2bits.INTEDG0 = 0;    // front descendant
    INTCONbits.INT0IF   = 0;    // assurer que l'evenement soit a 0
    INTCONbits.INT0E    = 1;    // enable int 0

    INTCONbits.GIE = 1;  //interruptions globales permises

    TRISBbits.TRISB0    = 1;    // PORTB bit 0 en entree
    ANSELH              = 0; // RB(0:4) en mode digital. Sur le 18F45K20 AN et PortB sont sur les memes broches

    TRISD = 0; //Tout le port D en sortie

    //Configuration du port analogique
    ANSELbits.ANS0 = 1;  //A0 en mode analogique
    ADCON0bits.ADON = 1; //Convertisseur AN à on
    ADCON1bits.VCFG1 = 0; //Tension de référence V- reliée à VSS
    ADCON1bits.VCFG0 = 0; //Tension de référence V+ reliée à VDD
    ADCON2bits.ADFM = 1; //Alignement à droite des 10bits de la conversion (2 MSB dans ADRESH, 8 LSB à dans ADRESL)
    ADCON2bits.ACQT = 7; //20 TAD (on laisse le max de temps au Chold du convertisseur AN pour se charger)
    ADCON2bits.ADCS = 6; //Fosc/64 (Fréquence pour la conversion la plus longue possible)
    
    
    
}

