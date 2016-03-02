/* 
 * File:   Constantes.h
 * Author: ellioth
 *
 * Created on February 10, 2016, 2:43 PM
 */

#ifndef CONSTANTES_H
#define	CONSTANTES_H

class Constantes {
private:
    static const int BarraLengX=100;
public:
    //datos de pantallla
    static const int ScreenX=800;
    static const int ScreenY=600;
    //bandera para impirmir en pantalla
    static const bool debug=true;
    //largo del mensaje
    static const int LengMSG=2;
    //cantidad de jugadores
    static const int MaxPlyrs=2;
    
    /*-----------jugador-------------*/
    //dimensiones del cliente
    static const int PlayrLenght=100;
    static const int PlayrLengY=20;
    //posicion inicial del jugador
    static const int initPosXPLY=25;
    static const int PosYPLY=90;
    //constantes para disminuir el tamaño del cliente
    static const int Decrement=-5;
    static const int Increment=5;
    //constante para mover el cliente
    static const int pixlMovBrr=10;
    
    /*--------------bola-----------------*/
    //sector de choque contra la paleta del cliente
    static const int BarraLengXSector1=BarraLengX*(1/3);
    static const int BarraLengXSector2=BarraLengX*(2/3);
    static const int BarraLengXSector3=BarraLengX;
    //dimensiones de la bola
    static const int BallSize=20;
    //constante para mover la bola
    static const int pixlMovBll=10;
    
    /*--------------bloques-------------*/
    //cantidad de los bloques en pantalla
    static const int TotalBricks=64;
    static const int ColBrick=4;
    static const int RowBrick=16;
    static const int BrrSize=50;
    
    //constantes varias
    static const int cero=0;
    static const int uno=1;
    static const int dos=2;
    static const int tres=3;
    static const int cuatro=4;
    static const int cinco=5;
    static const int seis=6;
    static const int siete=7;
    static const int diez=10;
    static const int cincuenta=50;
    
    /*-------errores por parte del server------*/
    static const char* error1;
    static const char* error2;
    static const char* error3;
    static const char* error4;
    static const char* error5;
    static const char* error6;
    
};

#endif	/* CONSTANTES_H */

