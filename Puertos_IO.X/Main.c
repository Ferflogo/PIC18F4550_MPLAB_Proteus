/*
 * File:   Main.c
 * Author: FernandoFG
 *
 * Created on 18 de marzo de 2020, 05:30 PM
 */

#define _XTAL_FREQ  8000000 // Frecuencia a la cual se va a trabajar
#include    <xc.h>
#include    "fuses.h" // Header donde se encuentran las configuraciones de Oscilador, enables, etc.

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

//      Funciones

void secuencial_Efecto1(void); // Genera un shift en los puertos A, corrimiento del 1
void secuencial_Efecto2(void); // Genera un shift desde el centro hacia los lados contrarios
void secuencial_Efecto3(void);
void secuencial_Efecto4(void);

//      Variables Globales

unsigned char efecto = 1; // Unsigned: Sin signo
unsigned long velocidad = 1;

int main(void) {
    TRISD = 0; // Se definen el puerto D como Salidas
    LATD = 0; // Se inician/escriben el valor en bajo
    
    TRISBbits.TRISB7 = 1; // Inicia los valores de pulsador como alto
    TRISBbits.TRISB6 = 1; // es en alto, ya que esta en Pull-Up
    INTCON2bits.RBPU = 0; // Pull-Up del puerto B
    while (1) {
        //efecto
        if (!PORTBbits.RB7) { // Pregunta por el pin RB7 (Lectura)
            __delay_ms(50);
            if(++efecto==5){efecto=1;} // Reinicia el contador de efecto
                // ++efecto Suma un 1 a efecto cada vez que entra en el if
                // Tambien pregunta por el valor de efecto.
        }
        switch (efecto) { // Dependiendo del valor de efecto aplica distintas funciones
            case 1: secuencial_Efecto1();
                break;
            case 2: secuencial_Efecto2();
                break;
            case 3: secuencial_Efecto3();
                break;
            case 4: secuencial_Efecto4();
                break;
        }
    }
    return 1;
}

void secuencial_Efecto1(void) {
    for (int i = 0; i < 8; i++) {
        LATD = 1 << i; // SHIFT de un 1 en un byte
        if(velocidad==1){__delay_ms(50);} // Cambia las velocidades que realiza el Shift
        else if(velocidad==2){__delay_ms(100);}
        else if(velocidad==3){__delay_ms(200);}
        else if(velocidad==4){__delay_ms(400);}
        //velocidad
        if (!PORTBbits.RB6) { // Si el puerto RB6 es diferente de true
            __delay_ms(50);
            if(++velocidad==5){velocidad=1;} // Reinicia Contador de Velocidad
        }
    }
}

void secuencial_Efecto2(void) {
    for (int i = 0, j = 7; i < 8; i++, j--) {
        LATD = (1 << i) + (1 << j); // Genera un shift desde el centro hacia los lados contrarios
        if(velocidad==1){__delay_ms(50);}
        else if(velocidad==2){__delay_ms(100);}
        else if(velocidad==3){__delay_ms(200);}
        else if(velocidad==4){__delay_ms(400);}
        //velocidad
        if (!PORTBbits.RB6) {
            __delay_ms(50);
            if(++velocidad==5){velocidad=1;}
        }
    }
}

void secuencial_Efecto3(void) {
    for (int i = 0; i < 9; i++) {
        LATD = (1 << i) - 1;
        if(velocidad==1){__delay_ms(50);}
        else if(velocidad==2){__delay_ms(100);}
        else if(velocidad==3){__delay_ms(200);}
        else if(velocidad==4){__delay_ms(400);}
        //velocidad
        if (!PORTBbits.RB6) {
            __delay_ms(50);
            if(++velocidad==5){velocidad=1;}
        }
    }
}

void secuencial_Efecto4(void) {
    volatile unsigned int m=0,n=0;
    for (int i = 0; i < 5; i++) {
        LATD = m+n;
        m += (1<<i);
        n += (1<<(7-i));
        if(velocidad==1){__delay_ms(50);}
        else if(velocidad==2){__delay_ms(100);}
        else if(velocidad==3){__delay_ms(200);}
        else if(velocidad==4){__delay_ms(400);}
        //velocidad
        if (!PORTBbits.RB6) {
            __delay_ms(50);
            if(++velocidad==5){velocidad=1;}
        }
    }
}
