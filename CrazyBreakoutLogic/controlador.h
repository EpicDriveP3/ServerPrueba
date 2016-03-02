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
#include <string.h>
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
    int _Tplys, _BallsLeft,_BarrsHit;
    void MainLoop();
    void destroyObj(int BarNum);
    void resizeBar(int pTypeOP);
    void checkColl();
    void checkCollBrr(int bar, int *x, int*y);
    void checkCollPly(int plyr, int *x, int*y);
    bool getBoolMutex(int plyr);
    string getMsgMutex(int plyr);
};

#endif	/* CONTROLER_H */

