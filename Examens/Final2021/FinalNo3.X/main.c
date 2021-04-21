 /**
 * @file   main.c, projet FinalNo3
 * @author Benoit Beaulieu
 * @date   avril 2021
 * @brief  No 3 de l'examen final du cours 247-416
  */

#include <xc.h>
#define _XTAL_FREQ 1000000 //Constante utilisée par la fonction de délais

void initialisation(void);

void main(void)
{
    
    unsigned long effet = 0x87654321;
    unsigned int resAN = 0; //résultat de la conversion AN
    int i = 0;
    initialisation();

 
    
    while(1) // Boucle principale du programme
    {
        
        ADCON0bits.GO_DONE = 1;  //lance une conversion
        while (ADCON0bits.GO_DONE == 1); //attend fin de la conversion
        resAN = (unsigned int) (ADRESH << 8 | ADRESL);
        
        switch (ADRESH)
        {
            case 0:
                T1CONbits.TMR1ON = 1;
                T3CONbits.TMR3ON = 0;
                break;
                    
            case 1:
                //PORTD = 1;
                T1CONbits.TMR1ON = 0;
                T3CONbits.TMR3ON = 1;
                 break;
                
            case 2:
                T1CONbits.TMR1ON = 0;
                T3CONbits.TMR3ON = 0;
                PORTD = (unsigned char) ((effet >> (i*4)) & 0xF);
                i = (i+1) % 8;
                __delay_ms(300);
 
                break;
                
            case 3:
                T1CONbits.TMR1ON = 0;
                T3CONbits.TMR3ON = 0;
                PORTD = ADRESL;
                break;
                  
        }
     }
}

/**
 * @brief Fonction qui sert à gérer l'initialisation des différents regesitres et variables.
 */
void initialisation(void)
{

    TRISD = 0; //Tout le port D en sortie

     //1-Config port
    TRISA = 0xFF;  //Désactive buffer 3 états de RA0. Donc broche en entrée
    ANSEL = 0xFF; //Entrée RA0/AN0 À RA3/AN3 en mode analogique
    
     
    
    //2- Config module ADC 
    ADCON2bits.ADCS = 6; //Fosc/64 (Fréquence pour la conversion la plus longue possible)
    ADCON1 = 0; //Vref+ = VDD et Vref- = VSS
    ADCON0bits.CHS = 0b0000; //Canal 0
    //ADCON0bits.CHS = 0b1001; //canal 9
    ADCON2bits.ADFM = 1; //Format du résultat: Alignement à droite
    ADCON2bits.ACQT = 7; //20 TAD (on laisse le max de temps au Chold du convertisseur AN pour se charger)
    ADCON0bits.ADON = 1; //Convertisseur AN à on
	
    /****** Timer 1 ********/
    // FOSC/4 = 1MHz/4 = 250 KHz
    // On veut intr aux 225ms -> f=44Hz
    // 250Khz / 56250 = 1/225ms    //65536-56250 = 9 286 -> 0x2446/
    T1CONbits.RD16 = 1; 
    T1CONbits.T1CKPS = 0; //psc = 0
    T1CONbits.TMR1CS = 0; //fosc/4
    TMR1 = 9286;
    //int de trm1
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    
    
     // configuration timer3
    
    T3CONbits.RD16 = 1; // read write en une opération
    T3CONbits.T3CKPS = 0b00; //prescaler = 0
    T3CONbits.TMR3CS = 0; //Fosc/4
    
    /**** Timer 3 *****/
    // calcul de la valeur à mettre dans les registres pour avoir un délai = 50 ms
    // FOSC/4 = 1MHz/4 = 250 KHz
    // 250KHz / 12500  = 1/50ms
    //65536-12500= 53036 = 0xCF2C
    TMR3 = 53036; 
    

    PIR2bits.TMR3IF = 0;
    PIE2bits.TMR3IE = 1;
    
    
    
    INTCONbits.PEIE = 1; //permet interruption des périphériques
    INTCONbits.GIE = 1;  //interruptions globales permises

  
    
}

