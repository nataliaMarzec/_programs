/**
 * Pulsador.h
 * Autor: natim
 */

#ifndef PROGRAMS_PULSERA_INC_PULSADOR_H_
#define PROGRAMS_PULSERA_INC_PULSADOR_H_

#include "sapi.h"

typedef enum {
	UP1_, FALLING1_, DOWN1_, RISING1_,
} EstadoPulsador;

typedef void (*evento)(void *);

typedef struct Pulsador {
	gpioMap_t gpio;
	evento onPress;
	evento onRelease;
	void * model;
	EstadoPulsador estadoP;
	delay_t delay;
} Pulsador;


void inicializarDatosPulsadorDeArranque(Pulsador * pul , gpioMap_t gpio, void * model);
void actualizarPulsador(Pulsador * pul);
void pulsador_onPress(Pulsador * pul, evento onPress);
void pulsador_onRelease(Pulsador * pul, evento onRelease);


#endif  /* PROGRAMS_PULSERA_INC_PULSADOR_H_ */
