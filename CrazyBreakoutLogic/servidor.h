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
#include "Constantes.h"

using namespace std;

/**
 * clase servidor, esta clase la vamos a usar para eviar y recibir 
 * datos contra los clientes conectados.
 */
class servidor: public Constantes {
    
public:
    servidor(int port);
    virtual ~servidor();
    void sendMSG(const char* msg, int lenght);
    bool getBoolPlyrs(int plyr);
    void setBoolPlyrs(int plyr);
    string getMSGPlyrs(int plyr);
    int getTplyrs();
private:
    //bloqueo mutex
    pthread_mutex_t _lock;
    //hilo para el listener
    pthread_t _hiloServer;
    int counter;
    //datos propios de la instanciacion del servidor
    int _sockfd, _newsockfd, _portno, _n, _codigos;
    socklen_t _clilen;
    char* _id;
    struct sockaddr_in _serv_addr, _cli_addr;
    //datos para hacer el observer
    bool _Boolplyrs[MaxPlyrs];
    char* _plyMSG[MaxPlyrs];
    //_ToScreen es el sockfd que sera el cliente al cual se le envia
    //la imagen.
    int _ToScreen, _Tplayrs;
    void* ServerLoop(void);
    void gettDatas(int plyr, int newsockfd);
    void error(const char* msg);
    /**
     * metodo estatico que permite acceder al metodo que incializa el
     * ciclo que arranca el listener del server.
     * @param data recibe un this de la clase
     * @return retorna el acceso al ciclo de la clase.
     */
    static void * ServerLoopHelper(void* data){
      return ((servidor*)data)->ServerLoop();  
    };
};

#endif	/* SERVER_H */

