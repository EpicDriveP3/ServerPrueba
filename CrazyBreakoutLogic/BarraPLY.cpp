/* 
 * File:   BarraPLY.cpp
 * Author: ellioth
 * 
 * Created on February 10, 2016, 1:56 PM
 */

#include "BarraPLY.h"

/**
 * constructor que recibe un id para identificarlos
 * @param pId dato tipo entero.
 */
BarraPLY::BarraPLY(int pId) {
    _id=pId;
    _PosX=initPosXPLY;
    _PosY=PosYPLY;
    _size=BarraLengXSector3;
}

BarraPLY::~BarraPLY() {
    
}

/**
 * metodo que retorna la posicion en X de la paleta del 
 * cliente
 * @return retorna un dato tipo entero que es la posicion en 
 * X. 
 */
int BarraPLY::getPosX() {
    return _PosX;
}

/**
 * metodo que retorna la posicion en Y de la barra para 
 * hacer reviciones contra esta coordenada.
 * @return retorna un dato tipo entero que es la posicion 
 * en Y.
 */
int BarraPLY::getPosY() {
    return _PosY;
}

/**
 * metodo que obtiene el tamaño dela paleta del cliente.
 * @return retorna un dato entero que es el tamaño de la paleta
 * del cliente.
 */
int BarraPLY::getSize() {
    return _size;
}

/**
 * metodo para redimencionar el tamaño de la paleta del cliente.
 * @param pOP recibe un dato entero que indica si vamos a hacer un
 * decremento o incremento.
 * @return retorna un dato entero que es el tamaño de la barra.
 */
int BarraPLY::resize(int pOP) {
    if(pOP==Decrement)
        _size+=Decrement;
    _size+=Increment;
}

/**
 * metodo para mover la paleta, actualiza su posicion en X
 * segun el tipo de mensaje que recibe.
 * @param pX recibe un dato tipo entero, este puede ser un 
 * positivo o negativo de hacia donde moverse.
 */
void BarraPLY::move(string pX) {
    if(_PosX>cero){
        if (strcmp(pX.c_str(),RightMove))
            _PosX+=pixlMovBrr;
    }
    if((_PosX+BarraLengXSector3)<ScreenX){
        if (strcmp(pX.c_str(),LeftMove))
            _PosX-=pixlMovBrr;
    }
}
