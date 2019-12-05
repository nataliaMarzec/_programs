

#include <sapi.h>
#include "semaforoEstados.h"

void controladorSemaforo_inciar(ControladorSemaforo * cs){
	cs->estado = R;
	cs->ultimoCambio =  tickRead();
}

void controladorSemaforo_UpDate(ControladorSemaforo * cs){
	int tickActual = tickRead();
	int tiempoPasado = tickActual - cs->ultimoCambio;

	switch(cs->estado){
		case R :{
			if(tiempoPasado >= 1000){
				cs->estado=AR;
				cs->ultimoCambio=tickActual;
			}break;
		}
		case AR :{
			if(tiempoPasado >= 2000){
				cs->estado=V;
				cs->ultimoCambio=tickActual;
			}break;
		}
		case V :{
			if (tiempoPasado >= 3000){
				cs->estado = AV;
				cs->ultimoCambio = tickActual;
			}break;
		}
		case AV :{
			if(tiempoPasado >= 4000){
				cs->estado = R;
				cs->ultimoCambio = tickActual;
			}break;
		}
	}
}

void controladorSemaforo_Prender(ControladorSemaforo * cs){

	switch(cs->estado){

	case R:{
			gpioWrite(LED2,1);
			gpioWrite(LED1,0);
			gpioWrite(LED3,0);
		}break;
	case AR:{
			gpioWrite(LED2,1);
			gpioWrite(LED1,1);
			gpioWrite(LED3,0);
		}break;
	case V:{
			gpioWrite(LED2,0);
			gpioWrite(LED1,0);
			gpioWrite(LED3,1);
		}break;
	case AV:{
			gpioWrite(LED2,0);
			gpioWrite(LED1,1);
			gpioWrite(LED3,1);
			}break;
	}
}


