/*
 * Main.c
 *
 *  Created on: 14 sep. 2019
 *      Author: natim
 */
#include <sapi.h>
#include "controlador.h"


int main(void){
//inicializar la placa:
boardConfig();

controladorsemaforo cs;
controladorsemaforo_inicializar(&cs);

 while(1){
 controladorsemaforo_update(&cs);
 controladorsemaforo_render(&cs);

 delay(1000);
 }
 return 0;

}


