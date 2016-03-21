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
    string _mensaje,temp;
    //crea un mensaje que indica la terminacion del juego.
    if(pBolas==cero || pBarrs==-dos){
        _mensaje="terminate";
    }
    //condicion para cuando aun no ha terminado el juego
    else{
        //agregamos al inicio del mensaje la cantidad de datos que van
        _mensaje="{"+to_string(pBolas)+","+ to_string(pPlyrs)
                +","+ to_string(pBarrs);
        //ciclo para agregar a las pelotas.
        for(int i=0; i<pBolas;i++){
            temp=";Bo:"+to_string(bola[i]->getPx())+
                    ","+to_string(bola[i]->getPy());
            _mensaje.append(temp);
        }
        //ciclo para agregar a los jugadores.
        for(int i=0;i <pPlyrs; i++){
            temp=";Pl:"+to_string(plyrs[i]->getPosX())+","+
                    to_string(plyrs[i]->getSize());
            _mensaje.append(temp);
        }
        //parte para agregar el bloque.
        if(barrs==NULL && pBarrs>=cero){
            temp=";Bl:"+to_string(pBarrs)+","+to_string(cero);
            _mensaje.append(temp);
        }
        else if(pBarrs>=cero){
            temp=";Bl:"+to_string(pBarrs)+","+to_string(barrs->getHitLft());
            _mensaje.append(temp);
        }
        _mensaje.append(";}\0");
    }
    return _mensaje;
}

