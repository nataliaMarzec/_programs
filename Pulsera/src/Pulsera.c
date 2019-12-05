/*
 * Pulsera.c
 *
 *  Created on: 12 oct. 2019
 *      Author: natim
 */

#ifndef NULL
	#define NULL 0
#endif
#include "PulseraRender.h"
#include "sapi.h"

void PulseraInit(Pulsera * p, unsigned estado){
	p->estado=estado;
	p->observerP = NULL;
	p->funcion = NULL;
}

unsigned char habilitarPulsera(Pulsera* model){
	return model->estado;
}

void setEstadoPulsera(Pulsera* model,Estados valor){
	model->estado=valor;
}

void pulseraEnMovimiento(Pulsera* model){
	setEstadoPulsera(model,EN_MOVIMIENTO);
//	delayInit(&model->timeInit,200);
}

void pulseraDetenida(Pulsera* model){
	setEstadoPulsera(model,DETENIDO);
}

void pulseraUpdate(Pulsera * p){
		switch(p->estado) {

			case EN_MOVIMIENTO : {
				if(delayRead(&p->timeInit)){
					printf("TE MOVISTE");
					p->estado=DETENIDO;

			  }
				break;
			};
			case DETENIDO : {

		}

	}
}

//void pulsera_setObservador(Pulsera * p, void * observerP,funcion f ) {
//	p->observerP = observerP;
//	p->funcion = f;
//}
//
//void tickUltimoCambio(Pulsera p){
////    delay_t tiempoPasado=tiempoActual-&p->tickLastTime;
//}
////ESTADOS:
//void funcionEventoCambiaElEstado(Pulsera *p, void * observerP){
//// IF PARA EL BLUETOOH
//}

//unsigned char pulsera_teMoviste(Pulsera * p) {
//	p->estado=EN_MOVIMIENTO;
//	p->timeInit = tickRead();
//	return p->estado;
//}
//void timeOut(Pulsera * p) {
//	delayInit(&p->timeOut, 30);
//}
//
