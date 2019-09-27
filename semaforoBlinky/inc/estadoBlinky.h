/*
 * estadoBlinky.h
 *
 */

#ifndef PROGRAMS_SEMAFORONUEVO_INC_ESTADOBLINKY_H_
#define PROGRAMS_SEMAFORONUEVO_INC_ESTADOBLINKY_H_


enum Estado{
	PRENDIDO,APAGADO
};

typedef struct blinky {
	int estado;
	int ultimoCambio;
} blinky;

void inciar(blinky * bs);
void controladorBlinky_Update(blinky * bs);
void controladorBlinky_Prender(blinky * bs);

#endif /* PROGRAMS_SEMAFORONUEVO_INC_ESTADOBLINKY_H_ */
