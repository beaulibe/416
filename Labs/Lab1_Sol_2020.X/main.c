 /**
 * @file   main.c, projet Lab1
 * @author Benoit Beaulieu
 * @date   Janvier 2017
 * @brief  Programme du laboratoire 1 dans le cours 247-416-SH
 * @revision Jacob Deschamps, d�cembre 2018, modification du main
 * @revision Benoit Beaulieu, janvier 2020, modification du main 
 * Environnement:
 *     D�veloppement: MPLAB X IDE (version 5.30)
 *     Compilateur: XC8 (version 2.10)
 *     Mat�riel: Montage laboratoire 1 avec PIC 18F458
 */

/****** Include ************/
#include <xc.h>
#include "Lcd4Lignes.h"
#include "interrupts.h"

/****** Constantes ************/
#define _XTAL_FREQ 16000000 //Constante utilis�e par delaisMS(x). Doit = fr�q interne du uC



/****** Prototypes ************/
void initialisation(void);


/****** Variables globales ***************/
extern unsigned int  g_nombreCar; //Nombre de caract�res dans le tampon
extern unsigned char g_temponClavier[NOMBRE_CAR_MAX]; //Tampon de r�ception des caract�res

void main(void)
{
    initialisation(); //Initialise les ports et l,interruption INT0 du PIC18
    lcd_init(); //Initialise l'afficheur LCD
    
    PORTCbits.RC0 = 1; //Allume la DEL jaune
    __delay_ms(500);
    PORTDbits.RD7 = 1; //Allume la DEL rouge
    
	//Ajoutez du code ici pour afficher sur le LCD votre message "Lab1 VotreNom"
	
    lcd_putMessage("Lab1 Benoit 2020");
    while(1) // Boucle principale du programme
    {
		//Vous pouvez retirer les deux lignes de code ci-dessous pour le clignotement de la DEL. Elles ne
		//servent qu'� indiquer que le programme roule, mais ralentissent cependant l'affichage des touches
        PORTCbits.RC0 ^= 1; //La DEL jaune clignote (cela indique que le programme roule sur le PIC18)
         __delay_ms(50); //D�lai d'environ 50 ms
        
        //Ajoutez du code ici pour afficher sur le LCD les carct�res re�us du clavier
        if (g_nombreCar >= 1  ) //au moins un caractere recu
        {
            lcd_ecritChar(g_temponClavier[g_nombreCar-1]); //on l'affiche       
            g_nombreCar--; //y'en a un de moins dans le buffer
        }
   
    }
}

/**
 * @brief Fonction qui sert � g�rer l'initialisation des diff�rents regesitres et variables.
 */
void initialisation(void)
{
    //Ajoutez du code ici pour configurer les ports utilis�s sur le PIC18
    
    
    ADCON1 = 0x07; //Deactive fonction analogique du port A
    TRISA = 0; //PORT A  en sortie pour le LCD
    TRISBbits.RB4 = 0; //RB4 en sortie pour RS du LCD
    
    
    //***configs pour le clavier
    CMCON = 0x07;               // comparateurs OFF pour uiliser port D comme I/O digital
    TRISD = 0x7F;               // forcer le port D (D6 � D0) en entree (CLAVIER) et D7 en sortie pour DEL
    
    TRISC = 0;                  // port C en sortie (DEL sur RC0))
    
    
    //Ajoutez du code ici pour configurer l'interuption INT0
    TRISBbits.RB0 = 1;       // PORTB bit 0 en entree pour le strobe (INT0))
    // initialisation pour int0 du clavier
    INTCON2bits.INTEDG0 = 0;    // front descendant sur INT0
    INTCONbits.INT0IF = 0;      // reset flag interruption
    INTCONbits.INT0IE = 1;      // INT0 permise
    INTCONbits.GIE = 1;         //interruptions globales permises
    
    
    
   
}