/*
 * boton.h
 *
 *  Created on: 20 sep. 2019
 *      Author: natim
 */

#ifndef PROGRAMS_BOTON_BOTON_H_
#define PROGRAMS_BOTON_BOTON_H_

enum Estado{
	Button_up,Button_falling,Button_rising,Button_down
};

typedef void (*buttonHandler)(void);

typedef struct boton {
	int estado;
	int ultimoCambio;
	int pin;
	buttonHandler onPress;
	buttonHandler onRelease;

}boton;

typedef struct botonDos {
	int estado;
	int ultimoCambio;
	int pindos;
	buttonHandler onPress;
	buttonHandler onRelease;

}botonDos;

void inicializar(boton *b,botonDos *bdos, buttonHandler onpress, buttonHandler onrelease,int pin,int pindos);
void boton_Actualizar(boton * b,botonDos *bdos);




#endif /* PROGRAMS_BOTON_BOTON_H_ */


