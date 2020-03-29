/*
 * File:   Programa_principal.c
 * Author: FernandoFG
 *
 * Created on 17 de marzo de 2020, 05:02 PM
 */


#include <xc.h>
#include "Configuracion.h"
#include "LCD_libreria.h"

const char ash[] = {0b00000111,
                    0b00001110,
                    0b00000101,
                    0b00001110,
                    0b00010100,
                    0b00001010,
                    0b00010001,
                    0b00000000, 0};

void LCD_Init(void){
    OpenXLCD(FOUR_BIT & LINES_5X7);
    while(BusyXLCD()); // Se pregunta si el LCD esta ocupado
    WriteCmdXLCD(0x06); // Mover cursor a la derecha
    WriteCmdXLCD(0x0C); // Desactiva el cursor
}

void SetupPorts(void){
    ADCON1bits.PCFG = 0xF;
    TRISBbits.RB0 = 1;
    INTCON2bits.RBPU = 0; // Resistencias de Pull-Up
}

void main(void) {
    LCD_Init();
    SetupPorts();
    
    LCD_gotoXY(0,0);
    putrsXLCD("**POKEMON GO!**");
    __delay_ms(300);
    LCD_gotoXY(1,0);
    putrsXLCD("Presiona Start!");
    __delay_ms(300);
    
    if(PORTBbits.RB0 == 0){
        WriteCmdXLCD(BORRAR_LCD);
        __delay_ms(5);
        LCD_WriteChr_CGRAM(ash,0); // Se necesita de un tiempo para Guardar
        __delay_ms(500);
        while(1){
            LCD_gotoXY(0,0);
            putrsXLCD("Ash Ketchup");
            __delay_ms(300);
            //LCD_gotoXY(1,0);
            //putrsXLCD(0);
            //__delay_ms(500);
            if(PORTBbits.RB7 == 0){
                
                WriteCmdXLCD(BORRAR_LCD);
                __delay_ms(5);
                LCD_gotoXY(1,0);
                putrsXLCD("Ash Camina");
                __delay_ms(300);
                
            }else{ WriteCmdXLCD(BORRAR_LCD); __delay_ms(5); }
        }
    }

}
