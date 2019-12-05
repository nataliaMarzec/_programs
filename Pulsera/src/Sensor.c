/*
 * Sensor.c 2
 * modelo tiene la informacion que tendria la base de datos
 */

#include "Sensor.h"
#include "Pulsera.h"
MPU9250_address_t addrs = MPU9250_ADDRESS_0;

void nullHandlerSensor(void *);
void cambiarEstado(Sensor * sensor, SensorEstado estado);
void iniciarContadorDelay(Sensor * sensor);

//INICIALIZA AL ULTIMO CAMBIO MPUREAD() Y ARRANCA CON LECTURA ACTUAL,
void iniciarSensorMPU9250(Sensor * sensor, void * model) {
	mpu9250Read();
//	MPU9250_address_t addr = MPU9250_ADDRESS_0;
//	sensor->addrs = mpu9250Init(addr);
	sensor->model = model;
	sensor->onInitial = nullHandlerSensor;
	sensor->onFinish = nullHandlerSensor;
	sensor->state = Levantado_;
	sensor->iniciar = mpu9250Read();
//	sensor->timeInit;
//	sensor->timeLast = tickRead();
	sensor->ultimaLecturaX = mpu9250GetAccelX_mss();
	sensor->ultimaLecturaY = mpu9250GetAccelY_mss();
	sensor->ultimaLecturaZ = mpu9250GetAccelZ_mss();
	sensor->sensibilidad = 3.0;


}

void nullHandlerSensor(void * model) {
}

void sensor_onInitial(Sensor * sensor, evento onInitial) {
	sensor->onInitial = onInitial;
}
void sensor_onFinish(Sensor * sensor, evento onFinish) {
	sensor->onFinish = onFinish;
}

void cambiarEstado(Sensor * sensor, SensorEstado estado) {
	sensor->state = estado;
}
void iniciarContadorDelay(Sensor * sensor) {
	delayInit(&sensor->delay,100);
}
void iniciarTiempo(Sensor * s) {
	Pulsera * pulsera = (Pulsera *) s->model;
	delayInit(&pulsera->timeInit, 5);
}


void actualizarSensor(Sensor * sensor) {
//	bool_t estadoInicial
	int8_t status;
	status = mpu9250Init( addrs );
//	sensor->addrs;
	mpu9250Read();
//	tick_t tickActual = tickRead();
//	tick_t tiempoPasado = tickActual - sensor->timeLast;

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
		case Levantado_: {
			if (sensor->sensibilidad < intervaloEvaluacionX
				|| sensor->sensibilidad < intervaloEvaluacionX
				|| sensor->sensibilidad < intervaloEvaluacionX) {

				cambiarEstado(sensor, Movimiento_);
//				iniciarTiempo(sensor);
				iniciarContadorDelay(sensor);

				sensor->ultimaLecturaX = lecturaActualX;
				sensor->ultimaLecturaY = lecturaActualY;
				sensor->ultimaLecturaZ = lecturaActualZ;

			} else {
				cambiarEstado(sensor,Quieto_);
			}
			break;
		}

	case Movimiento_: {
		if (delayRead(&sensor->delay)) {
			if (sensor->sensibilidad < intervaloEvaluacionX
					|| sensor->sensibilidad < intervaloEvaluacionX
					|| sensor->sensibilidad < intervaloEvaluacionX) {
				cambiarEstado(sensor,Levantado_);
//				iniciarTiempo(sensor);
				iniciarContadorDelay(sensor);
				printf("Acelerometro:   (%f, %f, %f)   [m/s2]\r\n",
						lecturaActualX, lecturaActualY,
						lecturaActualZ);
//				sensor->ultimaLecturaX = lecturaActualX;
//				sensor->ultimaLecturaY = lecturaActualY;
//				sensor->ultimaLecturaZ = lecturaActualZ;
//				sensor->onInitial(sensor->model);


			} else {
					cambiarEstado(sensor, Quieto_);
//		            iniciarTiempo(sensor);
					iniciarContadorDelay(sensor);
//					sensor->ultimaLecturaX = lecturaActualX;
//					sensor->ultimaLecturaY = lecturaActualY;
//					sensor->ultimaLecturaZ = lecturaActualZ;

				}
				break;
			}


	case Quieto_: {
		if (delayRead(&sensor->delay)) {
			if (sensor->sensibilidad > intervaloEvaluacionX
					|| sensor->sensibilidad > intervaloEvaluacionY
					|| sensor->sensibilidad > intervaloEvaluacionZ) {
				cambiarEstado(sensor, Levantado_);
//				iniciarTiempo(sensor);
				iniciarContadorDelay(sensor);
				sensor->onFinish(sensor->model);
				printf("estoy quieto... lecturaActualX %f  , últimaLecturaX: %f,intervaloEvaluacionX%f \n",
                  lecturaActualX, sensor->ultimaLecturaX,intervaloEvaluacionX);
		}
		}
		else {
			cambiarEstado(sensor, Movimiento_);
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


