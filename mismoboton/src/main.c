/*
 * main.c
 *
 *  Created on: 20 sep. 2019
 *      Author: natim
 */
#include <sapi.h>
#include "estadoBoton.h"

void on_realese() {
    gpioWrite(LED2,OFF);
	gpioWrite(LED1,OFF);

}

void on_press() {
   gpioWrite(LED1,ON);
   gpioWrite(LED2,ON);
}

void


void main(void) {

	boardConfig();

	boton b;


    int pin;
    pin=TEC1;
	inicializar(&b, on_press,on_realese,pin);

	while (1) {
		boton_Actualizar(&b);

		delay(1);
	}

}

