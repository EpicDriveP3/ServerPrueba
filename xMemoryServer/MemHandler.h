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

class MemHandler :public Constantes {
public:
    MemHandler(int port);
    virtual ~MemHandler();
    void LoopForService();
private:
    servidor * _servidor;
    lista * _listaDatosAlmacenados;
    void* _chuckMemory;
    char* _diskLocation;
};

#endif	/* MEMHANDLER_H */

