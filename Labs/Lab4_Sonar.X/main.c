 /**
 * @file   main.c, projet Lab1
 * @author Jacob Deschamps
 * @date   Janvier 2019
 * @brief  Programme du laboratoire 4 dans le cours 247-416-SH
 * @version 1.0
 */

#include <xc.h>
#include <stdio.h>
#include "Lcd4Lignes.h"
#include "interrupts.h"

#define NB_CHAR 20

void initialisation(void);

//Variables globales pour l'écho du sonar définie dans le fichier interrupts.c
extern unsigned int g_echo[NB_ECHO];
extern int g_compteEcho;

void main(void)
{
    int dist_mm; //Variable qui contiendra la valeur de la distance moyenne (en mm)
    int i; //Index pour la boucle for du calcul des distances moyennes
    char message[NB_CHAR]; //Tableau de 20 caractères pour l'affichage des distances perçues
    
    initialisation(); //Initialise les ports, les timers, Le module CCP1 et les interruptions du PIC18
    lcd_init(); //Initialise l'afficheur LCD
    
    PORTCbits.RC0 = 0; //Éteint la DEL jaune
    PORTDbits.RD7 = 0; //Éteint la DEL rouge
    PORTCbits.RC1 = 0; //Le signal TRIG envoyé vers le sonar est forcé à 0 au début du programme
    
    lcd_putMessage((const unsigned char*) "Lab4 Sonar 2019"); //Affiche ce message sur le LCD
    
    while(1) //Boucle principale du programme
    {
        if (g_compteEcho >= NB_ECHO)
        {
            dist_mm = 0; //À chaque fois que le tableau d'echo est rempli, on calcule la distance moyenne
            
            for (i = 0; i < NB_ECHO; i++)
            {
                //Tel que donnée dans la fiche technique du sonar HC-SR04 :
                //Distance = Temps de l'impulsion d'echo * Vitesse du son/2
                //Temps de l'impulsion d'echo = (1/(Fosc/4)) * Prescaler du timer 3 * g_echo
                //Vitesse du son = 340 m/s
                //Donc, la distance en m revient à : (1/(Fosc/4)) * Prescaler du timer 3 * g_echo * (340/2)
                //Distance en m = (1/(16000000/4))*8*g_echo*(340/2)
                //Distance en mm = 1000 * Distance en m
                //Distance en mm = 1000*(1/(16000000/4))*8*g_echo*(340/2) = 0.34 * g_echo
                //Distance en mm = g_echo/3 (on arrondit 0.34 à (1/3))
                dist_mm = dist_mm + (g_echo[i]/3);
            }

            sprintf(message, "Distance = %d", (dist_mm/NB_ECHO)); //La distance moyenne est insrée dans un tableau de caractères
            
            //Affichage de la distance moyenne calculée précédemment
            lcd_cacheCurseur();
            lcd_gotoXY(1, 2);
            lcd_effaceLigne(2);
            lcd_putMessage((const unsigned char*) message);
            lcd_gotoXY(17, 2);
            lcd_putMessage((const unsigned char*) "mm");
        }     
    }
}

/**
 * @brief Fonction qui sert à gérer l'initialisation des différents regesitres et variables.
 */
void initialisation(void)
{
    //Configuration des ports utilisés sur le PIC18
    ADCON1 = 0x07; //Désactive les fonctions analogiques du port A
    CMCON = 0x07; //Désactive les comparateurs pour utiliser le port D comme I/O digital
    TRISA = 0b11000000; //Tout le port A est en sortie sauf les bit RA6 et RA7
    TRISBbits.RB4 = 0; //Le bit RB4 du port B est en sortie
    TRISCbits.RC0 = 0; //Le bit RC0 du port C est mis en sortie
	TRISCbits.RC1 = 0; //Le bit RC1 du port C est mis en sortie pour l'envoi du signal TRIG vers le sonar
	TRISCbits.RC2 = 1; //Le bit RC2 du port C est mis en entrée pour recevoir l'echo du sonar
    TRISDbits.RD7 = 0; //Le bit RD7 du port D est en sortie
    
    //Configuration des registres du timer 0
    T0CONbits.TMR0ON = 0; //Le timer 0 est désactivé pour configurer ses registres
    T0CONbits.T08BIT = 0; //Le timer 0 est mis en mode 16 bits
    T0CONbits.T0CS = 0; //Le timer 0 est référencé à l'horloge interne du microcontrôleur
    T0CONbits.PSA = 0; //Un prescaler est utilisé pour timer 0
    T0CONbits.T0PS = 0b001; //Les bits T0PS2, T0PS1 et T0PS0 valent respectivement 001 pour utiliser un prescaler de 1:4
    //Il faut toujours écrire dans le registre TMR0H avant d'écrire dans le registre TMR0L
    TMR0H = 0b00010101; //Voir le site Internet https://www.exploreembedded.com/wiki/PIC18F4520_Timer pour le calcul des timers
    TMR0L = 0b10100000; //(TMR0H + TMR0L) = 65536 - ((Delay*Fosc)/(4*Prescaler)) -> (TMR0H + TMR0L) = 65536 - ((0.06*16000000)/(4*4)) = 5536
    T0CONbits.TMR0ON = 1; //Le timer 0 est démarré
    
    //Initialisation de l'interruption du timer 0
    INTCONbits.TMR0IF = 0; //Remise à zéro du flag d'interruption du timer 0
    INTCONbits.TMR0IE = 1; //Permet les interruption pour le timer 0
    INTCON2bits.TMR0IP = 1; //L'interruption du timer 0 est définie comme une interruption de haute priorité
    
    //Configuration des registres du timer 1
    T1CONbits.TMR1ON = 0; //Le timer 1 est désactivé pour configurer ses registres
    T1CONbits.RD16 = 1; //Le timer 1 est utilisé en une opération sur 16 bits
    T1CONbits.T1CKPS = 0b11; //Un prescaler 1:8 est utilisé (bits T1CKPS1 et T1CKPS0 tous deux mis à 1)
    T1CONbits.SOSCEN = 0; //L'oscillateur du timer 1 est désactivé
    T1CONbits.TMR1CS = 0; //Le timer 1 est référencé à l'horloge interne du microcontrôleur
    TMR1 = 0b0011110010110000; //(TMR1H + TMR1L) = 65536 - ((Delay*Fosc)/(4*Prescaler)) -> (TMR1H + TMR1L) = 65536 - ((0.1*16000000)/(4*8)) = 15536
    T1CONbits.TMR1ON = 1; //Le timer 1 est démarré
    
    //Initialisation de l'interruption du timer 1
    PIR1bits.TMR1IF = 0; //Remise à zéro du flag d'interruption du timer 1
    PIE1bits.TMR1IE = 1; //Permet les interruption pour le timer 1
    IPR1bits.TMR1IP = 1; //L'interruption du timer 1 est définie comme une interruption de haute priorité
    
    //Configuration des registres du timer 3
    T3CONbits.TMR3ON = 0; //Le timer 3 est désactivé pour configurer ses registres
    T3CONbits.RD16 = 1; //Le timer 3 est utilisé en une opération sur 16 bits
    T3CONbits.T3ECCP1 = 1; //Le timer 3 est utilisé comme horloge pour les modules CCP1 et ECCP1
    T3CONbits.T3CKPS = 0b11; //Un prescaler 1:8 est utilisé (bits T3CKPS1 et T3CKPS0 tous deux mis à 1)
    T3CONbits.TMR3CS = 0; //Le timer 3 est référencé à l'horloge interne du microcontrôleur
    
    //Puisque le timer 3 sera utilisé par le module CCP1, aucune interruption n'aura besoin d'être générée pour le timer 3.
    //On utilisera plutôt l'interruption du modile CCP1.
    
    //Configuration des registres du module CCP1
    CCPR1 = 0; //Toute valeur potentiellement contenue dans les registres CCPR1H et CCPR1L du module CCP1 est supprimée
    CCP1CONbits.CCP1M = 0b0101; //Le module CCP1 est utilisé en mode capture pour chaque front montant du signal d'echo à percevoir
    
    //Initialisation de l'interruption du module CCP1
    PIR1bits.CCP1IF = 0; //Remise à zéro du flag d'interruption du module CCP1
    PIE1bits.CCP1IE = 1; //Permet les interruption pour le module CCP1
    IPR1bits.CCP1IP = 1; //L'interruption du module CCP1 est définie comme une interruption de haute priorité
	
	//Initialisation générale des interruptions
	INTCONbits.PEIE = 1; //Les interruptions des périphériques sont permises
    INTCONbits.GIE = 1; //Interruptions globales permises
    RCONbits.IPEN = 1; //Les priorités d'interruptions sont activées
}