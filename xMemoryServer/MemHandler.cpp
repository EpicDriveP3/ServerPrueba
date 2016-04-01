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
MemHandler::MemHandler(int port, char* DiskLocation) {
    _servidor= new servidor(port);
    _chuckMemory=malloc(SPACE_MEMORY);
    _writerMemoryPointer=_chuckMemory;
    _diskLocation=DiskLocation;
    _listaDatosAlmacenados= new lista();
}

/**
 * destructor de la clase, se encarga de liberar toda la memoria 
 * que estabamos usando.
 */
MemHandler::~MemHandler() {
    free(_chuckMemory);
    _writerMemoryPointer=NULL;
    delete []_diskLocation;
    delete _listaDatosAlmacenados;
    delete _servidor;
}

/**
 * metodo usado para establecer el ciclo que infinito que se 
 * ejecutara por si solo y estara revizando para pedidos del cliente
 * y cuando el cliente envie algo, vamos a agarrar el mensaje,
 * parsearlo e indetificar lo que se ocupa para luego devolver lo
 * que se a pedido.
 */
void MemHandler::LoopForService() {
    //obtenemos el mensaje.
    char* IncommingMessage= _servidor->listenMsg();
    //string para obtener el largo de caracteres de la cadena.
    string getMsgDatas= IncommingMessage;
    /*opcion por si ya no nos queda espacio en memoria, 
     en ese caso pasamos todo a disco y verificamos que aun nos quede 
     espacio en disco*/
    if(getMsgDatas.length()>=_MemoryLeft && _DiskLeft<SPACE_MEMORY){
        PassToDisk();
    }
    
    /****************************************************************/
    /*---------aqui hay que meterle la vara del rapidJson-----------*/
    /*----------y encolar los datos a la lista como datos-----------*/
    /*--------------------que estan en memoria----------------------*/
    /****************************************************************/
    
    /*ciclo para escribir sobre la memoria, mientras esta aun le quede
    espacio*/
    for(int i=0; i<getMsgDatas.length(); i++,_MemoryLeft--){
        //movemos el puntero
        _writerMemoryPointer+=i;
        //escribimos en la memoria.
        *((char*)_writerMemoryPointer)=*(IncommingMessage+i);
    }
}

/**
 * metodo para pasar todos los datos de la memoria al disco.
 */
void MemHandler::PassToDisk() {
    fstream diskWriter(_diskLocation);
    if(diskWriter.is_open()){
        Nodo* temp=_listaDatosAlmacenados->getHead();
         void* PointerOfMemory;
        for(int i=0; i<_listaDatosAlmacenados->getSize(); i++){
            if(!temp->saveAtDisk()){
                //movmevos el puntero del archivo a la ultima posicion
                diskWriter.seekg(_DiskPointer);
                //obtenemos los datos del json que vamos a guardar
                int space=temp->getSpaceSave();
                int size=temp->getSizeSave();
                //obtenemos el puntero de la memoria
                PointerOfMemory=(_chuckMemory+space);
                //escribimos en disco
                diskWriter.write((char*)PointerOfMemory,size);
                //alteramos los datos internos del nodo.
                temp->setSaveDisk();
                temp->setSpaceSave(_DiskPointer);
                //movemos el puntero del disco
                _DiskPointer+=size;
                _DiskLeft-=size;
            }
            temp= temp->getNext();
        }
        //cerramos el archivo
        diskWriter.close();
    }
    //limpiamos la memoria
    bzero(_chuckMemory,DOSCIENTOS_CINCUENTA_Y_SEIS);
}
