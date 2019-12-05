/*
 * PulseraRender.c
 *
 *  Created on: 12 oct. 2019
 *      Author: natim
 */
#include <sapi.h>
#include "PulseraRender.h"

void renderizar(PulseraRender * render,Pulsera * modelo, gpioMap_t gpio) {
	render->pulsera = modelo;
	render->gpio = gpio;
}

void update(PulseraRender * render) {
	gpioWrite(render->gpio,habilitarPulsera(render->pulsera));
}


