/* 
 * File:   structs.h
 * Author: ellioth
 *
 * Created on February 27, 2016, 9:56 PM
 */

#ifndef STRUCTS_H
#define	STRUCTS_H

/**
 * struct que usaremos para pasar datos por medio de los 
 * hilos.
 */
struct ThreadData{
    int _Tsockfd;
    int _Tplyr;
};


#endif	/* STRUCTS_H */

