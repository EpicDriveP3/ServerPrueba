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
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>

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
private:
    //pelota en el campo
    Bola* _pelota[MaxBalls];
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
    int _dirrection;
    //variables para desplazar la pelota sobre la pantalla
    int _MoveBallX,_MoveBallY;
    /**
     * _BallsLeft-> dato que contiene la cantidad de pelotas en campo
     * _BarrsLeft-> dato que contiene la cantidad de barras restante en campo.
     */
    int _BallsLeft,_BarrsHit,_BarrsLeft;
    void MainLoop();
    void destroyObj(int BarNum);
    void resizeBar(int pTypeOP);
    void checkColl();
    void checkCollBrr(int bar, int *x, int*y, bool *bandera);
    void checkCollPly(int plyr, int *x, int*y, bool *bandera);
};

#endif	/* CONTROLER_H */

