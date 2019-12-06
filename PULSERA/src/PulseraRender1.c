/*
 * PulseraRender.c
 *
 *  Created on: 12 oct. 2019
 *      Author: natim
 */
#include <sapi.h>
#include "PulseraRender1.h"

void renderizar(PulseraRender1 * render,Pulsera1 * modelo, gpioMap_t gpio) {
	render->pulsera = modelo;
	render->gpio = gpio;
}

void update(PulseraRender1 * render) {
	gpioWrite(render->gpio,habilitarPulsera(render->pulsera));
}


