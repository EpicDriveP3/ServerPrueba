/* 
 * File:   MemHandler.cpp
 * Author: ellioth
 * 
 * Created on March 22, 2016, 9:10 PM
 */

#include <string.h>

#include "MemHandler.h"

/**
 * construtor de la clase, recibe un dato, que es el puerto 
 * por donde instancearemos el server.
 * @param port dato tipo entero, es el puerto donde crearemos
 * el server.
 */
MemHandler::MemHandler(int port, char* DiskLocation) {
    _servidor= new servidor(port);
    _chuckMemory=malloc(SPACE_MEMORY);
    _writerMemoryPointer=_chuckMemory;
    _diskLocation=DiskLocation;
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
    char* IncommingMessage= _servidor->listenMsg();
    string getMsgDatas= IncommingMessage;
    if(getMsgDatas.length()>=_MemoryLeft){
        //pasamos toda los datos a disco.
    }
}

void MemHandler::PassToDisk() {
    fstream diskWriter(_diskLocation);
    if(diskWriter.is_open()){
        Nodo* temp=_listaDatosAlmacenados->getHead();
        for(int i=0; i<_listaDatosAlmacenados->getSize(); i++){
            if(!temp->saveAtDisk()){
                //movmevos el puntero del archivo a la ultima posicion
                diskWriter.seekg(_DiskPointer);
                //obtenemos los datos del json que vamos a guardar
                int space=temp->getSpaceSave();
                int size=temp->getSizeSave();
                //obtenemos el puntero de la memoria
                void* PointerOfMemory=(_chuckMemory+space);
                //escribimos en disco
                diskWriter.write((char*)PointerOfMemory,size);
                //alteramos los datos internos del nodo.
                temp->setSaveDisk();
                temp->setSpaceSave(_DiskPointer);
                //movemos el puntero del disco
                _DiskPointer+=size;
            }
            temp= temp->getNext();
        }
        //cerramos el archivo
        diskWriter.close();
    }
    //limpiamos la memoria
    bzero(_chuckMemory,DOSCIENTOS_CINCUENTA_Y_SEIS);
}
