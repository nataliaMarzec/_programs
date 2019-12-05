/*
 * PulseraRender.h
 *
 *  Created on: 12 oct. 2019
 *      Author: natim
 */

#ifndef PROGRAMS_PULSERA_INC_PULSERARENDER_H_
#define PROGRAMS_PULSERA_INC_PULSERARENDER_H_
#include "Pulsera.h"
#include <sapi.h>
typedef struct {
	gpioMap_t gpio;
	Pulsera * pulsera;
} PulseraRender ;

void renderizar(PulseraRender * render,Pulsera * modelo, gpioMap_t gpio);
void update(PulseraRender * render);


#endif /* PROGRAMS_PULSERA_INC_PULSERARENDER_H_ */
