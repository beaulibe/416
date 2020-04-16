/**
 * @file   main.c
 * @author Benoit Beaulieu
 * @date   Avril 2020
 * @brief  Sem11 no 2. Minuterie d'une bombe.
 * Question #2: Sur votre carte PicKit4, écrivez un programme qui gère la 
 * minuterie d?une bombe.  Au départ, la valeur de la minuterie est de 127 et 
 * est affichée sur les DEL. Lorsqu?on appuie sur SW1 la minuterie démarre. 
 * Le Timer0 est utilisé pour décrémenter le compte de la minuterie (i.e. de 
 * 127 à 0) à toutes les 50ms.
 *  Lorsque la minuterie arrive à 0, la bombe explose (ie toutes les DEL se 
 * mettent à clignoter).
 * Contraintes: 
	SW1 est lu par scrutation. 
	Le Timer0 est configuré en mode 16 bits. 
	Le diviseur (prescaler) du Timer0 = 4
 */


#include <xc.h>

#define _XTAL_FREQ 1000000

void initialisation(void);

//unsigned char decompte;



void main(void)
{
    initialisation();

    // Boucle principale du programme
    while(1)
    {
      
        if (PORTBbits.RB0 == 0)  //sw1 appuyé
        {
            while (PORTBbits.RB0 == 0); //on attend que sw1 soit relaché

            T0CONbits.TMR0ON    = 1;
            
        }
        
        if (PORTD == 0)
        {
            while(1) //on reste ici
            {
            PORTD =  ~PORTD;
            __delay_ms(500);
            }
        }

        
    }
}
/**
 * @brief Fonction qui sert à gérer l'initialisation des différents registres et variables.
 */
void initialisation(void)
{
    /****** SW1 *******/
    TRISBbits.TRISB0    = 1;    // PORTB bit 0 en entree
    ANSELH              = 0; // RB(0:4) en mode digital. Sur le 18F45K20 AN et PortB sont sur les memes broches

    /*********DEL ********/
    TRISD = 0;  //En sortie pour les dels
    PORTD = 127;
    
    /****** Timer 0 ********/
    T0CONbits.T08BIT    = 0; // mode 16 bits
    T0CONbits.T0CS      = 0;
    T0CONbits.PSA       = 0; // on utilise un prescaler
    T0CONbits.T0PS      = 1; // prescaler = 4

    // calcul de la valeur à mettre dans les registres pour avoir un délai = 50ms (20Hz)
    // FOSC/4 = 1MHz/4 = 250 KHz
    // 250KHz / 4 = 62500
    // 62500 KHz / 3125 = 20Hz
    TMR0 = 62411; //65536 - 3125

    INTCONbits.TMR0IE   = 1;  // timer 0 interrupt enable
    INTCONbits.TMR0IF   = 0; // timer 0 interrupt flag
    T0CONbits.TMR0ON    = 0; //on ne démarre pas tout de suite le tmr0

    /******* Interruptions *******/
    INTCONbits.PEIE = 1; //permet interruption des périphériques
    INTCONbits.GIE = 1;  //interruptions globales permises

    
    //TRISCbits.RC1 = 0; //Active broche en sortie
}