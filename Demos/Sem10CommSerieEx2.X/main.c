/**
 * @file   main.c
 * @author Benoit Beaulieu
 * @date   Avril  2020
 * @brief  Exercice 2 de la semaine 10
 * Relier TX (RC6) du PIC sur RXD de la clé usb.
 * Relier RX (RC7) du PIC sur TXD de la clé usb.
 * Note: On doit alimenter la carte par un pwr supply 3.3V externe, car si on 
 * aliment par usb, ça cause des problèmes.
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
    while(PIR1bits.TXIF==0); //on attend que le registe de transmission soit prêt 
    TXREG = 'G'; 
    PORTDbits.RD0 ^= 1;
    while(PIR1bits.TXIF==0); //on attend que le registe de transmission soit prêt     
    TXREG = 'O';     
    while(1) //Boucle principale du programme
    {
        if (g_rxCar == 'A')
        {
            i = 0;
            while (msg[i] != '\0')
            {
                while(PIR1bits.TXIF==0); //on attend que le registe de transmission soit prêt 
                TXREG = msg[i];
                i++;
                //__delay_ms(10);
            }  
            g_rxCar = 0;
        }          
    }
}

/**
 * @brief Fonction qui sert à gérer l'initialisation des différents registres et variables.
 */
void initialisation(void)
{
    
    TRISD = 0; //port D en sortie
 
    
    //La vitesse de communication se configure via les registres SPBRG, TXSTA (bit BRGH) et BAUDCON (bit BRG16). Voir tableau 18-5 p248.
    SPBRG = 25; //9600bps Voir tableau p187. Osc = 1MHz
    TXSTAbits.BRGH = 1; //Low speed. 0 = valeur par défaut
    BAUDCONbits.BRG16 = 1;
    
    //Les broches TX et RX (RC6 et RC7) doivent être en entrée. 
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
     
    //Permettre la transmission via le bit TXEN du registre TXSTA.  
    TXSTAbits.TXEN = 1;
     
    //Activer le port de communication asynchrone via le bit SPEN (=1) du registre RCSTA et le bit  SYNC (=0) du registre TXSTA.
    RCSTAbits.SPEN = 1; // 1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins) 
    TXSTAbits.SYNC = 0; //0 = Asynchronous mode 
    
    //Permettre la réception via le bit CREN du registre RCSTA.
    RCSTAbits.CREN = 1;

    //Au besoin, permettre les interruptions lors de la réception d?une donnée par le bit RCIE du registre PIE1.	
    PIE1bits.RC1IE = 1; //permet interruption en réception
    
    //Au besoin, permettre les interruptions des périphériques PEIE et les interruptions globales GIE.
    INTCONbits.PEIE = 1; //permet interruption des périphériques
    INTCONbits.GIE = 1;  //interruptions globales permises
}      
