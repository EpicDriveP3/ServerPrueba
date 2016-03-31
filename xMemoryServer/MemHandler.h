/* 
 * File:   MemHandler.h
 * Author: ellioth
 *
 * Created on March 22, 2016, 9:10 PM
 */

#ifndef MEMHANDLER_H
#define	MEMHANDLER_H
#include "Constantes.h"
#include "Lista.h"
#include "Nodo.h"
#include "servidor.h"
#include <string>
#include <fstream>

class MemHandler :public Constantes {
public:
    MemHandler(int port, char* DiskLocation);
    virtual ~MemHandler();
    void LoopForService();
private:
    servidor * _servidor;
    lista * _listaDatosAlmacenados;
    void* _chuckMemory;
    void* _writerMemoryPointer;
    char* _diskLocation;
    int _MemoryLeft;
    int _DiskPointer;
    void PassToDisk();
};

#endif	/* MEMHANDLER_H */

