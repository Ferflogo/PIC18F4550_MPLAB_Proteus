/*
 * File:   Programa_principal.c
 * Author: FernandoFG
 *
 * Created on 17 de marzo de 2020, 05:02 PM
 */


#include <xc.h>
#include "Configuracion.h"
#include "LCD_libreria.h"

void LCD_Init(){
    OpenXLCD(FOUR_BIT & LINES_5X7);
    while(BusyXLCD()); // Se pregunta si el LCD esta ocupado
    WriteCmdXLCD(0x06); // Mover cursor a la derecha
    WriteCmdXLCD(0x0C); // Desactiva el cursor
}

void main(void) {
    LCD_Init();
    LCD_gotoXY(0,0);
    putrsXLCD("**POKEMON GO!**");
    __delay_ms(200);
    LCD_gotoXY(1,0);
    putrsXLCD("Presiona Start!");
    __delay_ms(200);
    /*LCD_gotoXY(0,0);
    *putrsXLCD("SOY EL PUTOAMO");
    *__delay_ms(1);*/
}
