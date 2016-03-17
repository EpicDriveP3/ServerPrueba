/* 
 * File:   JsonCreator.h
 * Author: ellioth
 *
 * Created on February 17, 2016, 11:24 PM
 */

#ifndef JASONCREATOR_H
#define	JASONCREATOR_H
#include <string>
#include "BarraDes.h"
#include "BarraPLY.h"
#include "Bola.h"
#include "Constantes.h"

using namespace std;

/**
 * clase usada para crear el Json que se usara crear el mensaje que se enviara
 * al cliente que tenga pantalla.
 */

class JsonCreator: public Constantes {
public:
    JsonCreator();
    virtual ~JsonCreator();    
    string create(Bola* bola[], BarraPLY* plyrs[], BarraDes* Barrs,int pBolas,
    int pPlyrs, int pBarrs);
private:
    string _mensaje;
};

#endif	/* JASONCREATOR_H */

