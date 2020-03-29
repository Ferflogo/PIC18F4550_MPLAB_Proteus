/*
 * File:   Main.c
 * Author: FernandoFG
 *
 * Created on 27 de marzo de 2020, 04:52 PM
 */


#include <xc.h>
#include "Configuracion.h"

/*
 *      Configuracion de ADC (Analog-to-Digital Converter)
 * 
 *  Este modulo posee 13 entradas para el PIC18F4550 y posee una RESOLUCION de 10bits
 *  (10 bits => 2^10 = 1024).
 *  Posee 5 registros:
 *              A/D Result High Register (ADRESH)
 *              A/D Result LOW Register (ADRESL)
 *              A/D Control Register 0 (ADCON0)
 *              A/D Control Register 1 (ADCON1)
 *              A/D Control Register 2 (ADCON2)
 * 
 *  Para poder configurar el modulo del ADC se debe:
 *      1.Configurar A/D Module:
 *          *Configurar los pines Analogicos, Tension de Referencia y I/O Digitales (ADCON1)
 *          *Seleccionar A/D Canal de entrada (ADCON0 / input Channel)
 *          *Seleccionar A/D Tiempo de adquisicion (ADCON2 / acquisition time)
 *          *Seleccionar A/D Conversion de Reloj (ADCON2 / conversion time)
 *          *Encender Modulo A/D (ADCON0)
 * 
 *      2.Configuracion interrupcion A/D (si es requerido)
 *          * Limpiar bit ADIF
 *          * Poner bit ADIE (Enable)
 *          * Poner GIE (Enable Global Interrupts)
 * 
 *      3. Esperar el tiempo requerido de adquisicion
 * 
 *      4. Comenzar Conversion: *Poner bit GO/DONE (ADCON0 registro)
 *      
 *  Nota:
 *      El voltaje de referencia (vref) sirve para agregar un offset a la conversio, ejemplo
 *  si tenemos una tension de 5V y un vref de 3V, la converion seria en base a Vdd-Vref = 2V
 *  y nuestra resolucion pasaria de 5V -> 4.8mV a 2V -> 1.95mV.
 * 
 *      El tiempo de conversion por bit esta definido por el TAD como son 10 bits la conversion
 *  es de minimo 11 TAD. EL TAD Varia dependiento del Periodo de oscilador (TOSC)
 * 
 *      20MHz -> 1/20MHz = 50ns : TOSC
 * 
 *      Para este PIC el TAD Min es de 0.7us, TAD > 0.7us
 * 
 *      8TOSC = 8*50ns = 0.4us NO SE PUEDE UTILIZAR
 *      16TOSC = 16*50ns = 0.8us SI SE PUEDE UTILIZAR
 * 
 *      TAD = 0.8us -> X*TAD > 2.45us, si X es 6, X*TAD = 4.8us
 * 
 *  El ADFM: A/D Result format Select bit
 *      Esta es la justificacion si es derecha o izquierda, lo que quiere decir es si guarda
 *      desde los bits mas significativos o menos significativos
 * 
 */

void Init_ADC(void){
    TRISA = 1;              // Puerto A de Entrada
    TRISD = 0;              // Puerto D como Salida
    TRISC = 0;              // Puerto C como Salida
    ADCON1bits.PCFG = 0;    // Todos los Puertos Analogicos
    ADCON1bits.VCFG = 0;    // Voltaje de referencia seran Vref+ = Vdd y Vref- = Vss
    ADCON0 = 0;             /* El canal utilizado es el 0000 (AN0)
                             * GO/DONE = 0 -> Estatus de la Conversion
                             *      *Cuando ADON = 1
                             *          Conversion en progreso GO/DONE = 1
                             *          A/D Idle (en espera)   GO/DONE = 0
                             * ADON = 0 -> El modulo esta desabilitado**
                             */
    ADCON2bits.ACQT = 3;    // 16TAD (A/D Acquisition Time Select bits))
    ADCON2bits.ADCS = 5;    // FOSC/16 (A/D Convserion Clock Select bits))
    ADCON2bits.ADFM = 1;    // Justificacion Derecha
}

void main(void) {
    Init_ADC();
    ADCON0bits.ADON = 1;    // Encendemos o habilitamos el modulo A/D**
    while(1){
        ADCON0bits.GO_DONE = 1;
        while(ADCON0bits.GO_DONE == 1);
        PORTD = ADRESL;
        PORTC = ADRESH;
    }
    return;
}
