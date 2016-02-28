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

/**
 * metodo para crear el Json que se le enviara al cliente que tenga la pantalla
 * @param bola dato tipo puntero que es el arreglo de las bolas en el campo.
 * @param plyrs dato tipo puntero que es el arreglo que contiene a los 
 * clientes conectados.
 * @param barrs dato tipo puntero que es el arreglo que contiene las barras o 
 * bloques restantes en el campo.
 * @param pBolas dato tipo entero que es la cantidad de bolas en el campo.
 * @param pPlyrs dato tipo entero que es la cantidad de jugadores en el campo.
 * @param pBarrs dato tipo entero que es la cantidad de bloques en el campo.
 * @return retorna un dato tipo string que es el Json creado.
 */
string JsonCreator::create(Bola* bola[], BarraPLY* plyrs[], BarraDes* barrs[],
        int pBolas, int pPlyrs, int pBarrs){
    _mensaje="{";
    //ciclo para agregar a las pelotas.
    for(int i=0; i<pBolas;i++){
        _mensaje+="bola"+to_string(i)+":"+to_string(bola[i]->getPx())+","+
                to_string(bola[i]->getPy());
    }
    //ciclo para agregar a los jugadores.
    for(int i=0;i <pPlyrs; i++){
        _mensaje+=";plyr"+to_string(i)+":"+to_string(plyrs[i]->getPosX())+","+
                to_string(plyrs[i]->getSize());
    }
    //ciclo para agregar a los bloques.
    for(int i=0; i<pBarrs; i++){
        _mensaje+=";barra"+to_string(i)+":"+to_string(bola[i]->getPx())+","+
                to_string(bola[i]->getPy())+","+to_string(barrs[i]->getHitLft());
    }
    _mensaje+="}";
    return _mensaje;
}

