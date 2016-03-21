/* 
 * File:   cliente.h
 * Author: ellioth
 *
 * Created on March 4, 2016, 9:56 AM
 */

#ifndef CLIENTE_H
#define	CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <iostream>
#include "Constantes.h"


using namespace std;
/**
 * clase de cliente que va a ser la que vamos a usar con la gui 
 * para conectarnos a la logica
 */
class cliente : public Constantes{
public:
    cliente(int pPort, char* pIp);
    virtual ~cliente();
    void sendMsg(string dato);
    string getMensaje();
private:
    int _port, _sockfd, _n;
    struct sockaddr_in _serv_addr;
    struct hostent * _server;
    string _mensaje;
    char* _IP;
    pthread_t _hilo;
    pthread_mutex_t _lock;
    void ConnectToServer();
    void* ReciverLoop(void );
    static void * StaticReciver(void* data){
        return ((cliente*)data)->ReciverLoop();
    };
    void error(const char* mensaje);
};

#endif	/* CLIENTE_H */

