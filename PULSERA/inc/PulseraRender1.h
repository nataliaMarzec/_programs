/*
 * PulseraRender.h
 *
 *  Created on: 12 oct. 2019
 *      Author: natim
 */

#ifndef PROGRAMS_PULSERA_INC_PULSERARENDER1_H_
#define PROGRAMS_PULSERA_INC_PULSERARENDER1_H_
#include "Pulsera1.h"
#include <sapi.h>
typedef struct {
	gpioMap_t gpio;
	Pulsera1 * pulsera;
} PulseraRender1 ;

void renderizar(PulseraRender1 * render,Pulsera1 * modelo, gpioMap_t gpio);
void update(PulseraRender1 * render);


#endif /* PROGRAMS_PULSERA_INC_PULSERARENDER1_H_ */
