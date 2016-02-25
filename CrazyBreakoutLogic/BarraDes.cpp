/* 
 * File:   BarraDes.cpp
 * Author: ellioth
 * 
 * Created on February 10, 2016, 1:57 PM
 */

#include "BarraDes.h"

BarraDes::BarraDes(int pX, int pY, int pType) {
    _Posx=pX;
    _Posy=pY;
    _type=pType;
    _hitsLft=_type;
}

BarraDes::~BarraDes() {
}

int BarraDes::getHitLft() {
    return _hitsLft;
}

int BarraDes::getPosX() {
    return _Posx;
}

int BarraDes::getPosY() {
    return _Posy;
}

int BarraDes::getType() {
    return _type;
}

void BarraDes::impact() {
    _hitsLft--;
}
