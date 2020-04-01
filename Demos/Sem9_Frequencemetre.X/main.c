/**
 * @file   main.c
 * @author Benoit Beaulieu
 * @date   Mars 2020
 * @brief  Exercice 2 - Fréquencemètre
 * Une façon assez simple de réaliser un fréquencemètre est de compter le nombre de 
 * fronts montants (ou descendants) d'un signal pendant un certain temps. Par exemple,
 *  si on compte huit fronts montants pendant une seconde, nous avons une fréquence de 8 Hz.
 * Sachant cela, réalisez un fréquencemètre en vous servant du timer 1 pour avoir 
 * une période d'une seconde. Utilisez ensuite l'interruption INT1 pour compter les 
 * fronts montants pendant ce temps. Prenez le signal de sortie de la DEL7 de l'exercice 
 * précédant comme fréquence d'entrée. Pour ce faire, utilisez un fil pour relier 
 * la broche de la DEL7 (broche RD7) à la broche d'entrée de l'interruption INT1 (broche RB1).
 */

#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

extern int g_freq;
extern int g_delTmr0; 

/*********** prototypes *****************/
void initialisation(void);


void main(void)
{
    initialisation();

    
    ADCON0bits.GO_DONE = 1;  //On lance une première conversion de l'ADC
 
    while(1) //Boucle principale du programme
    { 
        PORTD = (g_delTmr0 << 7) | g_freq;  //La DEL7 clignote selon la fréquence du timer 0 modulée par l'ADC
        
    }
    
}

/**
 * @brief Fonction qui sert à gérer l'initialisation des différents registres et variables.
 */
void initialisation(void)
{
    
    TRISD = 0; //port D en sortie
    ANSELH = 0; //Les fonctions analogiques sont désactivées pour le port B
    TRISBbits.RB1 = 1; //La broche RB1 du port B est mise en entrée pour recevoir l'interruption INT1
    

    
   //Configuration du port analogique
    TRISAbits.TRISA0 = 1; //A0 en entrée
    ANSELbits.ANS0 = 0;  //A0 en mode analogique
    ADCON0bits.ADON = 1; //Convertisseur AN à on
    ADCON1bits.VCFG1 = 0; //Tension de référence V- reliée à VSS
    ADCON1bits.VCFG0 = 0; //Tension de référence V+ reliée à VDD
    ADCON2bits.ADFM = 0; //Alignement à gauche des 10bits de la conversion (8 MSB dasn ADRESH, 2 LSB à gauche dans ADRESL)
    ADCON2bits.ACQT = 7; //20 TAD (on laisse le max de temps au Chold du convertisseur AN pour se charger)
    ADCON2bits.ADCS = 6; //Fosc/64 (Fréquence pour la conversion la plus longue possible)
    //Config AN par interruption
    PIR1bits.ADIF = false; //on reset le flag
    PIE1bits.ADIE = 1; //permet interruptions de l'AD
    ADCON0bits.GO_DONE = 1;  //lance une conversion    
    
    
    
   // configuration timer0
    T0CONbits.TMR0ON    = 1;
    T0CONbits.T08BIT    = 0; // mode 16 bits
    T0CONbits.T0CS      = 0;
    T0CONbits.PSA       = 0; // prescaler enabled
    T0CONbits.T0PS      = 0b011; // 1:16 pre-scaler

    

    // calcul de la valeur à mettre dans les registres pour avoir un délai = 1 seconde
    // FOSC/4 = 1MHz/4 = 250 KHz
    // avec 16 bits on peut avoir une attente maximale = 65535 coups d'horloge
    // avec 8 bits on peut avoir une attente maximale = 255 coups d'horloge
    // dans le cas ici, on active le prescaler à 1:16 => 250 KHz / 16 = 15625 (il est possible de fonctionner en mode 16 bits)
    // 15625 décimal = 0x3D09
    // l'interruption du Timer0 se produit au passage de 0xFFFF à 0x0000, il faut donc soustraire le nombre de coups d'horloge voulu du total
    // 0xFFFF - 0x3D09 = 0xC2F6 !
    
    //Attention, il faut écrire dans le TMR0H avant le TMR0L, car le TMR0H est un buffer
    // avant le vrai registre. Voir section 12.2
    //Lorsqu'on écrit dans TMR0L le valeur de TMR0H est mise dans le vrai registre en même temps.
    TMR0H = 0xC2; 
    TMR0L = 0xF6;
    

    INTCONbits.TMR0IE   = 1;  // timer 0 interrupt enable
    INTCONbits.TMR0IF   = 0; // timer 0 interrupt flag
    
    //Configuration des registres du timer 1
    T1CONbits.TMR1ON = 0; //Le timer 1 est désactivé pour configurer ses registres
    T1CONbits.RD16 = 1; //Le timer 1 est mis en mode 16 bits
    T1CONbits.T1CKPS = 3; //Un prescaler de 8 est utilisé pour le timer 1
    T1CONbits.TMR1CS = 0; ///Le timer 1 est référencé à l'horloge interne du microcontrôleur (Fosc/4)
    TMR1 = 0x85EE; //TMR1 = 65536 - ((Delay*Fosc)/(4*Prescaler)) -> TMR1 = 65536 - ((1*1000000)/(4*8)) = 34286
    T1CONbits.TMR1ON = 1; //Le timer 1 est démarré
    
    //Configuration des resgistres de l'interruption du timer 1
    PIR1bits.TMR1IF = 0; //Le flag d'interruption du timer 1 est remis à 0
    PIE1bits.TMR1IE = 1; //Les interruptions du timer 1 sont permises

    
    
    
    
     //Configuration de l'interruption INT1
    INTCON3bits.INT1IF = 0; //Le flag d'interruption d'INT1 est remis à 0
    INTCON3bits.INT1E  = 1; //Les interruptions d'INT1 sont permises
    INTCON2bits.INTEDG1 = 1; //L'interruption INT1 surviendra sur un front montant
    
    //Interruptions générales
    INTCONbits.PEIE = 1; //permet interruption des périphériques
    INTCONbits.GIE = 1;  //interruptions globales permises
}