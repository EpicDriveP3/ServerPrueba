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
    _pelota[cero]= new Bola(ScreenX/dos,PosYPLY-(BallSize+dos));
    for(int i =0; i<)
    MainLoop();
}

controlador::~controlador() {
    delete [] _barras;
    delete [] _pelota;
    delete [] _ply;
}

/**
 * ciclo principa para revizar todo.
 */
void controlador::MainLoop() {
    while(true){
        while(_servidor->_Tplayrs>cero){
            _Tplys=_servidor->_Tplayrs;
            for(int i=0; i<MaxPlyrs; i++){
                if(_servidor->_Boolplyrs[i]){
                    _ply[i]->move(atoi(_servidor->_plyMSG[i]));
                    _servidor->_Boolplyrs[i]=false;
                }
            }
            checkColl();
            string msg=_Json->create(_pelota, _ply, _barras,
                    _BallsLeft,_Tplys,_BarrsLeft);
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
    for(int i =0; i<_Tplys; i++){
        if(_pelota[cero]->getPy()+BallSize==PosYPLY &&
                _ply[i]->getPosX()<=_pelota[cero]->getPx()&&
                (_ply[i]->getPosX()+PlayrLenght)>=_pelota[cero]->getPx())
            y=-1;
        if(_pelota[cero]->getPy()+BallSize==PosYPLY && 
                _pelota[cero]->getPx()>=_ply[i]->getPosX() &&
                _pelota[cero]->getPx()<=(_ply[i]->getPosX()+BarraLengXSector1))
            x=-1;
        else if(_pelota[cero]->getPy()+BallSize==PosYPLY && 
                _pelota[cero]->getPx()>=(_ply[i]->getPosX()+BarraLengXSector1) &&
                _pelota[cero]->getPx()<=(_ply[i]->getPosX()+BarraLengXSector2))
            x=0;
        else if(_pelota[cero]->getPy()+BallSize==PosYPLY && 
                _pelota[cero]->getPx()>=(_ply[i]->getPosX()+BarraLengXSector2) &&
                _pelota[cero]->getPx()<=(_ply[i]->getPosX()+BarraLengXSector3))
            x=1;
    }
    
    //verificaciones para colicion contra cada uno de los bloques.
    for(int i=0; i<TotalBricks; i++){
        if(_barras[i]->getPosY()+BarraLengY==_pelota[cero]->getPy()&&
                _barras[i]->getPosX()<=_pelota[cero]->getPx() &&
                (_barras[i]->getPosX()+BarraLengXSector3)<=_pelota[cero]->getPx()){
            y=-1;
            _barras[i]->impact();
        }
        else if(_barras[i]->getPosY()==_pelota[cero]->getPy()+BallSize &&
                _barras[i]->getPosX()<=_pelota[cero]->getPx() &&
                (_barras[i]->getPosX()+BarraLengXSector3)<=_pelota[cero]->getPx()){
            y=-1;
            _barras[i]->impact();
        }
        else if(_barras[i]->getPosX()==_pelota[cero]->getPx()+BallSize &&
                _barras[i]->getPosY()<=_pelota[cero]->getPy()+BallSize &&
                (_barras[i]->getPosY()+BarraLengY)<=_pelota[cero]->getPy()
                +BallSize){
            x=-1;
            _barras[i]->impact();
        }
        else if(_barras[i]->getPosX()+BarraLengXSector3==_pelota[cero]->getPx() &&
                _barras[i]->getPosY()<=_pelota[cero]->getPy() &&
                (_barras[i]->getPosY()+BarraLengY)<=_pelota[cero]->getPy()){
            x=-1;
            _barras[i]->impact();
        }
        //verificacion para eliminar la barra que ya no le quedan vidas.
        if(_barras[i]->getHitLft()==cero)
            destroyObj(i);
    }
    //movemos la pelota segun con los datos que hayamos cambiado.
    _pelota[cero]->move(x,y);
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

