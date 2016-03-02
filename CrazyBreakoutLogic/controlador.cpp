/* 
 * File:   controlador.cpp
 * Author: ellioth
 * 
 * Created on February 12, 2016, 3:50 PM
 */

#include "controlador.h"

controlador::controlador(int Pport) {
    _port=Pport;
    _servidor= new servidor(_port);
    _pelota[cero]= new Bola(ScreenX/dos-BallSize,PosYPLY-(BallSize+dos));
    int space=cero;
    for(int i =cero; i<ColBrick; i++)
        for(int j=cero; j<RowBrick;j++,space++)
            _barras[space]=new BarraDes(j*BrrSize,(i*BrrSize)+(cincuenta),
                    j+uno);
    MainLoop();
}

controlador::~controlador() {
    delete [] _barras;
    delete [] _pelota;
    delete [] _ply;
}

/**
 * ciclo principal para revizar todo.
 */
void controlador::MainLoop() {
    while(true){
        while(_servidor->getTplyrs()>cero){
            for(int i=cero; i<MaxPlyrs; i++){
                if(_servidor->getBoolPlyrs(i)){
                    _ply[i]->move(stoi(_servidor->getMSGPlyrs(i)));
                    _servidor->setBoolPlyrs(i);
                }
            }
            checkColl();
            string msg=_Json->create(_pelota, _ply, _barras[_BarrsHit],
                    _BallsLeft,_Tplys,_BarrsHit);
            _servidor->sendMSG(msg.c_str(),msg.length());
        }
    }
}

/**
 * metodo para ir revizando las coliciones de la pelota contra 
 * los objetos en campo.
 */
void controlador::checkColl() {
    int x,y;
    //bloque para verificar choques con limites de pantalla
    if(_pelota[cero]->getPx()==ScreenX)
        x=-1;
    else if(_pelota[cero]->getPx()==cero)
        x=-1;
    if(_pelota[cero]->getPy()==ScreenY)
        y=-1;
    else if(_pelota[cero]->getPy()==cero)
        y=-1;
    //verificacion para choque contra la paleta de cada jugador.
    for(int i =0; i<_Tplys; i++)
        checkCollPly(i,&x,&y);
    //verificaciones para colicion contra cada uno de los bloques.
    for(int i=0; i<TotalBricks; i++)
        checkCollBrr(i, &x, &y);
    if(_pelota[cero]->getPy()>_ply[cero]->getPosY())
            _ply[cero]->resize(Decrement);
    //movemos la pelota segun con los datos que hayamos cambiado.
    _pelota[cero]->move(x,y);
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
void controlador::checkCollPly(int plyr, int * x, int * y) {
    if(_pelota[cero]->getPy()+BallSize==PosYPLY &&
            _ply[plyr]->getPosX()<=_pelota[cero]->getPx()&&
            (_ply[plyr]->getPosX()+PlayrLenght)>=_pelota[cero]->getPx())
        (*y)=-1;
    if(_pelota[cero]->getPy()+BallSize==PosYPLY && 
            _pelota[cero]->getPx()>=_ply[plyr]->getPosX() &&
            _pelota[cero]->getPx()<=(_ply[plyr]->getPosX()+BarraLengXSector1))
        (*x)=-1;
    else if(_pelota[cero]->getPy()+BallSize==PosYPLY && 
            _pelota[cero]->getPx()>=(_ply[plyr]->getPosX()+BarraLengXSector1) &&
            _pelota[cero]->getPx()<=(_ply[plyr]->getPosX()+BarraLengXSector2))
        (*x)=0;
    else if(_pelota[cero]->getPy()+BallSize==PosYPLY && 
            _pelota[cero]->getPx()>=(_ply[plyr]->getPosX()+BarraLengXSector2) &&
            _pelota[cero]->getPx()<=(_ply[plyr]->getPosX()+BarraLengXSector3))
        (*x)=1;
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
void controlador::checkCollBrr(int bar, int * x, int * y) {
    if(_barras[bar]->getPosY()+BrrSize==_pelota[cero]->getPy()&&
            _barras[bar]->getPosX()<=_pelota[cero]->getPx() &&
            (_barras[bar]->getPosX()+BrrSize)<=_pelota[cero]->getPx()){
        (*y)=-1;
        _barras[bar]->impact();
        _barras[bar]->setFlag(true);
        _BarrsHit=bar;
    }
    else if(_barras[bar]->getPosY()==_pelota[cero]->getPy()+BallSize &&
            _barras[bar]->getPosX()<=_pelota[cero]->getPx() &&
            (_barras[bar]->getPosX()+BrrSize)<=_pelota[cero]->getPx()){
        (*y)=-1;
        _barras[bar]->impact();
        _barras[bar]->setFlag(true);
        _BarrsHit=bar;
    }
    else if(_barras[bar]->getPosX()==_pelota[cero]->getPx()+BallSize &&
            _barras[bar]->getPosY()<=_pelota[cero]->getPy()+BallSize &&
            (_barras[bar]->getPosY()+BrrSize)<=_pelota[cero]->getPy()
            +BallSize){
        (*x)=-1;
        _barras[bar]->impact();
        _barras[bar]->setFlag(true);
        _BarrsHit=bar;
    }
    else if(_barras[bar]->getPosX()+BrrSize==_pelota[cero]->getPx() &&
            _barras[bar]->getPosY()<=_pelota[cero]->getPy() &&
            (_barras[bar]->getPosY()+BrrSize)<=_pelota[cero]->getPy()){
        (*x)=-1;
        _barras[bar]->impact();
        _barras[bar]->setFlag(true);
        _BarrsHit=bar;
    }
    //verificacion para eliminar la barra que ya no le quedan vidas.
    if(_barras[bar]->getHitLft()==cero)
        destroyObj(bar);
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
    for(int i =0; i<_Tplys; i++){
        _ply[i]->resize(pTypeOP);
    }
}