/*
 * Sensor.h
 *      Author: natim
 */

#ifndef PROGRAMS_PULSERA_INC_SENSOR_H_
#define PROGRAMS_PULSERA_INC_SENSOR_H_

#include "sapi.h"
#include "Pulsera.h"

//typedef enum {
//	Brusco, Detenido
//}EstadoMovimiento;

typedef enum {
	Levantado_,Quieto_,Movimiento_
}SensorEstado;

typedef void (*evento)(void *);

typedef struct Sensor {
	evento onInitial;
	evento onFinish;
	void * model;
	SensorEstado state;
	delay_t delay;
	delay_t timeInit;
	//delay_t timeLast;
//	MPU9250_address_t addrs;
    float ultimaLecturaX;
    float ultimaLecturaY;
    float ultimaLecturaZ;
//    int8_t iniciar;
    bool_t iniciar;
    float sensibilidad;
//    bool_t estadoInicial;
//    int8_t tickDeUltimaEvaluacion;
} Sensor;


void iniciarSensorMPU9250(Sensor * sensor ,void * model);
void sensor_onInitial(Sensor * sensor, evento onInitial);
void sensor_onFinish(Sensor * sensor,evento onFinish);
void actualizarSensor(Sensor * sensor);




#endif /* PROGRAMS_PULSERA_INC_SENSOR_H_ */
