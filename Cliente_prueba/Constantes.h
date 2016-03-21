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
public:
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
    static const int DosCincoSeis=256;
    static const bool debug=true;
    static const char* conexion;
    
    /*-------errores por parte del server------*/
    
    /*"ERROR opening socket"*/
    static const char* error1;
    /*"ERROR on binding"*/
    static const char* error2;
    /*"ERROR on accept"*/
    static const char* error3;
    /*"ERROR connecting"*/
    static const char* error4;
    /*"ERROR writing to socket"*/
    static const char* error5;
    /*"ERROR reading from socket"*/
    static const char* error6;
    
};

#endif	/* CONSTANTES_H */

