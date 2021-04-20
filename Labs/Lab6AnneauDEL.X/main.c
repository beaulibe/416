/*
 * Fichier:   main.c
 * Auteur: Benoit
 * Crée le 18 février 2020, modif le 16 avril 2021
 * Brief: Lab6 du cours 416.
 * Matériel: PIC18F458, osciallateur de 40MHz (important pour les timings critiques des DEL NeoPixel, 
 * Anneau de DEL neoPixel WS2812 
 * (https://www.digikey.ca/product-detail/en/adafruit-industries-llc/1643/1528-1102-ND/5154677)
 * Convertisseur USB-Série.
 * Fonctionne avec le simulateur (SimTrameLabServomoteur) écrit en C# par Benoit
 * 
 */


#include <xc.h>
#include "NeoPxl.h"
#include "EffetsNeoPx.h"
#include <stdbool.h>
#include <stdint.h>


/****** Constantes ************/
#define _XTAL_FREQ 40000000 //Constante utilisée par delaisMS(x). Doit = fréq de l'oscillateur 
#define MAX_TRAME 6
#define SOH 1

enum enumTrame {EFFET=1,R,G,B};

/****** Prototypes ********/
void initialisation(void);
//unsigned char rxComm(void);  //pour tests
bool rxTrame(unsigned char* buffer);
void traiteTrame(unsigned char* buffer);

    

void main(void) 
{
    
    unsigned char trame[MAX_TRAME];
    
    
    initialisation();
    
    NeoSet6Couleur();   //rempli les tableaux g_NeoGreen[], g_NeoBlue[] et g_NeoRed[] avec 2 DEL de chaque couleur. Il y aura donc 6 couleurs au total]
    NeoDraw (); //envoie les valeurs de tableaux aux DEL pour afficher   
    while(true)
        
    {       
      //__delay_ms(50);
      //carRx = rxComm(); //on attend un caractère du port série
      if (rxTrame(trame))
      {
          traiteTrame(trame);
          NeoDraw ();

      }
    }

    return;
}


/**
 * @brief Vérifie s'il y a un caractère de reçu par le port série. Si oui
 * on l'ajoute à la trame. La variable indexTrame nous indique où mettre le 
 * caracère reçu dans le buffer de réception.
 * @param Le pointeur du buffer de réception des caractères
 * @return Vrai si tous les caractères de la trame ont été reçu (indexTrame = MAX_TRAME) et 
 * si le checksum est bon.
 * Faux Si tous les caractères n'ont pas encore été reçu.
 * 
 */
bool rxTrame(unsigned char* buffer)
{
    bool retour = false;
    unsigned char c; 
    static int indexTrame = 0;
    unsigned int chkSum = 0;
   // RCSTAbits.CREN = 1; //1 = Enables continuous receive
    if (PIR1bits.RC1IF == 1) //un caractère de reçu
    {
        c = RCREG;
        
        if (c == SOH && indexTrame == 0) //on a recu le 1er caractere de la trame
        {
            buffer[0]=c;
            indexTrame++;
        }
        else
        {
            if (indexTrame > 0 && indexTrame < MAX_TRAME) //on poursuit la réception de la trame
            {
                buffer[indexTrame]=c;
                indexTrame++;
            }
        }
        
        if (indexTrame >= MAX_TRAME)
        {
            for (int i = 1; i < MAX_TRAME-1; i++) //on calcule le chksum
            {
                chkSum = chkSum + (unsigned int)buffer[i];   
            }
            chkSum = chkSum & 0x00FF; //on garde que les 8 lsb
            if (chkSum == buffer[MAX_TRAME-1]) //chksum est bon?
                retour = true;
            indexTrame=0; //erreur on recommence
        }
        
        //RCSTAbits.CREN = 0;
    }
    
    return retour;
    
}

/**
 * @brief Selon l'octet "Effet" (buffer[EFFET]) dans la trame, appelle la méthode correspondant à l'effet désiré.
 * @param Le pointeur de la trame reçue.
 * @return rien
 * 
 */
void traiteTrame(unsigned char* buffer)
{
    uint8_t NeoR, NeoG, NeoB;
    
      
    switch (buffer[EFFET])
    {
        case 'P': 
            NeoR = (uint8_t)buffer[R]*255/100;
            NeoG = (uint8_t)buffer[G]*255/100;
            NeoB = (uint8_t)buffer[B]*255/100;

            NeoSetColor(NeoR, NeoG,NeoB);
        break;
        
        case 'A':
            NeoSet6Couleur();
        break;
            
        case 'B':
            NeoRotate();
        break;

        case 'C':
            NeoWave();
        break;

        
    }
    
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
    RCSTAbits.CREN = 1; //1 = Enables continuous receive
    
    
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