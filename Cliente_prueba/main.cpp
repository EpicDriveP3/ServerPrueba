/* 
 * File:   main.cpp
 * Author: ellioth
 *
 * Created on March 4, 2016, 9:55 AM
 */

#include <cstdlib>
#include <iostream>
#include "cliente.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;



/*
 * 
 */
int main(int argc, char** argv) {
    cliente * cl= new cliente(5001,"127.0.0.1");
    cl->sendMsg("N");
    //cin.ignore();
    /*string msg="";
    for(;;)
        if(strlen(cl->getMensaje().c_str())>2 && strcmp(msg.c_str(),cl->getMensaje().c_str())!=0){
            msg= cl->getMensaje();
            cout<<msg<<endl;
        }
    cin.ignore();
    /*
    for(;;){
        cout<<cl->getMensaje()<<endl;
    }*/
    srand(time(NULL));
    int move;
    string left= "L";
    string right= "R";
    for(;;){
        move= rand()%2;
        if(move==0)
            cl->sendMsg(left);
        cl->sendMsg(right);
        //sleep(1);
    }
    return 0;
}

