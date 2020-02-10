/**
 * @file   main.c, projet Sem4Ex3StateAN
 * @author Benoit Beaulieu
 * @date   26 Janvier 2015
 * @brief  Exercice sur d'une machine � �tats finis. Sw1 nous permet de changer
 *         d'�tat. Les DEL servent � savoir dans quel �tat on est.
 *              �tat0 = Les del affichent le code binaire d'une variable qui s'incr�mente � toutes les 250ms.
 *              �tat1 = Deux dels se d�placent de D0 � D7 � toutes les 250ms.
 *              �tat2 = Une del �teinte (les autres �tant allum�es) se d�place de D7 � D0 � toutes les 250ms.
 *              �tat3 = On affiche le r�sultat de la converaions AN (8 bits de poids fort) du pot sur les DELS
 
 */

#include "xc.h"
#include "interrupts.h"

 #define _XTAL_FREQ 1000000 // Definition pour utiliser les fonctions de d�lais.

int g_etat = 0;

//Prototypes des fonctions
void initialisation(void);


void main(void)
{
    

    initialisation();

    PORTD = 0;  //on �teind toutes les dels au d�part


    while(1) // Boucle principale du programme
    {

         switch(g_etat)  //on branche sur l'�tat actuel
        {
            case    enumEtat0:  //Les dels s'incr�mentent aux 250ms
                PORTD++;
                break;
                
            case    enumEtat1: //Deux dels se d�placent de D0 � D7 � toutes les 250ms.
            
                if (PORTD == 0 ) //viens d'arriver � l'�tat 1
                    PORTD = 3;  //allumne d0 et d1
                
                PORTD = PORTD << 1;  //on d�cale vers la gauche

                if (PORTD == 0b10000000)  //1�re del arriv�e � d7,
                    PORTD =  0b10000001;  //on doit la remettre � d0
                
                if (PORTD == 0b00000010) //2e del arriv�e � d7
                    PORTD =  0b00000011;  //on doit la remettre � D0
                break;
                
            case    enumEtat2: //Une del �teinte (les autres �tant allum�es) se d�place de D7 � D0 � toutes les 250ms.
                
                if (PORTD == 0 ) //viens d'arriver � l'�tat 2
                    PORTD = 0x7F; //juste d7 d'�teinte
                
                PORTD = PORTD >> 1; //d�cale vers la droite
                if (PORTD != 0x7F)  // si ce n'est pas d7 qui est �teinte
                    PORTDbits.RD7 = 1;  //on doit ralumer d7, car a �t� �teinte lors du d�calage � droite
                break;
                
            case    enumEtat3: //On affiche le r�sultat de la converaions AN (8 bits de poids faible) du pot sur les DELS
                ADCON0bits.GO_DONE = 1;  //lance une conversion
                while (ADCON0bits.GO_DONE == 1); //attend fin de la conversion
                PORTD = ADRESL; //on afficher seulement les 8 LSB.

                break;

             default:
                break;
        }

        
         if (g_etat < enumEtat3)  //pas de d�lais � l'�tat 3
             __delay_ms(250);

    }
}


/**
 * @brief Fonction qui sert � g�rer l'initialisation des diff�rents regesitres du Pic
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
    ADCON0bits.ADON = 1; //Convertisseur AN � on
    ADCON1bits.VCFG1 = 0; //Tension de r�f�rence V- reli�e � VSS
    ADCON1bits.VCFG0 = 0; //Tension de r�f�rence V+ reli�e � VDD
    ADCON2bits.ADFM = 1; //Alignement � droite des 10bits de la conversion (2 MSB dans ADRESH, 8 LSB � dans ADRESL)
    ADCON2bits.ACQT = 7; //20 TAD (on laisse le max de temps au Chold du convertisseur AN pour se charger)
    ADCON2bits.ADCS = 6; //Fosc/64 (Fr�quence pour la conversion la plus longue possible)
    
    
    
}

