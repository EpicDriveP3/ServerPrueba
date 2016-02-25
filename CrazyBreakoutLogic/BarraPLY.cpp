/* 
 * File:   BarraPLY.cpp
 * Author: ellioth
 * 
 * Created on February 10, 2016, 1:56 PM
 */

#include "BarraPLY.h"

BarraPLY::BarraPLY(int pId) {
    _id=pId;
    _PosX=initPosXPLY;
    _PosY=PosYPLY;
}

BarraPLY::~BarraPLY() {
    
}

int BarraPLY::getPosX() {
    return _PosX;
}

int BarraPLY::getPosY() {
    return _PosY;
}

int BarraPLY::getSize() {
    return _size;
}

int BarraPLY::resize(int pOP) {
    if(pOP==Decrement)
        _size+=Decrement;
    _size+=Increment;
}

void BarraPLY::move(int pX) {
    if (pX>cero)
        _PosX+=pixlMovBrr;
    else if (pX<cero)
        _PosX-=pixlMovBrr;
}
