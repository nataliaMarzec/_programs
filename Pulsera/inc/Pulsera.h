/*
 * Pulsera.h
 *
 *  Created on: 12 oct. 2019
 *      Author: natim
 */

#ifndef PROGRAMS_PULSERA_INC_PULSERA_H_
#define PROGRAMS_PULSERA_INC_PULSERA_H_
#include <sapi.h>
struct Pulsera;

typedef enum Estados{
	EN_MOVIMIENTO,DETENIDO
}Estados;

typedef void (*funcion)(void * , struct Pulsera* );

typedef struct Pulsera{
//	unsigned char valor;-> estadoPuLsera
	funcion funcion;
	void * observerP;

	Estados estado;
	delay_t timeInit;
	delay_t timeOut;
}Pulsera;


void PulseraInit(Pulsera * p, unsigned estado);
unsigned char habilitarPulsera(Pulsera* model);

void pulsera_setObservador(Pulsera * p, void * observerP,funcion f );

void pulseraEnMovimiento(Pulsera * p);
void pulseraDetenida(Pulsera * p);
void pulseraUpdate(Pulsera * p);


#endif /* PROGRAMS_PULSERA_INC_PULSERA_H_ */
