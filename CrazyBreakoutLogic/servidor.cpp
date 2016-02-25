/* 
 * File:   servidor.cpp
 * Author: ellioth
 * 
 * Created on February 12, 2016, 2:26 PM
 */

#include "servidor.h"

servidor::servidor(int port) {
    _portno= port;
    _sockfd = socket(AF_INET, SOCK_STREAM, cero);
    //resivision de si la conexion del socket 
    // fue positiva o fallida.
    if (_sockfd <cero)
        error(error1);
    //se escibe 0s en la variables puesta.
    //esto garantiza que no se use memoria sucia.
    bzero((char *) &_serv_addr, sizeof(_serv_addr));
    //establecemos los datos que se van a utilizar 
    //en el socket.
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_addr.s_addr = INADDR_ANY;
    _serv_addr.sin_port = htons(_portno);
    if (bind(_sockfd, (struct sockaddr *) &_serv_addr, sizeof(_serv_addr))<cero)
        error(error2);
    //se pone a escuchar en el socket si hay nuevas conexiones.
    listen(_sockfd,cinco);
    _clilen = sizeof(_cli_addr);
    _Tplayrs=0;
    while(true){
        _newsockfd = accept(_sockfd, (struct sockaddr*) &_cli_addr, &_clilen);
        if (_newsockfd < cero)
            error(error3);
        if(_Tplayrs==cero)
            _ToScreen=_newsockfd;
        int pid= fork();
        if(pid<cero)
            error(error4);
        if (pid == cero){
            close(_sockfd);
            gettDatas(_Tplayrs,_newsockfd);
            _Tplayrs++;
            exit(cero);
         }
        if(debug)
            printf("servidor: got connection from %s port %d\n",
                    inet_ntoa(_cli_addr.sin_addr), ntohs(_cli_addr.sin_port));
        else close(_newsockfd);
    }
    close(_sockfd);
}

servidor::~servidor() {
}

void servidor::error(const char* msg) {
    perror(msg);
    exit(uno);
}

void servidor::gettDatas(int pPlyr, int newsockfd) {
    void* almacenador= malloc(sizeof(LengMSG));
    while(true){
        while(!_Boolplyrs[pPlyr]){
            bzero(almacenador, sizeof(LengMSG));
            _n = read(newsockfd,almacenador,sizeof(LengMSG));
            if (_n < cero)
                error(error6);
            _Boolplyrs[pPlyr]=true;
            _plyMSG[pPlyr]=(char*)almacenador;
        }
    }
}

bool servidor::sendMSG(const char* msg, int lenght) {
    _n=write(_ToScreen, msg, lenght);
    if (_n < cero) 
        error(error5);
    if(debug)
        cout<<"mensaje enviado"<<endl;
}

bool servidor::getBoolPlyrs(int plyr) {
    return _Boolplyrs[plyr];
}

string servidor::getMSGPlyrs(int plyr) {
    return _plyMSG[plyr];
}

int servidor::getTplyrs() {
    return _Tplayrs;
}
