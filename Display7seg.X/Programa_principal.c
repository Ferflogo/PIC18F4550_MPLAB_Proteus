/*
 * File:   Programa_principal.c
 * Author: FernandoFG
 *
 * Created on 16 de marzo de 2020, 05:14 PM
 */


#include <xc.h>
#include "Configuracion.h"

int display[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
// Display de 7 segmentos de Catodo Comun

void Setup_Ports(){
    ADCON1bits.PCFG = 0xF; // Todos los pines como digitales
    LATA = 0;
    LATD = 0;
    TRISA = 0; // Puertos como salidas
    TRISD = 0; // Puertos como salidas
    TRISBbits.RB0 = 1; // Pines de entrada
    TRISBbits.RB1 = 1;
    TRISBbits.RB4 = 1;
    INTCON2bits.RBPU = 0; // Pines B como PULL-UP
}

void main(void) {
    Setup_Ports();
    while(1){
        if(PORTBbits.RB4 == 0){
            LATAbits.LA0 = 1;
            LATAbits.LA1 = 0;
            for(int i = 0; i < 10; i++){
                PORTD = display[i];
                __delay_ms(500);
            }
            PORTD = 0x0;
            LATAbits.LA0 = 0;
            LATAbits.LA1 = 0;
        }else if(PORTBbits.RB0 == 0){
            LATAbits.LA0 = 0;
            LATAbits.LA1 = 1;
            for(int i = 9; i > 0; i--){
                PORTD = display[i];
                __delay_ms(500);
            }
            PORTD = 0x0;
            LATAbits.LA0 = 0;
            LATAbits.LA1 = 0;
        }else if(PORTBbits.RB1 == 0){
            LATAbits.LA0 = 1;
            LATAbits.LA1 = 1;
            PORTD = display[4];
            __delay_ms(500);
            PORTD = 0x0;
            LATAbits.LA0 = 0;
            LATAbits.LA1 = 0;
        }
    }
}
