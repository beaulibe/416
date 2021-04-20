 /**
 * @file   main.c, projet Final 2021
 * @author Benoit Beaulieu
 * @date   avril 2021
 * @brief  
 */

#include "xc.h"
#include "stdbool.h"

#define _XTAL_FREQ 1000000
void initialisation(void);

//unsigned char g_caracRx = 'a';


void main(void)
{
    char msg[] = "No 1";
    int i = 0;
    
    initialisation();
    
    while (msg[i] != '\0')
    {
        while(PIR1bits.TXIF==0); //on attend que le registe de transmission soit prêt 
        TXREG = msg[i++];
    }

    PORTD = 'A';
    
    while(1) // Boucle principale du programme
    {
/* //par pooling
        if (PORTBbits.RB0 == 0)
        {
            while (PORTBbits.RB0 == 0);
            while(PIR1bits.TXIF==0); //on attend que le registe de transmission soit prêt 
            PORTD = g_caracRx;
            TXREG = g_caracRx++;
 
        }
        
  */  
    }
}


/**
 * @brief Fonction qui sert à gérer l'initialisation des différents regesitres et variables.
 */
void initialisation(void)
{

    TRISD = 0; //Tout le port D en sortie

    ANSELH = 0;  // RB(0:4) en mode digital. Sur le 18F45K20 AN et PortB sont sur les memes broches
    TRISBbits.RB0 = 1;  //RB0 en entree
    PORTBbits.RB0 = 1;  //met à 1 pour ne pas générer d'interruption au départ.
    INTCONbits.INT0IF = 0; //Reset flag d'interruption d'INT0 (pour s'assurer de ne pas avoir d'interruption au départ)    
    INTCONbits.INT0IE = 1; //Permettre les interruptions d'INT0
    INTCON2bits.INTEDG0 = 0; //Choisir le front de l'interruption INT0
    
    
    //Configuration du port analogique
/*    TRISAbits.TRISA0 = 1; //A0 en entrée
    ANSELbits.ANS0 = 1;  //A0 en mode analogique
    
    ADCON0bits.ADON = 1; //Convertisseur AN à on
    ADCON1bits.VCFG1 = 0; //Tension de référence V- reliée à VSS
    ADCON1bits.VCFG0 = 0; //Tension de référence V+ reliée à VDD
    ADCON2bits.ADFM = 0; //Alignement à gauche des 10bits de la conversion (8 MSB dans ADRESH, 2 LSB dans ADRESL)
    ADCON2bits.ACQT = 7; //20 TAD (on laisse le max de temps au Chold du convertisseur AN pour se charger)
    ADCON2bits.ADCS = 6; //Fosc/64 (Fréquence pour la conversion la plus longue possible)
   */ //Config AN par interruption
 //   PIR1bits.ADIF = false; //on reset le flag
 //   PIE1bits.ADIE = 1; //permet interruptions de l'AD
    
    
 
    
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
    PIE1bits.RC1IE = 1; //permet interruption en réception
    
    
    INTCONbits.PEIE = 1; //permet interruption des périphériques
    INTCONbits.GIE = 1;  //interruptions globales permises
    
    
    
    
}

