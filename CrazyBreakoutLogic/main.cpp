/* 
 * File:   main.cpp
 * Author: ellioth
 *
 * Created on February 10, 2016, 1:55 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "Bola.h"
#include <pthread.h>
#include <string.h>
#include "servidor.h"

using namespace std;

pthread_mutex_t lock;


/*
 * 
 */
int main(int argc, char** argv) {
    //string dato = "0001";
    //string dato2= dato.substr(0,2);
    //string dato = "-1";
    //int dato2=stoi(dato);
    //cout<<dato2<<endl;
    //cout<<dato.length()<<endl;
    //forma 1
    /*
    Bola * pelota[3];
    pelota[0]= new Bola(1, 2);
    pelota[1]= new Bola(1, 2);
    pelota[2]= new Bola(1, 2);
    Bola * temp= pelota[0];
    pelota[0]=NULL;
    temp->~Bola();
    cout<<pelota[0]->getPx()<<endl;
    temp->move(1,1);
    cout<<temp->getPx()<<endl;
    */
    //forma 2 
    /*
    Bola * pelota[3];
    pelota[0]= new Bola(1, 2);
    pelota[1]= new Bola(1, 2);
    pelota[2]= new Bola(1, 2);
    delete pelota[0];
    pelota[1]->~Bola();
    pelota[2]->~Bola();
    //pelota[0]=new Bola(3,4);
    cout<<pelota[0]->getPx()<<endl;
    pelota[0]->move(1,1);
    cout<<pelota[0]->getPx()<<endl;
    */
    /*
    ThreadData datos;
    datos._Tplyr=1234;
    datos._Tsockfd=5678;
    metodoPrueba(&datos);
     
    string dato="{2,1,64;Bo:200,300;Bo:100,500;Pl:200,10;}";
    string temp=dato;
    //cout<<dato.find(",")<<endl;
    int n=1,i,pos=dato.find(";");
    int pBola, pPlyrs, pBolcks;
    ----bloque para econtrar cantidad de datos----
    i=temp.find(",",n);
    pBola=stoi(dato.substr(n,i));
    cout<<pBola<<endl;
    n=i+1;
    i=temp.find(",",n);
    pPlyrs=stoi(dato.substr(n,i));
    cout<<pPlyrs<<endl;
    n=i+1;
    i=temp.find(";",n);
    pBolcks=stoi(dato.substr(n,i));
    cout<<pBolcks<<endl;
    n=i+1;
    
    ----bloque para encontrar datos de una bola----
    cout<<"---bola---"<<endl;
    for(int f=0; f<pBola; f++){
        n=dato.find(":",n)+1;
        i=dato.find(",",n);
        int x=stoi(dato.substr(n,i));
        n=i+1;
        i=dato.find(";",n);
        int y=stoi(dato.substr(n,i));
        cout<<x<<endl;
        cout<<y<<endl;
    }
    cout<<"---player----"<<endl;
    for(int f=0; f<pPlyrs; f++){
        n=dato.find(":",n)+1;
        i=dato.find(",",n);
        int x=stoi(dato.substr(n,i));
        n=i+1;
        i=dato.find(";",n);
        int y=stoi(dato.substr(n,i));
        cout<<x<<endl;
        cout<<y<<endl;
    }
    int i=temp.find(",");
    cout<<stoi(dato.substr(n,i))<<endl;
    n=i+1;*/
    /*
    last= dato.find(":",last)+1;
    actual= dato.find(",",last);
    int BloqueID= stoi(dato.substr(last,actual));
    last=actual+1;
    actual=dato.find(";",last);
    int hitsLeft=stoi(dato.substr(last,actual));
    //aca tenes que establecer los atributos del bloque
    //un ->setHits(hitsLeft); y el BloqueID lo usas para
    //moverte en el arreglo de punteros que tenes para los bloques.
    //como recomendacion podes mandar a eliminar el bloque si 
    //el hitLeft==0*/
    /**
     * correr con un hilo esta vara 
     */
    pthread_mutex_t _lock;
    if(pthread_mutex_init(&_lock,NULL)!=0)
    return -1;
    servidor * server= new servidor(5000);
    cout<<"prueba-1"<<endl;
    while(true){
        cout<<"prueba-2"<<endl;
        cout<<server->getTplyrs()<<endl;
        for(int i =0; i<server->getTplyrs(); i++){
            if(server->getMSGPlyrs(i)!="N"){
                pthread_mutex_lock(&_lock);
                cout<<server->getMSGPlyrs(i)<<endl;
                server->setMsg(i);
                pthread_mutex_unlock(&_lock);
            }
        }
    }
    return 0;
}

