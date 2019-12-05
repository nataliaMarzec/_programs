/*
 * Main.c
 */
#include "sapi.h"
#include "Pulsera.h"
#include "Boton.h"
#include "Sensor.h"
#include "PulseraRender.h"
#include "UartConnector.h"
#define UART_PC        UART_USB
//#define UART_BLUETOOTH UART_232
//MPU9250_address_t addr = MPU9250_ADDRESS_0;
#define delay_t tickTime = 10

void pulsera_enReposo(void * p){
}
void pulsera_teMoviste(void *p){
	Pulsera * model=(Pulsera *) p;
	pulseraEnMovimiento(p);

}

int main(void){
 printf("Inicializando IMU MPU9250...\r\n");
 boardConfig();
 gpioInit(GPIO0, GPIO_OUTPUT);
// uartConfig(UART_USB, 115200);

 Pulsera p;
 Sensor s;
 PulseraRender pRender;
 Boton b;

 // UartConnector uart;
// pulsera_setObservador(&p, (void *)&uart, observerP);

 bool_t mpuRead;
 mpuRead = mpu9250Read();

  inicializarDatosBotonDeArranque(&b,TEC1,(void*)&p);
  boton_onPress(&b,pulsera_teMoviste);
//  boton_onRelease(&b,pulsera_enReposo);

  PulseraInit(&p,EN_MOVIMIENTO);//DETENIDO
  renderizar(&pRender,&p,GPIO0);

  iniciarSensorMPU9250(&s,&p);

//  sensor_onInitial(&s,pulsera_teMoviste);
//  sensor_onFinish(&s,pulsera_enReposo);

// uartConnector_initBt(&uartConnector, &app, datoBluetoohRecibido);

  while(TRUE){
	 printf("DENTRO DEL WHILE");
	 mpu9250Read();
	 actualizarBoton(&b);
//	 actualizarSensor(&s);
	 pulseraUpdate(&p);
	 update(&pRender);
	 printf( "Acelerometro:   (%f, %f, %f)   [m/s2]\r\n",
	                    mpu9250GetAccelX_mss(),
	                    mpu9250GetAccelY_mss(),
	                    mpu9250GetAccelZ_mss()
	                  );
	 delay(1);

	 //uartConnector_update(&uartConnector);
 }
 return 0;


}

//MPU9250_address_t addr = MPU9250_ADDRESS_0; // If MPU9250 AD0 pin is connected to GND

//void cambioDeEstado(void * observerP,Pulsera * pulsera,uint8_t b) {
//	UartConnector * u= (UartConnector *) observerP;
//	unsigned char valor=(pulsera->estado);
//    if(valor==EN_MOVIMIENTO){
//    uint8_t byte='h';
//    pulsera_press((Pulsera *)observerP);
//	uartConnector_send(u, "LED_ON");
//	}
//	else {
//    pulsera_release((Pulsera *)observerP);
//    uint8_t byte='l';
//    uartConnector_send(u, "LED_OFF");
//	}
//}
//
//void cambiarEstado(void * observerP,Pulsera * p) {
//	UartConnector * u= (UartConnector *) observerP;
//	unsigned char valor=(p->estado=EN_MOVIMIENTO)?'h':'l';
//	uartConnector_send(u,valor);
//}
//
//void actualizarValor(Pulsera * p){
//	setValor(p, !p->valor);
//}
//
//void setValor(Pulsera *p, unsigned char valor) {
//	p->valor = valor;
//	if(p->funcion != NULL) {
//		p->funcion(p->observerP,p);
//	}
//}
//
//EVENTOS:(SE USAN EN BLUETOOH Y EN UPDATEPULSERA)

