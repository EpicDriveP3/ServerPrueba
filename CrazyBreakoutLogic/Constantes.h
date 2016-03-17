/* 
 * File:   Constantes.h
 * Author: ellioth
 *
 * Created on February 10, 2016, 2:43 PM
 */

#ifndef CONSTANTES_H
#define	CONSTANTES_H

/**
 * Datos internos para las constantes que se usaran en 
 * el proyecto.
 */
class Constantes {
private:
    /* constante usada para definir el tamaño estandar de la paleta*/
    static const int BarraLengX=100;
public:
    /*tamaño de la pantalla en X*/
    static const int ScreenX=800;
    /*tamaño de la pantalla en Y*/
    static const int ScreenY=600;
    /*variable para validar los prints en pantalla*/
    static const bool debug=true;
    /*largo del mensaje que se espera recibir*/
    static const int LengMSG=1;
    /*cantidad maxima de recepcion de jugadores*/
    static const int MaxPlyrs=10;
    
    /*-----------jugador-------------*/
    /*largo de la paleta del jugador en X*/
    static const int PlayrLenght=100;
    /*largo de la paleta del jugador en Y*/
    static const int PlayrLengY=20;
    /*pos inicial de la paleta en X*/
    static const int initPosXPLY=(ScreenX/2)-(PlayrLengY/2);
    /*posicion fija en Y*/
    static const int PosYPLY=ScreenY-(PlayrLengY+100);
    /*constante para disminuir el tamaño de la barra*/
    static const int Decrement=-5;
    /*constante para aumentar el tamaño de la barra*/
    static const int Increment=5;
    /*cantidad de movimiento en pixeles*/
    static const int pixlMovBrr=10;
    /**mensaje de que el movimiento es nulo*/
    static const char* NullMove;
    /**mensaje de que el movimiento es izquierdo*/
    static const char* LeftMove;
    /**mensaje de que el movimiento es derecho*/
    static const char* RightMove;
    
    /*--------------bola-----------------*/
    /*espacio del choque con el primer sector de la barra para cambiar su 
     direccion*/
    static const int BarraLengXSector1=BarraLengX*(1/3);
    /*espacio del choque con el segundo sector de la barra para cambiar su 
     direccion*/
    static const int BarraLengXSector2=BarraLengX*(2/3);
    /*espacio del choque con el tercer sector de la barra para cambiar su 
     direccion*/
    static const int BarraLengXSector3=BarraLengX;
    /*tamaño de la pelota*/
    static const int BallSize=20;
    /*tamaño de la pelota, como es cuadrada solo se ocupa una constante*/
    static const int pixlMovBll=1;
    
    /*--------------bloques-------------*/
    /*cantidad total de bloques con lo que trabajaremos*/
    static const int TotalBricks=64;
    /*cantidad total de bloques por columna*/
    static const int ColBrick=4;
    /*cantidad total de bloques por fila*/
    static const int RowBrick=16;
    /*tamaño del bloque*/
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

