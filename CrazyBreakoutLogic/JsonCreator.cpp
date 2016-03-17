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
 * @param pBarrs dato tipo entero que es el bloque que queremos decir que
 * recibio un golpe.
 * @return retorna un dato tipo string que es el Json creado.
 */
string JsonCreator::create(Bola* bola[], BarraPLY* plyrs[], BarraDes* barrs,
        int pBolas, int pPlyrs, int pBarrs){
    if(pBolas==cero || pBarrs==-dos)
        _mensaje="terminate";
    else{
        _mensaje="{"+to_string(pBolas)+","+to_string(pPlyrs)+","+to_string(pBarrs);
        //ciclo para agregar a las pelotas.
        for(int i=0; i<pBolas;i++){
            _mensaje+=";Bo:"+to_string(bola[i]->getPx())+","+
                    to_string(bola[i]->getPy());
        }
        //ciclo para agregar a los jugadores.
        for(int i=0;i <pPlyrs; i++){
            _mensaje+=";Pl:"+to_string(plyrs[i]->getPosX())+","+
                    to_string(plyrs[i]->getSize());
        }
        //ciclo para agregar el bloque.
        if(barrs==NULL && pBarrs>=cero)
            _mensaje+=";Bl:"+to_string(pBarrs)+","+to_string(cero);
        else if(pBarrs>=cero){
            _mensaje+=";Bl:"+to_string(pBarrs)+","+to_string(cero);
        }
        _mensaje+=";}";
    }
    return _mensaje;
}

