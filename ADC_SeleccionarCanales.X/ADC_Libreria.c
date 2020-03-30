/*
 * File:   ADC_Libreria.c
 * Author: FernandoFG
 *
 * Created on 29 de marzo de 2020, 06:21 PM
 */


#include <xc.h>

/*
 *  Se crea esta libreria para configurar la lectura del puerto y la comunicacion con el 
 * LDC. Esta Libreria tiene la facilidad de poder definir distintos canales de entrada
 * analogica
 */

// Es la misma configuracion que se utiliza en el main

void ADC_Init(void){
    ADCON1bits.PCFG = 0b1100;   // AN0, AN1 y AN2
    ADCON1bits.VCFG = 0;        // Voltaje de referencia seran Vref+ = Vdd y Vref- = Vss
    ADCON0 = 0;                 /* El canal utilizado es el 0000 (AN0)
                                * GO/DONE = 0 -> Estatus de la Conversion
                                *      *Cuando ADON = 1
                                *          Conversion en progreso GO/DONE = 1
                                *          A/D Idle (en espera)   GO/DONE = 0
                                * ADON = 0 -> El modulo esta desabilitado**
                                */
    ADCON2bits.ACQT = 3;        // 16TAD (A/D Acquisition Time Select bits))
    ADCON2bits.ADCS = 5;        // FOSC/16 (A/D Convserion Clock Select bits))
    ADCON2bits.ADFM = 1;        // Justificacion Derecha
}

unsigned int ADC_Read(unsigned char ch){
    if(ch > 13)return 0;
    ADCON0 = 0x00;                      // Define el ADCON0 como todo en cero
    ADCON0 = (ch<<2);                   /* Este corrimiento se realiza para que el canal
                                        * coincida con CHS3:CHS0, ya que si no se corre
                                        * estaria en los bits de GO/DONE y ADON
                                        */
    ADCON0bits.ADON = 1;                // Habilita la conversion
    ADCON0bits.GO_DONE = 1;             // Se avisa que se esta realizando una conversion
    while(ADCON0bits.GO_DONE == 1);     //Mantiene un bucle mientras se realiza la conversion
    ADCON0bits.ADON = 0;                 // Se deshabilita las conversiones
    return ADRES;                       // Registro donde se guarda la conversion de el dato
}