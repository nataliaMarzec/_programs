/*
 * sensor.h
 *
 *  Created on: 5 oct. 2019
 *      Author: natim
 */

#ifndef PROGRAMS_BOTONENUNO_INC_SENSOR2_H_
#define PROGRAMS_BOTONENUNO_INC_SENSOR2_H_

#include "sapi.h"


typedef enum {
	Quieto, Movimiento,
}SensorEstado;


typedef void (*ManejoDeEventosDelSensor)(void *);

typedef struct Sensor {
	gpioMap_t gpio2;
	ManejoDeEventosDelSensor onInitial2;
	ManejoDeEventosDelSensor onFinish2;
	void * model2;
	SensorEstado state2;
	int8_t duracion2;

} Sensor;



void iniciarSensorMPU9250(Sensor * sensor , gpioMap_t gpio, void * model);
void sensor_onInitial(Sensor * sensor, ManejoDeEventosDelSensor handler);
void sensor_onFinish(Sensor * sensor, ManejoDeEventosDelSensor handler);
void actualizarSensor(Sensor * sensor);





#endif /* PROGRAMS_BOTONENUNO_INC_SENSOR2_H_ */
