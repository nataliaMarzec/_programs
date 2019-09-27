
#include <sapi.h>
#include "estadoBlinky.h"

void inciar(blinky * bs){
	bs->estado = PRENDIDO;
	bs->ultimoCambio =  tickRead();
}
void controladorBlinky_Update(blinky * bs){
	int tickActual = tickRead();
	int tiempoPasado = tickActual - bs->ultimoCambio;

	switch(bs->estado){
		case APAGADO :{
			if(tiempoPasado >= 100){
				bs->estado=PRENDIDO;
				bs->ultimoCambio=tickActual;
			}break;
		}
		case PRENDIDO :{
			if(tiempoPasado >= 200){
				bs->estado=APAGADO;
				bs->ultimoCambio=tickActual;
			}break;
		}
	}
}

void controladorBlinky_Prender(blinky * bs){

	switch(bs->estado){

	case PRENDIDO:{
			gpioWrite( LEDB, ON );
			gpioWrite( LEDR, ON );
			gpioWrite( LEDG, ON );
		}break;
	case APAGADO:{
			gpioWrite( LEDB, OFF );
			gpioWrite( LEDR, OFF );
			gpioWrite( LEDG, OFF);
		}break;
	}
}
