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
    static const int ScreenX=100;
    static const int ScreenY=100;
    static const bool debug=true;
    static const int Decrement=-5;
    static const int Increment=5;
    static const int pixlMovBrr=10;
    static const int pixlMovBll=10;
    static const int BrrType1=1;
    static const int BrrType2=2;
    static const int BrrType3=3;
    static const int LengMSG=2;
    static const int PlayrLenght=100;
    static const int BarraLengXSector1=BarraLengX*(1/3);
    static const int BarraLengXSector2=BarraLengX*(2/3);
    static const int BarraLengXSector3=BarraLengX;
    static const int BarraLengY=20;
    static const int BallSize=20;
    static const int TotalBricks=20;
    static const int DosCincoSeis=256;
    static const int MaxPlyrs=1;
    static const int cero=0;
    static const int uno=1;
    static const int dos=2;
    static const int tres=3;
    static const int cinco=5;
    static const int seis=6;
    static const int siete=7;
    static const int initPosXPLY=25;
    static const int PosYPLY=90;
    static const char* error1;
    static const char* error2;
    static const char* error3;
    static const char* error4;
    static const char* error5;
    static const char* error6;
    
};

#endif	/* CONSTANTES_H */

