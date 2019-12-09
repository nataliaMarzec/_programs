/*
 * Pulsera.h
 *
 *  Created on: 12 oct. 2019
 *      Author: natim
 */

#ifndef PROGRAMS_PULSERA_INC_PULSERA1_H_
#define PROGRAMS_PULSERA_INC_PULSERA1_H_
#include <sapi.h>
struct Pulsera1;

typedef void (*funcionp)(void * , struct Pulsera1* pul);

typedef enum Estados{
	EN_MOVIMIENTO,DETENIDO
}Estados;


typedef struct Pulsera1{
	void * observerP;
    funcionp funcionp;
	Estados estado;
	delay_t timeInit;
	delay_t timeOut;
}Pulsera1;


void PulseraInit(Pulsera1 * p, unsigned estado);
unsigned char habilitarPulsera(Pulsera1* model);

void pulsera_setObservador(Pulsera1 * p, void * observerP,funcionp f );

void pulseraEnMovimiento(Pulsera1 * p);
void pulseraDetenida(Pulsera1 * p);
void pulseraUpdate(Pulsera1 * p);


#endif /* PROGRAMS_PULSERA_INC_PULSERA1_H_ */
