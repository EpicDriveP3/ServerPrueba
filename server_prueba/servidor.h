/* 
 * File:   servidor.h
 * Author: ellioth
 *
 * Created on February 12, 2016, 2:26 PM
 */

#ifndef SERVER_H
#define	SERVER_H
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <iostream>
#include <strings.h>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

/**
 * clase servidor, esta clase la vamos a usar para eviar y recibir 
 * datos contra los clientes conectados.
 */
class servidor{
    
public:
    servidor(int port);
    virtual ~servidor();
private:
    int counter;
    //datos propios de la instanciacion del servidor
    int _sockfd, _newsockfd, _portno, _n, _codigos;
    socklen_t _clilen;
    char* _id;
    struct sockaddr_in _serv_addr, _cli_addr;
    void* ServerLoop(void);
    void* gettDatas(int plyr, int newsockfd);
    void error(const char* msg);
};

#endif	/* SERVER_H */

