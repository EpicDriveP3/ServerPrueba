/* 
 * File:   MemHandler.cpp
 * Author: ellioth
 * 
 * Created on March 22, 2016, 9:10 PM
 */

#include "MemHandler.h"

/**
 * construtor de la clase, recibe un dato, que es el puerto 
 * por donde instancearemos el server.
 * @param port dato tipo entero, es el puerto donde crearemos
 * el server.
 */
MemHandler::MemHandler(int port) {
    _servidor= new servidor(port);
    _chuckMemory=malloc(SPACE_MEMORY);
    _diskLocation=(char*)DISK_LOCATION;
    _listaDatosAlmacenados= new lista();
}

MemHandler::~MemHandler() {
    
}

/**
 * metodo usado para establecer el ciclo que infinito que se 
 * ejecutara por si solo y estara revizando para pedidos del cliente
 * y cuando el cliente envie algo, vamos a agarrar el mensaje,
 * parsearlo e indetificar lo que se ocupa para luego devolver lo
 * que se a pedido.
 */
void MemHandler::LoopForService() {

}
