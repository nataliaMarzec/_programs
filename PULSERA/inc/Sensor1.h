/*
 * Sensor.h
 *      Author: natim
 */

#ifndef PROGRAMS_PULSERA_INC_SENSOR1_H_
#define PROGRAMS_PULSERA_INC_SENSOR1_H_

#include "sapi.h"
#include "Pulsera1.h"

typedef enum {
	Levantado1_,Quieto1_,Movimiento1_
}SensorEstado;

typedef void (*evento)(void *);

typedef struct Sensor1 {
	evento onInitial;
	evento onFinish;
	void * model;
	SensorEstado state;
	delay_t delay;
	MPU9250_address_t addr;
    float ultimaLecturaX;
    float ultimaLecturaY;
    float ultimaLecturaZ;
    bool_t iniciar;
    float sensibilidad;

} Sensor1;


void iniciarSensorMPU9250(Sensor1 * sensor, void * model,int8_t status);
void sensor_onInitial(Sensor1 * sensor, evento onInitial);
void sensor_onFinish(Sensor1 * sensor,evento onFinish);
void actualizarSensor(Sensor1 * sensor);

#endif /* PROGRAMS_PULSERA_INC_SENSOR1_H_ */
