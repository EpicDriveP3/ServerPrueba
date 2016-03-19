/* 
 * File:   controlador.cpp
 * Author: ellioth
 * 
 * Created on February 12, 2016, 3:50 PM
 */

#include "controlador.h"

controlador::controlador(int Pport) {
    srand(time(NULL));
    _port=Pport;
    //arrancar server
    _servidor= new servidor(_port);
    //inicializar pelota
    _pelota[cero]= new Bola(ScreenX/dos-BallSize,PosYPLY-(BallSize+cinco));
    _BallsLeft++;
    /*--bloque para establecer el movimiento de la pelota sobre el campo---*/
    _dirrection=(rand()%tres);
    if(_dirrection==uno)
        _MoveBallX=-uno;
    else if(_dirrection==dos)
        _MoveBallX=cero;
    else if(_dirrection==tres)
        _MoveBallX=uno;
    _MoveBallY=-uno;
    /*---------------------------------------------------------------------*/
    //incializacion de los bloques
    _BarrsLeft=TotalBricks;
    int space=cero;
    for(int j =cero; j<RowBrick; j++)
        for(int i=cero; i<ColBrick;i++,space++){
            int fuerza= (rand()%tres)+uno;
            _barras[space]=new BarraDes(j*BrrSize,(i*BrrSize)+(cincuenta),
                    fuerza);
        }
    //entramos al hilo principal
    if(debug)cout<<"juego iniciado"<<endl;
    MainLoop();
    if(debug)cout<<"juego terminado"<<endl;
}

controlador::~controlador() {
    delete [] _barras;
    delete [] _pelota;
    delete [] _ply;
}

/**
 * ciclo principal para revizar todo.
 */
void controlador::MainLoop(){
    while(true){
        if(_servidor->getTplyrs()>cero){
            for(int i=cero; i<_servidor->getTplyrs(); i++){
                //verificamos si los players son nulos para crearlos 
                if(_ply[i]==NULL)
                    _ply[i]= new BarraPLY(i);
                //obtenemos sus cambios y nos movemos por la pantalla.
                if(_servidor->getBoolPlyrs(i)){
                    _ply[i]->move(_servidor->getMSGPlyrs(i));
                    _servidor->setBoolPlyrs(i);
                }
            }
            //revisamos las coliciones
            checkColl();
            string msg;
            //revisamos de primero la condicion de terminacion.
            if(_BallsLeft==cero || _BarrsLeft==cero){
                msg=_Json->create(NULL, _ply, NULL,_BallsLeft,
                        _servidor->getTplyrs(),-dos);
                _servidor->sendMSG(msg.c_str(),msg.length());
                break;
            }
            else if(_BarrsHit==-uno){
                msg=_Json->create(_pelota, _ply, NULL,_BallsLeft,
                        _servidor->getTplyrs(),_BarrsHit);
            }
            //en caso de que no seguimos normalmente
            else{
                msg=_Json->create(_pelota, _ply, _barras[_BarrsHit],
                    _BallsLeft,_servidor->getTplyrs(),_BarrsHit);
            }
            _servidor->sendMSG(msg.c_str(),msg.length());
            sleep(sleepTime);
        }   
    }
}

/**
 * metodo para ir revizando las coliciones de la pelota contra 
 * los objetos en campo.
 */
void controlador::checkColl() {
    _BarrsHit=-uno;bool bandera= false;
    //bloque para verificar choques con limites de pantalla
    if(_pelota[cero]->getPx()+BallSize==ScreenX)
        _MoveBallX=-uno;
    else if(_pelota[cero]->getPx()==cero)
        _MoveBallX=uno;
    if(_pelota[cero]->getPy()==cero)
        _MoveBallY=uno;
    //verificacion para choque contra la paleta de cada jugador.
    
    for(int i =cero; i<_servidor->getTplyrs(); i++)
        checkCollPly(i,&_MoveBallX,&_MoveBallY, &bandera);
    //verificaciones para colicion contra cada uno de los bloques.
    for(int i=cero; i<TotalBricks; i++){
        checkCollBrr(i, &_MoveBallX, &_MoveBallY, &bandera);
        if(bandera)
            break;
    }
    //verificacion por si la pelota se sale del alcance del jugador
    if(_pelota[cero]->getPy()>(PosYPLY+PlayrLengY)){
        _BallsLeft--;
        for(int i=cero; i<_servidor->getTplyrs(); i++)
            _ply[i]->resize(Decrement);
        if(_BallsLeft==cero){
            Bola * temp = _pelota[cero];
            _pelota[cero]= NULL;
            temp->~Bola();
            return;
        }
    }
    //movemos la pelota segun con los datos que hayamos cambiado.
    //solo se ejecuta la primera vez
    _pelota[cero]->move(_MoveBallX,_MoveBallY);
}

/**
 * metodo para revizar una colicion contra un jugador
 * @param plyr dato tipo entero que es el numero de cliente contra el 
 * cual estamos revizando.
 * @param x dato tipo puntero entero que es el X de la bola que va 
 * a cambiar segun se reporte un choque contra este.
 * @param y dato tipo puntero entero que es el Y de la bola que va 
 * a cambiar segun se reporte un choque contra este.
 */
void controlador::checkCollPly(int plyr, int * x, int * y, bool *bandera) {
    //colision con sector uno de la barra
    if(_pelota[cero]->getPy()+BallSize==PosYPLY && 
            (_pelota[cero]->getPx()+BallSize)>=_ply[plyr]->getPosX() &&
            _pelota[cero]->getPx()<=(_ply[plyr]->getPosX()+BarraLengXSector1)){
        (*x)=-uno;
        (*y)=-uno;
        (*bandera)=true;
    }
    //colision con sector dos de la barra
    else if(_pelota[cero]->getPy()+BallSize==PosYPLY && 
            _pelota[cero]->getPx()>=(_ply[plyr]->getPosX()+BarraLengXSector1) &&
            _pelota[cero]->getPx()<=(_ply[plyr]->getPosX()+BarraLengXSector2)){
        (*x)=cero;
        (*y)=cero;
        (*bandera)=true;
    }
    //colision con sector uno de la barra
    else if(_pelota[cero]->getPy()+BallSize==PosYPLY && 
            _pelota[cero]->getPx()>=(_ply[plyr]->getPosX()+BarraLengXSector2) &&
            _pelota[cero]->getPx()<=(_ply[plyr]->getPosX()+BarraLengXSector3)){
        (*x)=uno;
        (*y)=-uno;
        (*bandera)=true;
    }
}

/**
 * metodo para verificar coliciones contra barras
 * @param bar dato entero que es el espacio de la barra con la cual 
 * estamos revizando actualmente.
 * @param x dato tipo puntero entero que es el X de la bola que va 
 * a cambiar segun se reporte un choque contra este.
 * @param y dato tipo puntero entero que es el Y de la bola que va 
 * a cambiar segun se reporte un choque contra este.
 */
void controlador::checkCollBrr(int bar, int * x, int * y, bool * bandera) {
    //condicion por si revisamos contra una pelota que ya no existe.
    if(_barras[bar]==NULL)
        return;
    //choque de pelota en la parte inferior de la barra
    if(_pelota[cero]->getPy()==_barras[bar]->getPosY()&&
            (_pelota[cero]->getPx()+BallSize)>=_barras[bar]->getPosX()&&
            _pelota[cero]->getPx()<=(_barras[bar]->getPosX()+BrrSize)){
        (*y)=uno;
        *bandera=true;
    }
    //choque de pelota en la parte superior de la barra
    else if(_pelota[cero]->getPy()+BallSize==_barras[bar]->getPosY() &&
            (_pelota[cero]->getPx()+BallSize)>=_barras[bar]->getPosX() &&
            _pelota[cero]->getPx()<=(_barras[bar]->getPosX()+BrrSize)){
        (*y)=-uno;
        *bandera=true;
    }
    //choque de pelota en la parte izquierda de la barra
    else if((_pelota[cero]->getPx()+BallSize)==_barras[bar]->getPosX() &&
            (_pelota[cero]->getPy()+BallSize)>=_barras[bar]->getPosY() &&
            _pelota[cero]->getPy()<=(_barras[bar]->getPosY()+BrrSize)){
        (*x)=-uno;
        *bandera=true;
    }
    //choque de pelota en la parte derecha de la barra
    else if(_pelota[cero]->getPx()==(_barras[bar]->getPosX()+BrrSize) &&
            (_pelota[cero]->getPy()+BrrSize)>=_barras[bar]->getPosY() &&
            _pelota[cero]->getPy()<=(_barras[bar]->getPosY()+BrrSize)){
        (*x)=uno;
        *bandera=true;
    }
    /*verificacion para realizar una colicion y saber si se tieene que destruir
    el objeto*/
    if(*bandera){
        _BarrsHit=bar;
        _barras[bar]->impact();
        if(_barras[bar]->getHitLft()==cero){
            _BarrsLeft--;
            destroyObj(bar);
        }
    }
        
}

/**
 * funcion para destruir un objeto.
 * @param pBarNum
 */
void controlador::destroyObj(int pBarNum) {
    BarraDes * temp = _barras[pBarNum];
    _barras[pBarNum]=NULL;
    temp->~BarraDes();
}

/**
 * funcion para disminuir el tamaño de la barra,
 * todos los jugadores se ven afectados cuando se hace un resize.
 */
void controlador::resizeBar(int pTypeOP) {
    for(int i =0; i<_servidor->getTplyrs(); i++){
        _ply[i]->resize(pTypeOP);
    }
}