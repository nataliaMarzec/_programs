/*
 * main.c
 *
 *  Created on: 20 sep. 2019
 *      Author: natim
 */
#include <sapi.h>
#include "estadoBoton.h"

void on_realese() {
    gpioWrite(LED3,OFF);
	gpioWrite(LED1,OFF);

}

void on_press() {
   gpioWrite(LED1,ON);
   gpioWrite(LED3,ON);
}


void main(void) {

	boardConfig();

	boton b;
	botonDos bdos;


    int pin;
    int pindos;

    pin=TEC1;
    pindos=TEC2;

	inicializar(&b,&bdos, on_press,on_realese,pin,pindos);

	while (1) {
		boton_Actualizar(&b,&bdos);

		delay(1);
	}

}

