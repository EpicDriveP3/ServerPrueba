/* 
 * File:   cliente.cpp
 * Author: ellioth
 * 
 * Created on March 4, 2016, 9:56 AM
 */

#include "cliente.h"

/**
 * constructor que recibe dos datos, el puerto y el ip 
 * para realizar la conexion contra el servidor.
 * @param pPort dato tipo entero, es el puerto.
 * @param pIp dato tipo char*, es una cadena de caracteres
 * que es el ip a donde nos conectamos.
 */
cliente::cliente(int pPort, char* pIp) {
    _port=pPort;
    _IP=pIp;
    ConnectToServer();
    if(pthread_mutex_init(&_lock,NULL)!=cero)
        error("mutex falied at create");
    if(pthread_create(&_hilo,NULL,&cliente::StaticReciver,this)!=cero)
        error("error al crear hilo: ");
    //if(debug)cout<<"hilo creado"<<endl;
    
}

cliente::~cliente() {
    delete _IP;
    delete _server;
}

/**
 * metodo para realizar la conexion contra el servidor
 */
void cliente::ConnectToServer() {
    _sockfd = socket(AF_INET, SOCK_STREAM, cero);
    if (_sockfd < cero) 
        error(error1);
    _server = gethostbyname(_IP);
    if (_server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(cero);
    }
    bzero((char *) &_serv_addr, sizeof(_serv_addr));
    _serv_addr.sin_family = AF_INET;
    bcopy((char *)_server->h_addr, 
        (char *)&_serv_addr.sin_addr.s_addr,
        _server->h_length);
    _serv_addr.sin_port = htons(_port);
    if (connect(_sockfd,(struct sockaddr *) &_serv_addr,sizeof(_serv_addr))<
            cero) 
        error(error4);
}

/**
 * metodo que es privado, este metodo solo es ejecutado
 * por el hilo que va a escuchar los mensajes en formato
 * Json que le llegan desde el servidor.
 * @return no retorna nada, es usado para hacer que funcione
 * el hilo de pthread.
 */
void* cliente::ReciverLoop(void) {
    void* almacenador= malloc(DosCincoSeis);
    while(true){
        bzero(almacenador,DosCincoSeis);
        _n = recv(_sockfd,almacenador,DosCincoSeis-uno,0);
        if (_n < cero) 
            error(error6);
        pthread_mutex_lock(&_lock);
        _mensaje=(char*)almacenador;
        pthread_mutex_unlock(&_lock);
    }
    close(_sockfd);
}

/**
 * metodo para enviarle un mensaje al server.
 * @param dato recibe un dato tipo string, o una 
 * cadena de caracteres que es el mensaje que queremos
 * enviarle **--advertencia: solo recibe datos de peso de un byte--**
 */
void cliente::sendMsg(string dato) {
    char* msg= new char[dato.length()+uno];
    strcpy(msg, dato.c_str());
    msg[dato.length()]='\0';
    _n= send(_sockfd,msg,dato.length(),0);
    if(_n<cero)
        error(error5);
    
}

/**
 * metodo protegido con mutex para acceder al mensaje
 * que acaba de recibir por parte del servidor.
 * @return retorna un dato tipo string que es el mensaje
 * en formato Json que contiene los cambios realizados.
 */
string cliente::getMensaje() {
    pthread_mutex_lock(&_lock);
    string temp= _mensaje;
    pthread_mutex_unlock(&_lock);
    return temp;
}

/**
 * metodo aletar un error que surgio y bota todo el programa.
 * @param mensaje
 */
void cliente::error(const char* mensaje) {
    perror(mensaje);
    exit(0);
}
