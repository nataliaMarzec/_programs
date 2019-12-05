/*
 * BluetoothConnector.h
 *
 *  Created on: Sep 22, 2019
 *      Author: leo
 */

#ifndef PROGRAMS_BTEXAMPLE_INC_UARTCONNECTOR_H_
#define PROGRAMS_BTEXAMPLE_INC_UARTCONNECTOR_H_

#include <sapi.h>

typedef void (*ByteReadedEventHandler)(void * model, uint8_t byte);

typedef struct {
	uartMap_t map;
	void * model;
	ByteReadedEventHandler byteReadedEventHandler;
	unsigned int maxBytesReadedPerCycle;
	char * endOfPackage;
} UartConnector;

void uartConnector_initBt(UartConnector * uartConnector, void * model, ByteReadedEventHandler byteReadedEventHandler);

void uartConnector_init(UartConnector * uartConnector, uartMap_t map,
		void * model, ByteReadedEventHandler byteReadedEventHandler,
		unsigned int baudRate, unsigned int maxBytesReadedPerCycle,
		char * endOfPackage);

void uartConnector_update(UartConnector * uartConnector);
void uartConnector_send(UartConnector * uartConnector, char * string);

#endif /* PROGRAMS_BTEXAMPLE_INC_UARTCONNECTOR_H_ */
