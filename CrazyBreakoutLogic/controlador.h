/* 
 * File:   controlador.h
 * Author: ellioth
 *
 * Created on February 12, 2016, 3:50 PM
 */

#ifndef CONTROLER_H
#define	CONTROLER_H
#include "Bola.h"
#include "BarraDes.h"
#include "BarraPLY.h"
#include "Constantes.h"
#include "servidor.h"
#include "JsonCreator.h"
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <strings.h>

using namespace std;
/**
 * clase para controlar toda la logica, en esta se realiza 
 * todo lo necesario de movimientos, revizar coliciones, etc.
 * @param Pport recibe el puerto por donde se van a conectar
 * las personas.
 */
class controlador: public Constantes{
friend class servidor;
public:
    controlador(int Pport);
    virtual ~controlador();
    void setDirection(int pDirr);
private:
    //pelota en el campo
    Bola* _pelota[cinco];
    //barras que se destruiran en el campo
    BarraDes * _barras[TotalBricks];
    //paleta de jugadores
    BarraPLY * _ply[MaxPlyrs];
    //server por el cual nos conectaremos contra la gente
    servidor * _servidor;
    //variable 
    JsonCreator * _Json;
    //dato entero que es puerto por el cual van a acceder los clientes.
    int _port;
    /**
     * _BallsLeft-> dato que contiene la cantidad de pelotas en campo
     * _BarrsLeft-> dato que contiene la cantidad de barras restante en campo.
     */
    int _Tplys, _BallsLeft,_BarrsLeft;
    //ciclo principal para verificar todo lo que esta trabajando.
    void MainLoop();
    //metodo para destruir un objeto.
    void destroyObj(int BarNum);
    //metodo para redimencionar la barra cuando se salga del campo.
    void resizeBar(int pTypeOP);
    //metodo para revizar coliciones contra los objetos del campo.
    void checkColl();
    //metodo para revizar la coneccion contra los jugadores.
    bool checkContt();
};

#endif	/* CONTROLER_H */

