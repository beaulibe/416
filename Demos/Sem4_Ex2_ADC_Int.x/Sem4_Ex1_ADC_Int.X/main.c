 /**
 * @file   main.c, projet Sem4_Ex1
 * @author Benoit Beaulieu
 * @date   10 fév. 2020
 * @brief  Programme démo de la semaine 4 du cours 247-416. ADC par Intr
 */

#include <xc.h>
#include "interrupts.h"



void initialisation(void);

extern struct moteur stMotMoulin;
extern unsigned int g_lectureAN;

void main(void)
{

    stMotMoulin.vitesse = 100;
    stMotMoulin.temperature = 33;
    stMotMoulin.courant = 12;

    initialisation();

    ADCON0bits.GO_DONE = 1;  //on lance une 1ere conversion
    while(1) // Boucle principale du programme
    {
        
        //ADCON0bits.GODONE = 1; //Lance une conversion
        //while(ADCON0bits.GODONE);//Attend fin de conversion
        stMotMoulin.courant = g_lectureAN>>2;      
        PORTD = stMotMoulin.courant; //affiche poids fort

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
   
    /*
    //Configuration de l'interruption INT0
    INTCONbits.GIE = 1;
    INTCONbits.INT0IE =1;//  
    INTCON2bits.INTEDG0 = 0;
    
    //Configuration de l'interruption INT2
    INTCON3bits.INT2IE =1;//  
    INTCON2bits.INTEDG2 = 0;
    */
    
    //Configuration ADC
     
    ADCON0bits.ADON = 0;   //Convertisseur AN désactivé (pour configurer ses registres)
    ANSELbits.ANS0 = 1; //A0 sélectionné comme canal et mis en mode analogique
    ADCON0bits.CHS = 0b0000; //Canal 0
    ADCON1 = 0; //Vref+ = VDD et Vref- = VSS
    ADCON2bits.ADFM = 1; //Alignement à gauche des 10 bits de la conversion (8 MSB dans ADRESH et 2 LSB à gauche dans ADRESL)
    ADCON2bits.ACQT = 0b111; //20 TAD (on laisse le maximum de temps à la capacité du convertisseur AN pour se charger)
    ADCON2bits.ADCS = 0b110; //Fosc/64 (Fréquence pour la conversion la plus longue possible)
    ADCON0bits.ADON = 1; //Convertisseur AN activé (mais la toute première conversion n'a pas encore été démarrée)    
    
    //Interruption ADC
    INTCONbits.PEIE = 1; //Permet les interruptions des périphériques
    INTCONbits.GIE = 1; //Permet les interruptions globales
    PIE1bits.ADIE = 1; //Permettre interruption du AN
    
    
}

