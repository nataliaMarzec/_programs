/*
 * samaforoEstados.h
 *
 */

#ifndef SAMAFOROESTADOS_H_
#define SAMAFOROESTADOS_H_

enum EstadoSem {
	R,AR,V,AV
};

typedef struct Semaforo {
	int LuzRoja;
	int LuzAmarilla;
	int LuzVerde;

} Semaforo;

typedef struct ControladorSemaforo {
	int estado;
	int ultimoCambio;
	Semaforo sema;

	int TiempoRoja;
	int TiempoAmarilla;
	int TiempoVerde;
} ControladorSemaforo;


void controladorSemaforo_inciar(ControladorSemaforo * cs);
void controladorSemaforo_UpDate(ControladorSemaforo * cs);
void controladorSemaforo_Prender(ControladorSemaforo * cs);


#endif /* SAMAFOROESTADOS_H_ */
