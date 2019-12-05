/* ENTRADA
 * boton (Arranque)
 *
 * */

#include "Boton.h"

void nullHandlerBoton(void *);
void initDelayCounter(Boton * b);
void cambiaEstado(Boton * b, Estado estado);


void inicializarDatosBotonDeArranque(Boton * boton , gpioMap_t gpio, void * model){
	boton->gpio = gpio;
	boton->onPress = nullHandlerBoton;
	boton->onRelease = nullHandlerBoton;
	boton->estado = UP_;
	boton->model = model;
}

void nullHandlerBoton(void * model){

}

void boton_onPress(Boton * b, evento onPress) {
	b->onPress = onPress;
}

void boton_onRelease(Boton * b, evento onRelease) {
	b->onRelease = onRelease;
}

void cambiaEstado(Boton * b, Estado estado) {
	b->estado = estado;
}

void initDelayCounter(Boton * b) {
	delayInit(&b->delay, 40);
}
//void iniciarTiempoDePulsera(Boton * b){
//	Pulsera * pulsera = (Pulsera *)b->model;
//	delayInit(&pulsera->timeInit,20);
//}

void actualizarBoton(Boton * b) {
	bool_t leyendo = gpioRead( b->gpio );
	bool_t presionado = !leyendo;

	switch(b->estado) {

		case UP_ : {
			if(presionado) {
				cambiaEstado(b, FALLING_);
				initDelayCounter(b);
			}
			break;
		};
		case DOWN_ : {
			if(!presionado) {
				cambiaEstado(b, RISING_);
				initDelayCounter(b);
			}
			break;
		};
		case FALLING_ : {
			if(delayRead(&b->delay)) {
				if(presionado) {
					cambiaEstado(b, DOWN_);
					b->onPress(b->model);
		     }

				else {
					cambiaEstado(b, UP_);
				}
			}
			break;
		};
		case RISING_ : {
			if(delayRead(&b->delay)) {
				if(!presionado) {
					cambiaEstado(b, UP_);
					b->onRelease(b->model);
				}
				else {
					cambiaEstado(b, DOWN_);
				}
			}
			break;
		};
	}

}

