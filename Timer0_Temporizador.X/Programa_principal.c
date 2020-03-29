/*
 * File:   Programa_principal.c
 * Author: FernandoFG
 *
 * Created on 23 de marzo de 2020, 05:51 PM
 */


#include <xc.h>
#include "Configuracion.h"
#include "LCD_libreria.h" // Lbreria que trae MPLAB Modificada por Wels Theory
#define true 1

/* Temporizador con Timer 0
 * Bits del Timer0: T0CON Control Register
 *      TMR0ON: Se habilita el timer0
 *      T0BIT: Control de 8 bits (Cuentas de 0-255) o 16 bits (Cuentas de 0 a 65535)
 *      T0CS: Fuente del contador ya sea externa o interna(Para este caso sera interna)
 *      T0SE: Seleccion de flanco, ya sea de Subida o Bajada
 *      PSA: Se asigna una preescala
 *      T0PS2: T0PS0: Valor de la preescala(En este caso se quiere contar hasta 3s y la preescala es de 1:256)
 * 
 * Bits de las Interrupciones: INTCON Control Register
 *      GIE/GIEH: Habilita la interrupciones (Interrupcion Global)
 *      PEIE/GIEL: Habilita interrupciones de Perifericos
 *      TMR0IE: Habilita la interrupcion por Overflow(Desbordamiento) de cuenta
 *      INT0IF: Bandera de interrupcion Externa
 * 
 *      Nota: Las interrupciones Perifericas no significa que sean de dispositivos Externos
 * 
 *      El temporizador = (4/FOSC)*Pre-escaler*(x+1)
 *      Para 3s seria -> 3s = (4/20MHs)*256*(x+1)
 *          x = 58592 -> 65535 - x = 6943
 * 
 *      Cuando se escoge cuenta de con 16 bits este tiene dos registros el de Altos y el de Bajos
 *      de esta forma se logra hacer una cuenta de 16 bits.
 */

void LCD_Init(void){ // Se utiliza para poder usar una LCD y mostrar los datos, ya esta definido el
                     // puerto D como salidas para la conexion con la LCD de 5X7 de 16
    OpenXLCD(FOUR_BIT & LINES_5X7);
    while( BusyXLCD() ); // LCD esta ocupado
    WriteCmdXLCD(0x06); // Mover el cursor a la derecha
    WriteCmdXLCD(0x0C); // Desactivar cursor
}

void InitPort(void){ // Se definen los puertos de entrada y salidad, sin contar los de la LCD
    ADCON1bits.PCFG = 0xF; // Todas Digitales
    TRISB = 1;
    TRISA = 0;
    LATB = 1;
    LATA = 1;
}

void Timer0_Init(void){
    INTCONbits.GIE = 0;
    T0CONbits.T0CS = 0;     // Temporizador
    T0CONbits.PSA = 0;      // Habilita Preescala
    T0CONbits.T0PS = 0b111; // Preescala de 1:256
    T0CONbits.T08BIT = 0;   // 16 ibts de cuenta
    T0CONbits.TMR0ON = 1;   // Tmr0 Empieza
    INTCONbits.TMR0IF = 0;  // Flag del Tmr0 en Bajo
    INTCONbits.TMR0IE = 1;  // Habilita el Overflow
    INTCONbits.PEIE = 1;    // Habilita interrupciones Perifericas
    INTCONbits.GIE = 1;     // Permite las interrupciones
    // Esto tambien se podria hacer como T0CON = 0b10000111;
}

void main(void) {
    LCD_Init();
    InitPort();
    Timer0_Init();
    
    LCD_gotoXY(0,0);
    putrsXLCD("Tiempo:");
    
    while(true){
        if(PORTBbits.RB0 == 1){
            __delay_ms(100);
            TMR0L = 6943;   // Bits bajos del Tmr0
            TMR0H = (6943) >>8;   // Bits altos del Tmr0 con corrimiento de 8 bits
            LCD_gotoXY(1,5);
            putrsXLCD("3 Segundos");
            LATAbits.LA5 = 1; // Cuando los 2 son distintos prende el motor
            LATAbits.LA4 = 0;
        }else{
            __delay_ms(100);
            LCD_gotoXY(1,5);
            putrsXLCD("No se toco boton");
        }
    }
}

void __interrupt() ISR_TIMER0(void){
    if(INTCONbits.TMR0IF){
        LCD_gotoXY(1,5);
        putrsXLCD("Terminado");
        LATAbits.LA5 = 1;           // Cuando los 2 son iguales apaga el motor
        LATAbits.LA4 = 1;
        INTCONbits.TMR0IF = 0;      // Se baja la Bandera de interrupcion Tmr0
    }
}