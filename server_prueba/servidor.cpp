/* 
 * File:   servidor.cpp
 * Author: ellioth
 * 
 * Created on February 12, 2016, 2:26 PM
 */

#include <string.h>

#include "servidor.h"

/**
 * contructor de la clase que recibe un puerto para establecerlo
 * @param port es un dato tipo entero este es el puerto que usaremos
 * en el servidor.
 */
servidor::servidor(int port) {
    _portno= port;
    ServerLoop();
}

servidor::~servidor() {
    
}

/**
 * metodo que realiza el ciclo para escuchar a los clientes
 * que se quieren conectar.
 * @return no retorna nada, ese retorno se usa para la creacion 
 * de los pthread.
 */
void* servidor::ServerLoop() {
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //resivision de si la conexion del socket 
    // fue positiva o fallida.
    if (_sockfd <0)
        error("Error en apertura de socket");
    //se escibe 0s en la variables puesta.
    //esto garantiza que no se use memoria sucia.
    bzero((char *) &_serv_addr, sizeof(_serv_addr));
    //establecemos los datos que se van a utilizar 
    //en el socket.
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_addr.s_addr = INADDR_ANY;
    _serv_addr.sin_port = htons(_portno);
    if (bind(_sockfd, (struct sockaddr *) &_serv_addr, sizeof(_serv_addr))<0)
        error("Error en conexion de socket");
    //se pone a escuchar en el socket si hay nuevas conexiones.
    listen(_sockfd,5);
    _clilen = sizeof(_cli_addr);
    while(true){
        _newsockfd = accept(_sockfd, (struct sockaddr*) &_cli_addr, &_clilen);
        if (_newsockfd < 0)
            error("error en conexion con nuevo cliente");
        gettDatas(0,_newsockfd);
        printf("servidor: got connection from %s port %d\n",
                inet_ntoa(_cli_addr.sin_addr), ntohs(_cli_addr.sin_port));
    }
    close(_newsockfd);
    close(_sockfd);
}

/**
 * metodo para botar todo el programa si existe algun fallo y 
 * evitar errores futuros.
 * @param msg dato char* que es el mensaje que corresponde a error 
 * probocado.
 */
void servidor::error(const char* msg) {
    perror(msg);
    exit(1);
}

/**
 * ciclo por cliente que escucha los datos recibidos por el cliente, ya tiene
 * el mutex.
 * @param pPlyr dato tipo entero que es el numero del cliente.
 * @param newsockfd dato entero que es el socket del cliente con el que
 * nos comunicamos.
 */
void* servidor::gettDatas(int pPlyr, int newsockfd) {
    void* almacenador= malloc(100);
    while(true){
        bzero(almacenador, 100);
        _n = recv(newsockfd,almacenador,1,0);
        if (_n < 0)
            error("error de lectura en socket");
        cout<<(char*)almacenador<<endl;
        cout<<"ingrese un mensaje"<<endl;
        bzero(almacenador, 100);
        string temp;
        cin>>temp;
        strcpy((char*)almacenador,temp.c_str());
        _n = send(newsockfd,almacenador,1,0);
        if (_n < 0)
            error("error de escritura en socket");
    }
    free(almacenador);
}
