/**
 * @file   main.c
 * @author Benoit Beaulieu
 * @date   Avril  2020
 * @brief  Exercice 2 de la semaine 10
 */

#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#define _XTAL_FREQ 1000000

/*************var globales *************/
extern unsigned char g_rxCar;


const unsigned char msg[] = "Bravo!";

/*********** prototypes *****************/
void initialisation(void);

void main(void)
{
    int i = 0;
    
    
    initialisation();
    
    //On clignote D0 3x pour montrer le départ du programme
    for (int i = 0; i < 1226; i++)
    {
        PORTDbits.RD0 ^= 1;
        __delay_ms(2000);
        TXREG = 'G';
    }
    
    
    while(1) //Boucle principale du programme
    {
        if (g_rxCar == 'A')
        {
            i = 0;
            while (msg[i] != '\0')
            {
                TXREG = msg[i];
                i++;
            }          
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
    //1. Initialize the SPBRG register for the appropriate
    //baud rate. If a high-speed baud rate is desired,
    SPBRG = 25; //9600bps Voir tableau p187. Osc = 40MHz 
	//à tester.... Devrait plutôt être 25. Fosc = 1MHz. Tableau 18-5. Page 250
    
        //set bit BRGH (Section 18.1 ?USART Baud
    //Rate Generator (BRG)?).
    TXSTAbits.BRGH = 1; //Low speed. 0 = valeur par défaut
    BAUDCONbits.BRG16 = 1;

    
    
    
    //2. Set the RX/DT and TX/CK TRIS controls to ?1?.
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    
    //6. Enable the transmission by setting the TXEN
    //control bit. This will cause the TXIF interrupt bit to be set.
    TXSTAbits.TXEN = 1;
    
    //7. If interrupts are desired, set the TXIE interrupt
    //enable bit. An interrupt will occur immediately
    //provided that the GIE and PEIE bits of the INTCON register are also set.
    //NON, on ne veut pas d'interruptions lors de la transmission
    
    
    //3. Enable the asynchronous serial port by clearing
    //bit SYNC and setting bit SPEN.
    RCSTAbits.SPEN = 1; // 1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins) 
    TXSTAbits.SYNC = 0; //0 = Asynchronous mode 
 
    //7. Enable reception by setting the CREN bit
    RCSTAbits.CREN = 1;
    
    PIE1bits.RC1IE = 1; //permet interruption en réception
    
    
    //Interruptions générales
    INTCONbits.PEIE = 1; //permet interruption des périphériques
    INTCONbits.GIE = 1;  //interruptions globales permises
}