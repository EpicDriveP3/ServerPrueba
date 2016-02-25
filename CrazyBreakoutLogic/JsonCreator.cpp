/* 
 * File:   JsonCreator.cpp
 * Author: ellioth
 * 
 * Created on February 17, 2016, 11:24 PM
 */

#include "JsonCreator.h"

JsonCreator::JsonCreator() {

}

JsonCreator::~JsonCreator() {
}

string JsonCreator::create(Bola* bola[], BarraPLY* plyrs[], BarraDes* barrs[],
        int pBolas, int pPlyrs, int pBarrs){
    _mensaje="{";
    for(int i=0;i <pPlyrs; i++){
        _mensaje+="plyr"+to_string(i)+":"+to_string(plyrs[i]->getPosX())+","+
                to_string(plyrs[i]->getSize());
    }
    for(int i=0; i<pBolas;i++){
        _mensaje+=";bola"+to_string(i)+":"+to_string(bola[i]->getPx())+","+
                to_string(bola[i]->getPy());
    }
    for(int i=0; i<pBarrs; i++){
        _mensaje+=";barra"+to_string(i)+":"+to_string(bola[i]->getPx())+","+
                to_string(bola[i]->getPy())+","+to_string(barrs[i]->getHitLft());
    }
    _mensaje+="}";
    return _mensaje;
}

