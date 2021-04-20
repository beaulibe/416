/**
 * @file   main.c
 * @author Benoit Beaulieu
 * @date   Avril  2020
 * @brief  Exercice 1 de la semaine 10
 */

#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#define _XTAL_FREQ 1000000

/*********** prototypes *****************/
void initialisation(void);

void main(void)
{
    unsigned char carTx = 1;
    unsigned char carRx = 0;
    
    initialisation();
    
    //On clignote D0 3x pour montrer le départ du programme
    for (int i = 0; i < 6; i++)
    {
        PORTDbits.RD0 ^= 1;
        __delay_ms(300);
    }
    
    while(1) //Boucle principale du programme
    {
        TXREG = carTx++; //envoie au port série
         __delay_ms(500); //500ms entre chaque tx pour voir l'effet sur les DEL
        
         //lecture par pooling 
        if (PIR1bits.RC1IF == 1) //une donnée reçue
        {
            carRx = RCREG; //lecture au port série
            PORTD = carRx; //affiche la donnée reçu sur les DEL
        }
       
    }
    
}

/**
 * @brief Fonction qui sert à gérer l'initialisation des différents registres et variables.
 */
void initialisation(void)
{
    
    TRISD = 0; //port D en sortie
 
      
    /********** Transmission Communication série ************/
   //La vitesse de communication se configure via les registres SPBRG, TXSTA (bit BRGH) et BAUDCON (bit BRG16). Voir tableau 18-5 p248.
    SPBRG = 25; //9600bps Voir tableau p187. Osc = 1MHz
    TXSTAbits.BRGH = 1; //Low speed. 0 = valeur par défaut
    BAUDCONbits.BRG16 = 1;
    
    //Les broches TX et RX (RC6 et RC7) doivent être en entrée. 
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
     
    //Permettre la transmission via le bit TXEN du registre TXSTA.  
    TXSTAbits.TXEN = 1;
    TXSTAbits.TX9 = 0; //8 bits par carac.

     
    //Activer le port de communication asynchrone via le bit SPEN (=1) du registre RCSTA et le bit  SYNC (=0) du registre TXSTA.
    RCSTAbits.SPEN = 1; // 1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins) 
    TXSTAbits.SYNC = 0; //0 = Asynchronous mode 
    
    //Permettre la réception via le bit CREN du registre RCSTA.
    RCSTAbits.CREN = 1;
    RCSTAbits.RX9 = 0; //8 bits par carac.


    //Au besoin, permettre les interruptions lors de la réception d?une donnée par le bit RCIE du registre PIE1.	
    //PIE1bits.RC1IE = 1; //permet interruption en réception
    
    //Au besoin, permettre les interruptions des périphériques PEIE et les interruptions globales GIE.
    //INTCONbits.PEIE = 1; //permet interruption des périphériques
    //INTCONbits.GIE = 1;  //interruptions globales permises
}