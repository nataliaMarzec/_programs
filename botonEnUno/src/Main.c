/*
 * Main.c
 *
 *  Created on: 4 oct. 2019
 *      Author: natim
 */


#include <sapi.h>
#include "../../botonEnUno/inc/AppModelRENDER.h"
#include "../../botonEnUno/inc/AppMODEL.h"
#include "../../botonEnUno/inc/Boton2.h"
#include "../inc/Sensor2.h"
//MPU9250_address_t addr = MPU9250_ADDRESS_0; // If MPU9250 AD0 pin si esta conectada con gnd

void handlerDelBoton(void * appModelPointer) {
	AppModel * appModel = (AppModel *)appModelPointer;
	appModel_toggle(appModel);
}
void handlerDelSensor(void * appModelPointer){
	AppModel * appModel = (AppModel *)appModelPointer;
	appModel_toggle(appModel);

}

int main( void )
{
   boardConfig();
   printf("Inicializando IMU MPU9250...\r\n" );

   Sensor sensor;
   Button button;
   AppModel appModel;
   AppModelRender appModelRender;
   UartConnector uartConnector;

   appModel_init(&appModel, 0);
   appModelSensor_init(&appModel,0);

   boton_init(&button, TEC1, (void *)&appModel);
   boton_onRelease(&button, handlerDelBoton);

   //   	int8_t status;
   //   	status = mpu9250Init( addr );
//   iniciarSensorMPU9250(&sensor,(void *)&appModel);
//   sensor_onFinish(&sensor,(void *), handlerDelSensor);

   appModelRender_init(&appModelRender, &appModel, LED1);
//   appModelRenderSensor_init(&appModelRender,&appModel,LED2);

   while( TRUE ) {
	   printf("HOLA WHILE!!!");
	   actualizarBoton(&button);
	   appModelRender_update(&appModelRender);

	   delay(1);

	   actualizarSensor(&sensor);
	   printf( "Sensor:   (%f, %f, %f)   [m/s2]\r\n",
			   150,120,250
//	  	                 mpu9250GetAccelX_mss(),
//	  	                 mpu9250GetAccelY_mss(),
//	  	                 mpu9250GetAccelZ_mss()
	  	               );
	   appModelRenderSensor_update(&appModelRender);

	   uartConnector_update(&uartConnector);
	   delay(1000);
   }

   return 0;
}



