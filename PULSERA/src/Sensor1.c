/*
 * Sensor.c 2
 * modelo tiene la informacion que tendria la base de datos
 */

#include "Sensor1.h"
#include "Pulsera1.h"
MPU9250_address_t addrs = MPU9250_ADDRESS_0;

void nullHandlerSensor1(void *);
void cambiarEstado(Sensor1 * sensor, SensorEstado estado);
void iniciarContadorDelay(Sensor1 * sensor);


//INICIALIZA AL ULTIMO CAMBIO MPUREAD() Y ARRANCA CON LECTURA ACTUAL,
void iniciarSensorMPU9250(Sensor1 * sensor, void * model,int8_t status) {
	sensor->iniciar = mpu9250Read();
//	MPU9250_address_t addr = MPU9250_ADDRESS_0;
	sensor->addr = status;
	sensor->model = model;
	sensor->onInitial = nullHandlerSensor1;
	sensor->onFinish = nullHandlerSensor1;
	sensor->state = Levantado1_;
	sensor->tiempoComenzado = tickRead();
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
	delayInit(&sensor->delay,10000);
}
void iniciarTiempo(Sensor1 * s) {
	Pulsera1 * pulsera = (Pulsera1 *) s->model;
//	delayInit(&pulsera->timeInit, 5);
}


void actualizarSensor(Sensor1 * sensor) {
	sensor->addr;
	mpu9250Read();

	delay_t tickActual = tickRead();
	delay_t tiempoPasado = tickActual - sensor->tiempoComenzado;

	float lecturaActualX = mpu9250GetAccelX_mss();
	float lecturaActualY = mpu9250GetAccelY_mss();
	float lecturaActualZ = mpu9250GetAccelZ_mss();

	//comparar con la sensibilidad- movimiento brusco o detenido
	float intervaloEvaluacionX = lecturaActualX
			- sensor->ultimaLecturaX;
	float intervaloEvaluacionY = lecturaActualY
			- sensor->ultimaLecturaY;
	float intervaloEvaluacionZ = lecturaActualZ
			- sensor->ultimaLecturaZ;

//    int8_t tickUltimaEvaluacion ;

	switch (sensor->state) {
		case Levantado1_: {
			if (sensor->sensibilidad < intervaloEvaluacionX
				|| sensor->sensibilidad < intervaloEvaluacionX
				|| sensor->sensibilidad < intervaloEvaluacionX) {

				cambiarEstado(sensor, Movimiento1_);
//				iniciarTiempo(sensor);
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
				iniciarTiempo(sensor);
//				iniciarContadorDelay(sensor);
				printf("EN_MOVIMIENTO  lecturaActualX: %f ,últimaLecturaX: %f ,intervaloEvaluacionX: %f \n",
					  lecturaActualX, sensor->ultimaLecturaX, intervaloEvaluacionX);
				printf("EN_MOVIMIENTO  lecturaActualY: %f ,últimaLecturaY: %f ,intervaloEvaluacionY: %f \n",
									  lecturaActualY, sensor->ultimaLecturaY, intervaloEvaluacionY);
				printf("EN_MOVIMIENTO  lecturaActualZ: %f ,últimaLecturaZ: %f ,intervaloEvaluacionZ: %f \n",
									  lecturaActualZ, sensor->ultimaLecturaZ, intervaloEvaluacionZ);


			} else {
					cambiarEstado(sensor, Quieto1_);
//		            iniciarTiempo(sensor);
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
//				iniciarTiempo(sensor);
				iniciarContadorDelay(sensor);
				sensor->onFinish(sensor->model);
				printf("estoy quieto... lecturaActualX %f  , últimaLecturaX: %f,intervaloEvaluacionX%f \n",
                  lecturaActualX, sensor->ultimaLecturaX,intervaloEvaluacionX);
		}
		}
		else {
			cambiarEstado(sensor, Movimiento1_);
//			iniciarTiempo(sensor);
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


