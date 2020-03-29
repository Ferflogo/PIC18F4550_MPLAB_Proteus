/*
 * File:   Main.c
 * Author: FernandoFG
 *
 * Created on 27 de marzo de 2020, 04:52 PM
 */


#include <xc.h>
#include "Configuracion.h"

/*      PWM Mode (Pulse-Width Modulation)
 * 
 *  El Pic18f4550 posee dos pines de PWM el CCP1(RC2) y CCP2(RC1), utiliza el Timer2.
 *  Para calcular su periodo e utilizarlo en el registro PR2 se debe aplicar la sig
 *  formula => PWM Period = [(PR2) + 1]*4* TOSC * (TMR2 Prescale Value).
 * 
 *  En este caso se desea un periodo de 1/8kHz = (PR2 +1)*4*(1/200)*16
 *          => PR2 = 38.06 = 0x26
 * 
 *  Para modificar el Ciclo de Trabajo se debe especificar en el registro CCPRxL, en este
 *  caso el 1 o 2 y se calcula de la siguiente forma:  
 *               => PWM Duty Cicle = (CCPRxL:CCPxCON<5:4>)*TOSC*(TMR2 Rescale Value)
 * 
 * En este caso si trabajara el 100% se tendria:
 *          => CCPRxL = 156
 *          => 156 -> 100% : X -> 80%
 *          =>      X = 124 = 0b0111 1100 
 * 
 * Para escribir este dato los dos primeros bits van al registro de CCPxCON
 * Por lo cual en CCPxL tendriamos 0b0001 1111
 * Y en CCPxCON 0b00
 * 
 *  Nota: Posee una resolucion de 10 bits
 */

int duty_cicle;

void InitPWM_CCP1(){
    TRISCbits.RC1 = 0; // Definiendo puerto como Salida
    TRISCbits.RC2 = 0;
    PR2 = 0x26;
    CCPR1L = 0x1F; // O 0b1 1111
    T2CON = 0x03;       // Preescalado 1:16
    CCP1CON = 0x0C; // O 0x0C
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;
}

void main(void) {
    InitPWM_CCP1();
    while(1){
        /*
         * Esta funcion sirve para cambiar el Ciclo de trabajo de
         * la senal PWM con lo cual podemos variar la tension promedio
         * que llega a un
         */
        for(duty_cicle = 0x01; duty_cicle < PR2; duty_cicle++){
            CCPR1L = duty_cicle;
            __delay_ms(20);
        }
        __delay_ms(100);
        for(duty_cicle = PR2; duty_cicle > 0x01; duty_cicle--){
            CCPR1L = duty_cicle;
            __delay_ms(20);
        }
        __delay_ms(100);
        

//       Cambio de Ciclo de Trabajo con pulsadores:
        /*
         * if(PORTXbits.RX# == 0){
         *  duty_cicle = duty_cicle +1;
         * if( duty_cicle > PR2 ){
         *      duty_cicle = PR2 -1;
         *  }else{
         *      CCPR1L = duty_cicle
         *  }
         * }
         */
        
    }
    return;
}
