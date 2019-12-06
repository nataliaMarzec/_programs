/* ENTRADA
 * Pulsador(Arranque)
 *
 * */

#include "Pulsador.h"

void nullHandlerPulsador(void *);
void initDelayCounter(Pulsador * pul);
void cambiaEstado(Pulsador * pul, EstadoPulsador estado);


void inicializarDatosPulsadorDeArranque(Pulsador * pul , gpioMap_t gpio, void * model){
	pul->gpio = gpio;
	pul->onPress = nullHandlerPulsador;
	pul->onRelease = nullHandlerPulsador;
	pul->estadoP = UP1_;
	pul->model = model;
}

void nullHandlerPulsador(void * model){

}
void cambiaEstado(Pulsador* pul,EstadoPulsador estado){
	pul->estadoP=estado;
}

void pulsador_onPress(Pulsador * pul, evento onPress) {
	pul->onPress = onPress;
}

void pulsador_onRelease(Pulsador * pul, evento onRelease) {
	pul->onRelease = onRelease;
}

void initDelayCounter(Pulsador * pul) {
	delayInit(&pul->delay, 40);
}
//void iniciarTiempoDePulsera(Boton * b){
//	Pulsera * pulsera = (Pulsera *)b->model;
//	delayInit(&pulsera->timeInit,20);
//}

void actualizarPulsador(Pulsador * pul) {
	bool_t leyendo = gpioRead( pul->gpio );
	bool_t presionado = !leyendo;

	int x =0;
	switch(pul->estadoP) {

		case UP1_ : {
			if(presionado) {
				cambiaEstado(pul, FALLING1_);
				initDelayCounter(pul);
			}
			break;
		};
		case DOWN1_ : {
			if(!presionado) {
				cambiaEstado(pul, RISING1_);
				initDelayCounter(pul);
			}
			break;
		};
		case FALLING1_ : {
			if(delayRead(&pul->delay)) {
				if(presionado) {
					printf("BOTONNNNNNNNNNN PRESIONADO x=%d",x+5);
					cambiaEstado(pul,DOWN1_);
					pul->onPress(pul->model);

		     }

				else {
					cambiaEstado(pul, UP1_);
				}
			}
			break;
		};
		case RISING1_ : {
			if(delayRead(&pul->delay)) {
				if(!presionado) {
					cambiaEstado(pul, UP1_);
					pul->onRelease(pul->model);
				}
				else {
					cambiaEstado(pul, DOWN1_);
				}
			}
			break;
		}
		default : {
					cambiaEstado(pul, presionado ? DOWN1_ : UP1_);
				}

	}

}

