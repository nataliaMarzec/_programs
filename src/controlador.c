/*
 * controlador.c
 *
 *  Created on: 14 sep. 2019
 *      Author: natim
 */
#include "controlador.h"
#include <sapi.h>

void controladorsemaforo_inicializar(controladorsemaforo * cs) {
	cs->estado = Rojo;
	cs->ultimoCambio = tickRead();
}

void controladorsemaforo_update(controladorsemaforo * cs) {
	int tickActual = tickRead();
	int tickPasado = tickActual - cs->ultimoCambio;

	switch (cs->estado) {
	case Rojo: {
		if (tickPasado >= 5000) {
			cs->estado = AmarilloRojo;
			cs->ultimoCambio = tickActual;
		}
		break;
	}

	case AmarilloRojo: {
		if (tickPasado >= 2000) {
			cs->estado = Verde;
			cs->ultimoCambio = tickActual;

		}
		break;
	}
	case Verde: {
		if (tickPasado >= 4000) {
			cs->estado = AmarilloVerde;
			cs->ultimoCambio = tickActual;
		}
		break;
	}
	case AmarilloVerde: {
		if (tickPasado >= 2000) {
			cs->estado = Rojo;
			cs->ultimoCambio = tickActual;
		}
		break;
	}

	}
}

void controladorsemaforo_render(controladorsemaforo* cs) {

	switch (cs->estado) {
	case Rojo: {
		gpioWrite(LED1, 0);
		gpioWrite(LED2, 1);
		gpioWrite(LED3, 0);
		break;
	}
	case AmarilloRojo: {
		gpioWrite(LED1, 1);
		gpioWrite(LED2, 1);
		gpioWrite(LED3, 0);
		break;
	}
	case Verde: {
		gpioWrite(LED1, 0);
		gpioWrite(LED2, 0);
		gpioWrite(LED3, 1);
		break;
	}
	case AmarilloVerde: {
		gpioWrite(LED1, 0);
		gpioWrite(LED2, 1);
		gpioWrite(LED3, 1);
		break;
	}

	}
}

