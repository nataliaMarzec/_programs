/*
 * UartConnector.c
 */
//#include "UartConnector.h"
//
//void uartConnector_initBt(UartConnector * uartConnector, void * model, ByteReadedEventHandler byteReadedEventHandler) {
//	uartConnector_init(uartConnector, UART_232, model, byteReadedEventHandler,9600, 10, "\r\n");
//}
//
//void uartConnector_init(UartConnector * uartConnector, uartMap_t map,
//		void * model, ByteReadedEventHandler byteReadedEventHandler,
//		unsigned int baudRate, unsigned int maxBytesReadedPerCycle,
//		char * endOfPackage) {
//	uartConnector->map = map;
//	uartConnector->model = model;
//	uartConnector->byteReadedEventHandler = byteReadedEventHandler;
//	uartConnector->maxBytesReadedPerCycle = maxBytesReadedPerCycle;
//	uartConnector->endOfPackage = endOfPackage;
//	uartConfig(map, baudRate);
//}
//
//void uartConnector_update(UartConnector * uartConnector) {
//	int i = 0;
//	uint8_t byte;
//	while (i < uartConnector->maxBytesReadedPerCycle && uartReadByte(uartConnector->map, &byte)) {
//		uartConnector->byteReadedEventHandler(uartConnector->model, byte);
//		i++;
//	};
//}
//
//void uartConnector_send(UartConnector * uartConnector, char * string) {
//	uartWriteString(uartConnector->map, string);
//	uartWriteString(uartConnector->map, uartConnector->endOfPackage);
//}
//
