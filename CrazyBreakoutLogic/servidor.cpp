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
        
        //aqui vamos a poner el ciclo que va a abrir los hilos para 
        //los clientes
        /*--------------*/
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

/**
 * metodo para botar todo el programa si existe algun fallo y 
 * evitar errores futuros.
 * @param msg dato char* que es el mensaje que corresponde a error 
 * probocado.
 */
void servidor::error(const char* msg) {
    perror(msg);
    exit(uno);
}

/**
 * ciclo por cliente que escucha los datos recibidos por el cliente.
 * @param pPlyr dato tipo entero que es el numero del cliente.
 * @param newsockfd dato entero que es el socket del cliente con el que
 * nos comunicamos.
 */
void servidor::gettDatas(int pPlyr, int newsockfd) {
    void* almacenador= malloc(sizeof(LengMSG));
    while(true){
        while(!getBoolPlyrs(pPlyr)){
            
            bzero(almacenador, sizeof(LengMSG));
            _n = read(newsockfd,almacenador,sizeof(LengMSG));
            if (_n < cero)
                error(error6);
            _Boolplyrs[pPlyr]=true;
            _plyMSG[pPlyr]=(char*)almacenador;
        }
    }
}


/**
 * metodo para enviar los mensajes a la pantalla y alertar los cambios
 * @param msg dato tipo char* const, que es el mensaje que enviaremos.
 * @param lenght dato tipo entero, este es el largo del mensaje.
 */
void servidor::sendMSG(const char* msg, int lenght) {
    _n=write(_ToScreen, msg, LengMSG);
    if (_n < cero) 
        error(error5);
    if(debug)
        cout<<"mensaje enviado"<<endl;
}

/**
 * metodo para hacer el observer y darse cuenta si ya hay
 * un mensaje de parte del cliente.
 * @param plyr recibe un entero que es el numero del cliente.
 * @return retorna un dato tipo bool.
 */
bool servidor::getBoolPlyrs(int plyr) {
    return _Boolplyrs[plyr];
}

/**
 * metodo para establecer en falso el mensaje que recibimos del cliente 
 * y hacer que se pueda recibir un nuevo mensaje.
 * @param plyr dato tipo entero, este es el numero del jugador.
 */
void servidor::setBoolPlyrs(int plyr) {
    _Boolplyrs[plyr]=false;
}

/**
 * metodo para obtener el mensaje que envia el cliente.
 * @param plyr recibe un dato tipo entero que es el numero de cliente
 * @return retorna un dato tipo string que es el mensaje del cliente
 */
string servidor::getMSGPlyrs(int plyr) {
    return _plyMSG[plyr];
}

/**
 * metodo para conocer la cantidad total de jugadores conectados
 * actualmente.
 * @return dato entero.
 */
int servidor::getTplyrs() {
    return _Tplayrs;
}
