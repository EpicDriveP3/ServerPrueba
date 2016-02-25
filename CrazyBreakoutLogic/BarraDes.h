/* 
 * File:   BarraDes.h
 * Author: ellioth
 *
 * Created on February 10, 2016, 1:57 PM
 */

#ifndef BARRADES_H
#define	BARRADES_H
#include "Constantes.h"

class BarraDes:public Constantes {
public:
    BarraDes(int pX, int pY, int pType);
    virtual ~BarraDes();
    int getType();
    int getHitLft();
    int getPosX();
    int getPosY();
    void impact();
private:
    int _Posx, _Posy;
    int _hitsLft;
    int _type;
};

#endif	/* BARRADES_H */

