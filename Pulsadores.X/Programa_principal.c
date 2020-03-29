/*
 * File:   Programa_principal.c
 * Author: FernandoFG
 *
 * Created on 14 de marzo de 2020, 10:10 PM
 */


#include <xc.h>
#include "Configuracion.h"
#include <pic18f4550.h>

// Variables Globales

long juego = 1;
long velocidad = 1;

// Funciones

void Luces_Uno(void);
void Luces_Dos(void);
void Luces_Tres(void);
void Luces_Cuatro(void);

/* Configuracion de los bits
 *  TRIS: Se registra el pin como Entrada/Salida
 *  PORT: Sirve para leer o para encender/apagar
 *  LAT: Modificacion entre leer o escribir (I/O)
 */

// PORTx para leer, y LATx para escribir

void SetupPort(){
    
    ADCON1bits.PCFG = 0xF; // Todos los puertos como digitales
    
    LATD = 0x00; // Se definen los puertos como escritura
    LATB = 0x00;
    LATA = 0x00;
    
    TRISBbits.RB0 = 1; // Puerto como entrada
    TRISBbits.RB1 = 1;
    
    TRISD = 0x00; // Todos los puertos como salidas
    TRISA = 0x00;
    
    INTCON2bits.RBPU = 0; // Resistencias PULL-UP para puerto B
    
    /* Cuando se utiliza la entrada como un PULL-UP su estado
    * "normal" es de uno logico y este se debe llevar a cero
    * logico por medio de un SWITCH el cual lo conduzca a tierra.
    * Esto se hace por medio de una resistencia interna del micro
    * la cual esta conectada a Vcc.
    */
    
}


void main(void) {
    SetupPort();
    while(1){
        
        if(PORTBbits.RB0 != 1){
            
            __delay_ms(20);
            juego = juego + 1; // No se puede juego += juego;
            //PORTAbits.RA0 = 1; // Valor de la salida
            LATAbits.LA0 = 1;
            //LATAbits.RA0 = 1; No se puede usar
            __delay_ms(500);
            //PORTAbits.RA0 = 0; Si se puede utilizar
            LATAbits.LA0 = 0;
            __delay_ms(500);
            
            if(juego == 5){
                juego = 1;
                PORTAbits.RA1 = 1;
                __delay_ms(2000);
                PORTAbits.RA1 = 0;
                __delay_ms(1000);
            }
  
        }
        
        switch(juego){
                case 1:
                    Luces_Uno();
                    break;
                case 2:
                    Luces_Dos();
                    break;
                case 3:
                    Luces_Tres();
                    break;
                case 4:
                    Luces_Cuatro();
                    break;
            }
        
    }
}


void Luces_Uno(void){
    LATD = 0xAA; // Valores de Salidas
    
    if(velocidad == 1){ __delay_ms(1000); LATD = 0x00; __delay_ms(1000);
    }else if(velocidad == 2){ __delay_ms(500); LATD = 0x00; __delay_ms(500);
    }else if(velocidad == 3){ __delay_ms(250); LATD = 0x00; __delay_ms(250);
    }else if(velocidad == 4){ __delay_ms(100); LATD = 0x00; __delay_ms(100); }
    
    if(PORTBbits.RB1 == 0){ // Lectura del puerto
        __delay_ms(20);
        velocidad = velocidad + 1;
        
        PORTAbits.RA2 = 1;
        __delay_ms(500);
        PORTAbits.RA2 = 0;
        __delay_ms(500);
        
        if(velocidad == 5){velocidad = 1;}
    }
    
}
void Luces_Dos(void){
    LATD = 0xFF;
    
    if(velocidad == 1){ __delay_ms(1000); LATD = 0x00; __delay_ms(1000);
    }else if(velocidad == 2){ __delay_ms(500); LATD = 0x00; __delay_ms(500);
    }else if(velocidad == 3){ __delay_ms(250); LATD = 0x00; __delay_ms(250);
    }else if(velocidad == 4){ __delay_ms(100); LATD = 0x00; __delay_ms(100); }
    
    if(PORTBbits.RB1 == 0){
        __delay_ms(20);
        velocidad = velocidad + 1;
        
        PORTAbits.RA2 = 1;
        __delay_ms(500);
        PORTAbits.RA2 = 0;
        __delay_ms(500);
        
        if(velocidad == 5){velocidad = 1;}
    }
    
}
void Luces_Tres(void){
    LATD = 0x66;
    
    if(velocidad == 1){ __delay_ms(1000); LATD = 0x00; __delay_ms(1000);
    }else if(velocidad == 2){ __delay_ms(500); LATD = 0x00; __delay_ms(500);
    }else if(velocidad == 3){ __delay_ms(250); LATD = 0x00; __delay_ms(250);
    }else if(velocidad == 4){ __delay_ms(100); LATD = 0x00; __delay_ms(100); }
    
    if(PORTBbits.RB1 == 0){
        __delay_ms(20);
        velocidad = velocidad + 1;
        
        PORTAbits.RA2 = 1;
        __delay_ms(500);
        PORTAbits.RA2 = 0;
        __delay_ms(500);
        
        if(velocidad == 5){velocidad = 1;}
    }
}

void Luces_Cuatro(void){
    LATD = 0x99;
    
    if(velocidad == 1){ __delay_ms(1000); LATD = 0x00; __delay_ms(1000);
    }else if(velocidad == 2){ __delay_ms(500); LATD = 0x00; __delay_ms(500);
    }else if(velocidad == 3){ __delay_ms(250); LATD = 0x00; __delay_ms(250);
    }else if(velocidad == 4){ __delay_ms(100); LATD = 0x00; __delay_ms(100); }
    
    if(PORTBbits.RB1 == 0){
        __delay_ms(20);
        velocidad = velocidad + 1;
        
        PORTAbits.RA2 = 1;
        __delay_ms(500);
        PORTAbits.RA2 = 0;
        __delay_ms(500);
        
        if(velocidad == 5){velocidad = 1;}
    }
}