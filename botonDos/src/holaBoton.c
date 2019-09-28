/*
 * boton.c
 *
 *  Created on: 20 sep. 2019
 *      Author: natim
 */
#include <sapi.h>
#include "estadoBoton.h"

void inicializar(boton *b, botonDos *bdos, buttonHandler onpress,
		buttonHandler onrelease, int pin, int pindos) {
	b->estado = Button_up;
	b->ultimoCambio = tickRead();
	b->onPress = onpress;
	b->onRelease = onrelease;
	b->pin = pin;
	bdos->pindos = pindos;
}

void boton_Actualizar(boton * b, botonDos *bdos) {
	int tickActual = tickRead();
	int tiempoPasado = tickActual - b->ultimoCambio;
	//APAGADO
	int APRETADO = 0;
	//PRENDIDO
	int LIBRE = 1;

	switch (b->estado, bdos->estado) {
	case Button_up: {

		if (gpioRead(b->pin) == APRETADO) {
			b->estado = Button_falling;
			b->ultimoCambio = tickActual;
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
			 if(gpioRead(b->pin) == LIBRE){
				b->onRelease();
				b->estado = Button_up;
				b->ultimoCambio = tickActual;
			 }
			}
		}
		break;
		if (tiempoPasado > 40) {
			if (gpioRead(bdos->pindos) == LIBRE) {
				bdos->onPress();
				bdos->estado = Button_down;
				bdos->ultimoCambio = tickActual;
			} else {
				bdos->onRelease();
				bdos->estado = Button_up;
				bdos->ultimoCambio = tickActual;

			}
		}
		break;
	}

	case Button_down: {
		if (gpioRead(b->pin) == LIBRE && gpioRead(bdos->pindos) == APRETADO) {
			b->estado = Button_rising;
			b->ultimoCambio = tickActual;
		}
		break;
	}

	case Button_rising: {
		if (tiempoPasado > 40) {

			if (gpioRead(b->pin) == APRETADO) {
				b->onRelease();
				b->estado = Button_down;
				b->ultimoCambio = tickActual;
			} else {
				if (gpioRead(bdos->pindos) == LIBRE) {
					bdos->estado = Button_up;
					bdos->ultimoCambio = tickActual;
				}
			}
		}
		break;
	}
	}
}
