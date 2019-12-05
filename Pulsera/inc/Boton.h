/**
 * Button.h
 * Autor: natim
 */

#ifndef PROGRAMS_PULSERA_INC_BOTON_H_
#define PROGRAMS_PULSERA_INC_BOTON_H_

#include "sapi.h"

typedef enum {
	UP_, FALLING_, DOWN_, RISING_,
} Estado;

typedef void (*evento)(void *);

typedef struct Boton {
	gpioMap_t gpio;
	evento onPress;
	evento onRelease;
	void * model;
	Estado estado;
	delay_t delay;
} Boton;


void inicializarDatosBotonDeArranque(Boton * boton , gpioMap_t gpio, void * model);
void actualizarBoton(Boton * boton);
void boton_onPress(Boton * boton, evento onPress);
void boton_onRelease(Boton * boton, evento onRelease);


#endif  /* PROGRAMS_PULSERA_INC_BOTON_H_ */
