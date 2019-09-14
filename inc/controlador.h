/*
 * controlador.h
 *
 *  Created on: 14 sep. 2019
 *      Author: natim
 */

#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

typedef struct controladorsemaforo {
	int estado;
	int ultimoCambio;

} controladorsemaforo;

typedef enum EstadoSemaforo {
	Rojo, AmarilloRojo, Verde, AmarilloVerde
} EstadoSemaforo;

typedef struct semaforo {
	int colores[5];

} semaforo;

void controladorsemaforo_inicializar(controladorsemaforo* cs);
void controladorsemaforo_update(controladorsemaforo* cs);
void controladorsemaforo_render(controladorsemaforo* cs);

#endif /* CONTROLADOR_H_ */
