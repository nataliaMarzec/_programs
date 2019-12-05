/*
 * boton.c
 *
 *  Created on: 20 sep. 2019
 *      Author: natim
 */
#include <sapi.h>
#include "estadoBoton.h"



void inicializar(boton *b, buttonHandler onpress, buttonHandler onrelease,int pin) {
	b->estado = Button_up;
	b->ultimoCambio = tickRead();
    b->onPress=onpress;
    b->onRelease=onrelease;
    b->pin=pin;
}

void boton_Actualizar(boton * b) {
	int tickActual = tickRead();
	int tiempoPasado = tickActual - b->ultimoCambio;
	//APAGADO
	int APRETADO = 0;
	//PRENDIDO
	int LIBRE = 1;

	switch (b->estado) {
	case Button_up: {

		if (gpioRead(b->pin) == 0) {
			b->estado = Button_falling;
            b->ultimoCambio=tickActual;
		}
		break;
	}

	case Button_falling: {
		if (tiempoPasado > 40) {
			if (gpioRead(b->pin) == APRETADO) {
				b->onPress();
				b->estado = Button_down;
				b->ultimoCambio = tickActual;
			} else {
				b->estado = Button_up;
				b->ultimoCambio = tickActual;
			}
		}
		break;
	}
//
	case Button_down: {
		if (gpioRead(b->pin) == LIBRE) {
			b->estado = Button_rising;
			b->ultimoCambio=tickActual;
		}
		break;
	}

	case Button_rising: {
		if (tiempoPasado > 40) {
			if (gpioRead(b->pin) == LIBRE) {
				b->onRelease();
				b->estado = Button_down;
				b->ultimoCambio = tickActual;
			} else {
				b->estado = Button_up;
				b->ultimoCambio = tickActual;
			}
		}
		break;
	}

	}
}

