/*
 * Sensor1.c 2
 * modelo pulsera tiene la informacion que tendria la base de datos
 */

#include "Sensor1.h"
#include "Pulsera1.h"
MPU9250_address_t addrs = MPU9250_ADDRESS_0;

void nullHandlerSensor1(void *);
void cambiarEstado(Sensor1 * sensor, SensorEstado estado);
void iniciarContadorDelay(Sensor1 * sensor);

void iniciarSensorMPU9250(Sensor1 * sensor, void * model,int8_t status) {
	sensor->iniciar = mpu9250Read();
	sensor->addr = status;
	sensor->model = model;
	sensor->onInitial = nullHandlerSensor1;
	sensor->onFinish = nullHandlerSensor1;
	sensor->state = Levantado1_;
	sensor->ultimaLecturaX = mpu9250GetAccelX_mss();
	sensor->ultimaLecturaY = mpu9250GetAccelY_mss();
	sensor->ultimaLecturaZ = mpu9250GetAccelZ_mss();
	sensor->sensibilidad = 3.0;

}

void nullHandlerSensor1(void * model) {
}

void sensor_onInitial(Sensor1 * sensor, evento onInitial) {
	sensor->onInitial = onInitial;
}
void sensor_onFinish(Sensor1 * sensor, evento onFinish) {
	sensor->onFinish = onFinish;
}

void cambiarEstado(Sensor1 * sensor, SensorEstado estado) {
	sensor->state = estado;
}
void iniciarContadorDelay(Sensor1 * sensor) {
	delayInit(&sensor->delay,100);
}

void actualizarSensor(Sensor1 * sensor) {
	mpu9250Read();


	float lecturaActualX = mpu9250GetAccelX_mss();
	float lecturaActualY = mpu9250GetAccelY_mss();
	float lecturaActualZ = mpu9250GetAccelZ_mss();


	float intervaloEvaluacionX = lecturaActualX
			- sensor->ultimaLecturaX;
	printf("intervaloEvaluacionX %f =",intervaloEvaluacionX);


	float intervaloEvaluacionY = lecturaActualY
			- sensor->ultimaLecturaY;
	printf("intervaloEvaluacionY %f =",intervaloEvaluacionY);

	float intervaloEvaluacionZ = lecturaActualZ
			- sensor->ultimaLecturaZ;
	printf("intervaloEvaluacionZ %f =",intervaloEvaluacionZ);


	switch (sensor->state) {
		case Levantado1_: {
			if (sensor->sensibilidad < intervaloEvaluacionX
				|| sensor->sensibilidad < intervaloEvaluacionX
				|| sensor->sensibilidad < intervaloEvaluacionX) {

				cambiarEstado(sensor, Movimiento1_);
				printf("lev-mov: lecturaActualX: %f ,últimaLecturaX: %f ,intervaloEvaluacionX: %f \n",
				lecturaActualX, sensor->ultimaLecturaX, intervaloEvaluacionX);
				printf("EN_MOVIMIENTO  lecturaActualY: %f ,últimaLecturaY: %f ,intervaloEvaluacionY: %f \n",
		        lecturaActualY, sensor->ultimaLecturaY, intervaloEvaluacionY);
				printf("EN_MOVIMIENTO  lecturaActualZ: %f ,últimaLecturaZ: %f ,intervaloEvaluacionZ: %f \n",
			    lecturaActualZ, sensor->ultimaLecturaZ, intervaloEvaluacionZ);

				iniciarContadorDelay(sensor);
				sensor->ultimaLecturaX = lecturaActualX;
				sensor->ultimaLecturaY = lecturaActualY;
				sensor->ultimaLecturaZ = lecturaActualZ;

			} else {
				cambiarEstado(sensor,Quieto1_);
			}
			break;
		}

	case Movimiento1_: {
		if (delayRead(&sensor->delay)) {
			if (sensor->sensibilidad < intervaloEvaluacionX
					|| sensor->sensibilidad < intervaloEvaluacionX
					|| sensor->sensibilidad < intervaloEvaluacionX) {
				cambiarEstado(sensor,Levantado1_);
				iniciarContadorDelay(sensor);
				sensor->onInitial(sensor->model);
				printf("EN_MOVIMIENTO  lecturaActualX: %f ,últimaLecturaX: %f ,intervaloEvaluacionX: %f \n",
					  lecturaActualX, sensor->ultimaLecturaX, intervaloEvaluacionX);
				printf("EN_MOVIMIENTO  lecturaActualY: %f ,últimaLecturaY: %f ,intervaloEvaluacionY: %f \n",
									  lecturaActualY, sensor->ultimaLecturaY, intervaloEvaluacionY);
				printf("EN_MOVIMIENTO  lecturaActualZ: %f ,últimaLecturaZ: %f ,intervaloEvaluacionZ: %f \n",
									  lecturaActualZ, sensor->ultimaLecturaZ, intervaloEvaluacionZ);


			} else {
					cambiarEstado(sensor, Quieto1_);
					iniciarContadorDelay(sensor);

				}
				break;
			}


	case Quieto1_: {
		if (delayRead(&sensor->delay)) {
			if (sensor->sensibilidad > intervaloEvaluacionX
					|| sensor->sensibilidad > intervaloEvaluacionY
					|| sensor->sensibilidad > intervaloEvaluacionZ) {
				cambiarEstado(sensor, Levantado1_);
				iniciarContadorDelay(sensor);
				sensor->onFinish(sensor->model);
				printf("DETENIDO: lecturaActualX %f  , últimaLecturaX: %f,intervaloEvaluacionX%f \n",
                  lecturaActualX, sensor->ultimaLecturaX,intervaloEvaluacionX);
		}
		}
		else {
			cambiarEstado(sensor, Movimiento1_);
			iniciarContadorDelay(sensor);
			sensor->ultimaLecturaX=lecturaActualX;
			sensor->ultimaLecturaY=lecturaActualY;
			sensor->ultimaLecturaZ=lecturaActualZ;

		};
	}
		break;
	}

}
}


