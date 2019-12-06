/**
 * Button.h
 * Autor: natim
 */

#ifndef PROGRAMS_PULSERA_INC_BOTONARRANQUE_H_
#define PROGRAMS_PULSERA_INC_BOTONARRANQUE_H_

#include "sapi.h"

typedef enum {
	UP_, FALLING_, DOWN_, RISING_,
} EstadoB;

typedef void (*evento)(void *);

typedef struct BotonArranque {
	gpioMap_t gpio;
	evento onPress;
	evento onRelease;
	void * model;
	EstadoB estadoB;
	delay_t delay;
} BotonArranque;


void inicializarDatosBotonDeArranque(BotonArranque * boton , gpioMap_t gpio, void * model);
void actualizarBoton(BotonArranque * boton);
void boton_onPress(BotonArranque * boton, evento onPress);
void boton_onRelease(BotonArranque * boton, evento onRelease);


#endif  /* PROGRAMS_PULSERA_INC_BOTONARRANQUE_H_ */
