/*
 * Fichier:   main.c
 * Auteur: Benoit
 * Crée le 18 février 2020, 15:59
 * Brief: Lab6 du cours 416.
 * Matériel: PIC18F458, osciallateur de 40MHz, Anneau de DEL neoPixel WS2812 (https://www.digikey.ca/product-detail/en/adafruit-industries-llc/1643/1528-1102-ND/5154677)
 * 
 */


#include <xc.h>
#include "NeoPxl.h"
#include "EffetsNeoPx.h"
#include <stdbool.h>

/****** Constantes ************/
#define _XTAL_FREQ 40000000 //Constante utilisée par delaisMS(x). Doit = fréq de l'oscillateur 

/****** Prototypes ********/
void initialisation(void);
unsigned char rxComm(void);
    

void main(void) 
{
    unsigned char carRx = 2;
    
    initialisation();
    
    NeoInit();   
    NeoDraw ();    
    while(true)
        
    {       
      NeoDraw ();
      NeoRotate ();
      //__delay_ms(50);
      carRx = rxComm(); //on attend un caractère du port série
    }

    return;
}

void initialisation(void)
{
    TRISD = 0; //NeoPin sur RD0. On met tout le port en sortie.
    
    /********** Communication série ************/
    //1. Initialize the SPBRG register for the appropriate
    //baud rate. If a high-speed baud rate is desired,
    SPBRG = 64; //9600bps Voir tableau p187. Osc = 40MHz    
    
    //set bit BRGH (Section 18.1 ?USART Baud
    //Rate Generator (BRG)?).
    TXSTAbits.BRGH = 0; //Low speed. 0 = valeur par défaut
    
    //2. Enable the asynchronous serial port by clearing
    //bit SYNC and setting bit SPEN.
    RCSTAbits.SPEN = 1; // 1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins) 
    TXSTAbits.SYNC = 0; //0 = Asynchronous mode 
    
}

unsigned char rxComm(void)
{
    unsigned char carRecu = 0;
    

//3. If interrupts are desired, set enable bit RCIE.
//4. If 9-bit reception is desired, set bit RX9.
//5. Enable the reception by setting bit CREN.
    RCSTAbits.CREN = 1; //1 = Enables continuous receive
    
//6. Flag bit RCIF will be set when reception is
//complete and an interrupt will be generated if
//enable bit RCIE was set.
    while(PIR1bits.RC1IF == 0); //On bloque ici en attendant la rx d'un caractère
    
   
    
//7. Read the RCSTA register to get the ninth bit (if
//enabled) and determine if any error occurred
//during reception.
//8. Read the 8-bit received data by reading the
//RCREG register.
    carRecu = RCREG; 
    
    
//9. If any error occurred, clear the error by clearing
//enable bit CREN.
//    
    RCSTAbits.CREN = 0;
    
    return carRecu;
}