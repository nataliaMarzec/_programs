/*
 * Boton.c
 *  Created on: 4 oct. 2019
 *      Author: natim
 */
#include "../../botonEnUno/inc/Boton2.h"


void nullHandler(void *);
void iniciarDelay(Boton * boton);
void cambiarEstado(Boton * boton, BotonEstado state);
void cambiarMovimiento(Boton * boton, BotonMovimiento movimiento);

void boton_init(Boton * boton, gpioMap_t gpio, void * model) {
	 boton->gpio = gpio;
	 boton->onPress = nullHandler;
	 boton->onRelease = nullHandler;
	 boton->state = Up;
	 boton->model = model;
	 boton->movimiento = Apagado;
}


void nullHandler(void * model){
}

void boton_onPress(Boton * boton, evento eventHandler) {
	 boton->onPress = eventHandler;
}

void boton_onRelease(Boton *  boton, evento eventHandler) {
	 boton->onRelease = eventHandler;
}

void cambiarEstado(Boton *  boton, BotonEstado state) {
	 boton->state = state;
}

void cambiarMovimiento(Boton *  boton, BotonMovimiento movimiento) {
	 boton->movimiento = movimiento;
}

void iniciarDelay(Boton *  boton) {
	delayInit(& boton->delay, 40);
}

void actualizarBoton(Boton *  boton,Sensor2 * sensor, int x, int y , int z) {
	int tickActual = tickRead();
    int tiempoPasado = tickActual -  boton->ultimoCambio;
    int detectorMovimiento=Apagado;
	bool_t leyendo = gpioRead(  boton->gpio );
    int contMovimiento=0;
    int varx=x; int vary=y; int varz=z;
	bool_t presionado = !leyendo;
	switch( boton->state) {

		case Up : {
			if(presionado) {
				cambiarEstado( boton, Falling);

				if(contMovimiento>2){
				detectorMovimiento=Andando;
				printf("Andando %d",detectorMovimiento);
				contMovimiento++;

				 boton->ultimoCambio=tickActual;
				}
				iniciarDelay( boton);
			}
			break;
		};


		case Down : {
			if(!presionado) {
				cambiarEstado( boton, Rising);
				if(tiempoPasado>30){
				detectorMovimiento=Apagado;
				 boton->ultimoCambio=tickActual;
			    }
				iniciarDelay( boton);
			}
			break;
		};
		case Falling : {
			if(delayRead(&boton->delay)) {
				if(presionado) {
					cambiarEstado(boton, Down);
					 boton->onPress(boton->model);
				}
				else {
					cambiarEstado(boton, Up);
				}
			}
			break;
		}
		case Rising : {
			if(delayRead(&boton->delay)) {
				if(!presionado) {
					cambiarEstado(boton, Up);
					 boton->onRelease(boton->model);
				}
				else {
					cambiarEstado(boton, Down);
				}
			}
			break;
		}

	}
}


