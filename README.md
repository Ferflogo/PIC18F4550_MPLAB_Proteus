# PIC18F4550_MPLAB_Proteus

### BIENVENIDO AL MUNDO DE PROGRAMACION DE MICROCONTROLADORES ###

En este repositorio encontraras ejemplos de programas en C compilados en xC8 para el microcontrolador
PIC18F4550 donde encontraras configuraciones de puertos, timers, contadores,etc y programas para que 
puedas hacer tus proyectos con este micro. Estos estan basados en los tutoriales de WelsTheory, el cual
es un Youtuber que te invito a ver, ya que podras aprender mucho con el.

Encontraras ejemplos comentados sobre la utilizacion de pines I/O, interrupciones, Timers, Contadores
ADC(Convertidores de Analog-to-Digital), etc. A parte encontraras documentos de Proteus con las
simulaciones de cada ejemplo.

Espero que estos ejemplos te sean de mucha ayuda!!!

Nota: Para poder compilar los programas deberas poner en MPLAB X IDE(la version que estoy usando es v5.25)
los archivos .c en Source Files (el Programa_principal.c y Configuracion.c) y los archivos .h en Header Files
(Configuracion.h), para proteus dentro del programa, deberas dar doble clik en el microcontrolador o click
derecho -> Edit Properties y en Program File subir el archivo .hex que genera al compilar el MPLAB, este esta
en la carpeta dist y listo ya puedes simular el programa.

# Importante

Los archivos de Proteus que tengan LCD cuando se simula se debe apretar el MCLR(Master Clear) un par de veces
para que el LCD funcione, seguirle apretando hasta que funcione XD !!!
