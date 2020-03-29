/*
 * File:   Hola_Mundo.c
 * Author: FernandoFG
 *
 * Created on 14 de marzo de 2020, 10:23 AM
 */


#include <xc.h> // Biblioteca del compilador
#include "Configuracion.h" // Se incluye la biblioteca donde esta la configuracion hecha
#define true 1 // Se define esta constante para utilizar true como 1
#include "pic18f4550.h" // Ctrl + Click se entra a la biblioteca

/* Configuracion del Oscilador
 * Se define la frecuencia a la cual se trabaja en Configuracion.h
 */

/* El PPL Frecuency Multiplier
 * Nos permite multiplicar la frecuencia para obtener otras
 * frecuencias. Esto es configurado en Configuracion.c
 */

/* Configuracion de los bits
 *  TRIS: Se registra el pin con Entrada/Salida
 *  PORT: Sirve para leer o para encender/apagar
 *  LAT: Modificacion entre leer o escribir (I/O)
 */

/*      ENTRADAS Y SALIDAS DIGITALES CON EL PIC18F4550
 * Los pines de entradas y salidas presentan las siguientes características en sus puertos IO
 *      * 3 Registro independientes para Configurar, Escribir y Leer cada PUERTO (TRISx, LATx y PORTx).
 *      * Selección de resistencia PULL-UP solo para el Puerto B.
 * A continuación se explicará cómo configurar, escribir o leer un Pin de cada PUERTO;
 *      * TRISX: Escribiendo en cada bit (?1? lógico = Entrada y ?0? lógico = Salida).
 *      * LATX: Escribiendo en cada bit la salida tendrá un nivel de Voltaje (?1? lógico = 5v | ?0? lógico = 0v).
 *      * PORTX: Este registro es de solo Lectura (5v =?1? lógico | 0v =?0? lógico).
 * 
 *  1. Configuración de los pines IO de un PUERTO
 * TRISA = 0b11111111; Configura todos los pines del Puerto A como Entrada.
 * TRISA = 0b00000000; Configura todos los pines del Puerto A como Salida.
 * TRISA = 0b00001111; Los pines Altos como Salida y el resto como Entrada.
 * 
 *  2. Escritura de pines en un PUERTO
 * LATA = 0b11111111; Todos los pines del Puerto A con una salida de 5v.
 * LATA = 0b00000000; Todos los pines del Puerto A con una salida de 0v.
 * LATA = 0b00001111; Los pines Altos a 0v y los pines Bajos a 5v.
 * 
 *  3. Lectura de un PUERTO
 * Valor = PORTA [ RA0 ] : El estado lógico del pin A0 se escribe en la variable valor
 * Valor = PORTA : El estado lógico del todo el Puerto A se escribe en valor.
 * PORTxbits.Rx# == boolean: Pregunta por el estado logico del puerto
 *      Tambien se puede preguntar como PORTxbits.Rx# o !PORTxbits.Rx#
 * 
 * Para poder Habilitar la resistencia PULL-UP en un pin determinado, es necesario que
 * dicho pin este configurado como entrada y luego escribir ?0? lógico en el bit RBPU 
 * del registro INTCON2.
 */

void InitPort(){ // Funcion que configura los puertos
    ADCON1bits.PCFG = 0xF; // Todos los puertos como digitales (1111)
    LATD = 0; // Se ponen los puertos como escritura
    LATA = 0;
    LATB = 0;
    LATC = 0;
    LATE = 0;
    // TRISD = 0; Todo los puertos D son Salida
    TRISDbits.RD1 = 0; // PORTRD1 es Salida 0, Entrada 1
    TRISAbits.RA1 = 0;
    TRISBbits.RB1 = 0;
    TRISCbits.RC1 = 0;
    TRISEbits.RE1 = 0;
    
}

void main(void) {
    InitPort(); // Se inicializan los puertos
    while(true){
        PORTDbits.RD1 = 1; // Estritura de este puerto
        PORTAbits.RA1 = 1; // Deberia escribirse por medio de un LAT
        PORTBbits.RB1 = 1;
        PORTCbits.RC1 = 1;
        PORTEbits.RE1 = 1;
        __delay_ms(100);
        PORTDbits.RD1 = 0;
        PORTAbits.RA1 = 0;
        PORTBbits.RB1 = 0;
        PORTCbits.RC1 = 0;
        PORTEbits.RE1 = 0;
        __delay_ms(100);
    }
}
