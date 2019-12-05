/*
 * Boton.h
 *
 *  Created on: 4 oct. 2019
 *      Author: natim
 */

#ifndef PROGRAMS_BOTONENUNO_INC_BOTON2_H_
#define PROGRAMS_BOTONENUNO_INC_BOTON2_H_

#include "../../botonEnUno/inc/Sensor2.h"
#include "sapi.h"

typedef enum {
	Apagado=0, Andando=1,
}BotonMovimiento;

typedef enum {
	Up, Falling, Down, Rising,
} BotonEstado;


typedef void (*evento)(void *);

typedef struct  Boton {
	gpioMap_t gpio;
	evento onPress;
	evento onRelease;
	void * model;
	BotonEstado state;
	delay_t delay;
	BotonMovimiento movimiento;
	int ultimoCambio;

} Boton;



void boton_init( Boton *  boton , gpioMap_t gpio, void * model);

void boton_onPress( Boton *  boton, evento handler);
void boton_onRelease( Boton *  boton, evento handler);
void actualizarBoton( Boton *  boton);



#endif /* PROGRAMS_BOTONENUNO_INC_BOTON2_H_ */
