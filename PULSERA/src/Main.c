
#include "Pulsador.h"
#include "Pulsera1.h"
#include "PulseraRender1.h"
#include "Sensor1.h"
#include "sapi.h"

MPU9250_address_t addr = MPU9250_ADDRESS_0; // If MPU9250 AD0 pin is connected to GND

void pulsera_enReposo(void * p){
}
void pulsera_teMoviste(void *p){
	Pulsera1 * model=(Pulsera1 *) p;
	pulseraEnMovimiento(p);
}

int main(void){
   boardConfig();
   gpioInit(GPIO0, GPIO_OUTPUT);// @suppress("Symbol is not resolved")


   Pulsera1 p;
   Sensor1 s;
   PulseraRender1 pRender;
   Pulsador pul;

   printf("INICIALIZANDO BOTON");
   inicializarDatosPulsadorDeArranque(&pul,TEC2,(void*)&p); // @suppress("Symbol is not resolved")
   pulsador_onPress(&pul,pulsera_teMoviste);
   pulsador_onRelease(&pul,pulsera_enReposo);

   printf("INICIALIAZANDO PULSERA");
   PulseraInit(&p,EN_MOVIMIENTO);//DETENIDO
   renderizar(&pRender,&p,GPIO0); // @suppress("Symbol is not resolved")

   printf("Inicializando IMU MPU9250...\r\n" );
   int8_t status;
   status = mpu9250Init( addr );

   printf("INICIALIAZANDO SENSOR");
   iniciarSensorMPU9250(&s,&p,status);
   sensor_onInitial(&s,pulsera_teMoviste);
   sensor_onFinish(&s,pulsera_enReposo);

   if( status < 0 ){
      printf( "IMU MPU9250 no inicializado, chequee las conexiones:\r\n\r\n" );
      printf( "MPU9250 ---- EDU-CIAA-NXP\r\n\r\n" );
      printf( "    VCC ---- 3.3V\r\n" );
      printf( "    GND ---- GND\r\n" );
      printf( "    SCL ---- SCL\r\n" );
      printf( "    SDA ---- SDA\r\n" );
      printf( "    AD0 ---- GND\r\n\r\n" );
      printf( "Se detiene el programa.\r\n" );
      while(1);
   }
   printf("IMU MPU9250 inicializado correctamente.\r\n\r\n" );


   while(TRUE){

      mpu9250Read();
//		printf( "Acelerometro:   (%f, %f, %f)   [m/s2]\r\n",
//              mpu9250GetAccelX_mss(),
//              mpu9250GetAccelY_mss(),
//              mpu9250GetAccelZ_mss()
//            );
		actualizarPulsador(&pul);
		actualizarSensor(&s);
		pulseraUpdate(&p);
	    update(&pRender);

      delay(1000);
   }


   return 0 ;
}


