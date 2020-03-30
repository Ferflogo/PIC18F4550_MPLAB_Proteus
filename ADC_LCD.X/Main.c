/*
 * File:   Main.c
 * Author: FernandoFG
 *
 * Created on 27 de marzo de 2020, 04:52 PM
 */


#include <xc.h>
#include <stdio.h>                      // Biblioteca para por convertir variables
#include "Configuracion.h"
#include "LCD_libreria.h"               // Biblioteca para utilizar ADC modificada por WelsTheory
#include "ADC_Libreria.h"               // Biblioteca para Configurar ADC y Lectura

uint16_t valorLectura;                  // Entero de 16 bits, ya que el ADRES es de 16 bits
float tension;
char datos [20];

void LCD_Init(void){
    OpenXLCD(FOUR_BIT & LINES_5X7);     // Se define el dispositivo LCD que se utilizara
    while(BusyXLCD());                  // Loop mientras se esta escribiendo en el LCD
    WriteCmdXLCD(0x06);                 // Mover cursor a la derecha
    WriteCmdXLCD(0x0C);                 // Desactivar Cursor
}

void main(void) {
    LCD_Init();
    ADC_Init();
    TRISA = 1;
    LCD_gotoXY(0,0);                    // Ubica la ubicacion donde se escribira o del cursor
    putrsXLCD("** Canales ADC **");
    __delay_ms(100);                    // Le da tiempo al LCD para escribir
    LCD_gotoXY(1,0);
    putrsXLCD("  By: Fernando  ");
    __delay_ms(1500);
    WriteCmdXLCD(BORRAR_LCD);           // Limpia el LCD
    while(1){
        LCD_gotoXY(0,0);
        putrsXLCD("Tension medida: ");
        __delay_ms(100);
        valorLectura = ADC_Read(0);         // Se guarda el valor Leido
        tension = (valorLectura*5.0)/1023;  // Valor obtenida por la resolucion
        LCD_gotoXY(1,12);
        sprintf(datos,"%.2f",tension);      // Convierte la variable y la almacena en datos
        putrsXLCD(datos);
        __delay_ms(500);
    }
}
