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
#include "Constantes.h"

using namespace std;
class servidor: public Constantes {
    
public:
    servidor(int port);
    virtual ~servidor();
    void sendMSG(const char* msg, int lenght);
    bool getBoolPlyrs(int plyr);
    void setBoolPlyrs(int plyr);
    string getMSGPlyrs(int plyr);
    int getTplyrs();
    void gettDatas(int plyr, int newsockfd);
private:
    int _sockfd, _newsockfd, _portno, _n, _codigos;
    socklen_t _clilen;
    char* _id;
    bool _Boolplyrs[MaxPlyrs];
    char* _plyMSG[MaxPlyrs];
    int _ToScreen, _Tplayrs;
    struct sockaddr_in _serv_addr, _cli_addr;
    void error(const char* msg);
    
};

#endif	/* SERVER_H */

