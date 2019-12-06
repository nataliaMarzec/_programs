/* ENTRADA
 * boton (Arranque)
 *
 * */

#include "BotonArranque.h"

void nullHandlerBoton(void *);
void initDelayCounter(BotonArranque * b);
void cambiaEstado(BotonArranque * b, EstadoB estado);


void inicializarDatosBotonDeArranque(BotonArranque * boton , gpioMap_t gpio, void * model){
	boton->gpio = gpio;
	boton->onPress = nullHandlerBoton;
	boton->onRelease = nullHandlerBoton;
	boton->estadoB = UP_;
	boton->model = model;
}

void nullHandlerBoton(void * model){

}

void boton_onPress(BotonArranque * b, evento onPress) {
	b->onPress = onPress;
}

void boton_onRelease(BotonArranque * b, evento onRelease) {
	b->onRelease = onRelease;
}

void cambiaEstado(BotonArranque * b, EstadoB estado) {
	b->estadoB = estado;
}

void initDelayCounter(BotonArranque * b) {
	delayInit(&b->delay, 40);
}
//void iniciarTiempoDePulsera(Boton * b){
//	Pulsera * pulsera = (Pulsera *)b->model;
//	delayInit(&pulsera->timeInit,20);
//}

void actualizarBoton(BotonArranque * b) {
	bool_t leyendo = gpioRead( b->gpio );
	bool_t presionado = !leyendo;

	switch(b->estadoB) {

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
					printf("BOTONNNNNNNNNNN PRESIONADO");
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
		}
		default : {
					//error
					cambiaEstado(b, presionado ? DOWN_ : UP_);
				}

	}

}

