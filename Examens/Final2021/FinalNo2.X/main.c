 /**
 * @file   main.c, projet FinalNo2
 * @author Benoit Beaulieu
 * @date   avril 2021
 * @brief  No 2 de l'examen final du cours 247-416
  */

#include <xc.h>

#define SW1 PORTBbits.RB0

void initialisation(void);
void litAD(int noCanal, unsigned int* resultat);



void main(void)
{

    unsigned int resAN = 0; //résultat de la conversion AN
    int no = 0;
    unsigned int an = 0;
    
    initialisation();
    
    while(1) // Boucle principale du programme
    {
        if (SW1 == 0)
        { 
            no = (no + 1) % 8; //passe d'un canal à l'autre 0 à 3PORTD = litAD(0);
            while(SW1 == 0)
            {
               PORTD = (unsigned char) (1<< no); 
            }
           
        }
        litAD(no, &an);   
        PORTD = (unsigned char) (an>>2);
        CCPR2L = (unsigned char) (an>>2);
        CCP2CONbits.DC2B = an&0b11;

     }
}
void litAD(int noCanal, unsigned int* resultat)
{
        ADCON0bits.CHS = (unsigned char) (noCanal); //Canal 0        
        ADCON0bits.GO_DONE = 1;  //lance une conversion
        while (ADCON0bits.GO_DONE == 1); //attend fin de la conversion
        *resultat = ADRES;
}

/**
 * @brief Fonction qui sert à gérer l'initialisation des différents regesitres et variables.
 */
void initialisation(void)
{

    TRISD = 0; //Tout le port D en sortie

    //sw1
    ANSELH = 0;  // RB(0:4) en mode digital. Sur le 18F45K20 AN et PortB sont sur les memes broches
    TRISBbits.RB0 = 1;  //RB0 en entree


    //1-Config port
    TRISA = 0xFF;  //Désactive buffer 3 états de RA0. Donc broche en entrée
    TRISE = 0xFF;
    ANSEL = 0xFF; //Entrée RA0/AN0 À RA3/AN3 en mode analogique
    
    
    /***** pour AN9 sur RB3 *****/
    //TRISBbits.RB3 = 1; //Désactive buffer 3 états de RB3. Donc broche en entrée
    //ANSELHbits.ANS9 = 1; //Entrée Rb3/AN9 en mode analogique
            
    
    
    //2- Config module ADC 
    ADCON2bits.ADCS = 6; //Fosc/64 (Fréquence pour la conversion la plus longue possible)
    ADCON1 = 0; //Vref+ = VDD et Vref- = VSS
    ADCON0bits.CHS = 0b0000; //Canal 0
    //ADCON0bits.CHS = 0b1001; //canal 9
    ADCON2bits.ADFM = 1; //Format du résultat: Alignement à DROITE
    ADCON2bits.ACQT = 7; //20 TAD (on laisse le max de temps au Chold du convertisseur AN pour se charger)
    ADCON0bits.ADON = 1; //Convertisseur AN à on
	
  
    /******** PWM ***********/
    //voir section 11.4.7 (p152) fiches du 18F45K20
    //#1
    TRISCbits.RC1 = 1; //PWM CCP2 sur RC1

    //#3 Période PWM
    //Calculs: Période du PWM 1/400Hz = (PR2 + 1) x 4 x (1/1MHz) x Prescaler Tmr2 (voir p150 equ 11.1)
    // 1/400Hz = (155 + 1) x 4 / 1MHz x 4
    PR2 = 155;
    
    
    //#4
    CCP2CONbits.CCP2M = 0b1111; //mode PWM
    

    //#5 PWM Duty cycle
    CCPR2L = 0x80; //10% = x/4*(124+1) -> x = 50 -> 0b110010 
    CCP2CONbits.DC2B = 0b11;

    //#6 init du timer 2
    PIR1bits.TMR2IF = 0;
    T2CONbits.T2CKPS = 1; //Prescaler 1:4
    T2CONbits.TMR2ON = 1; //Timer2 ON
    
    //#7
    while (PIR1bits.TMR2IF ==0); //Attend 1 overflow du timer2
    TRISCbits.RC1 = 0; //PWM sur broche P1D/RD7


    
    
    
}

