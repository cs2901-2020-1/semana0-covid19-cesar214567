#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <string>
#include <algorithm>
#define NUM_HILOS 4
using namespace std;

void leer_archivos(/*void *a,void * cadena */string a,string &cadena){
    string iterador;
    ifstream texto(a);
    getline(texto,iterador,'\n');
    while ( texto>>iterador ){
        cadena+=iterador;
        iterador.clear();

    }


}

void comparar_lineas(string cadena1,string cadena2,int lim_inf,int lim_sup,int &desigualdades  ){
    for (int i=lim_inf;i<lim_sup;i++){
        if (cadena1[i]==cadena2[i]){
            desigualdades++;
        }
    }
}


int get_porc_of_equality(string direccion_a,string direccion_b){
    string iterador;
    string iterador2;
    string primera_cadena="";
    for(auto it:primera_cadena){
    int temporal=it;
    cout<<temporal<<endl;
    }
    
    string segunda_cadena="";
    thread thread1(leer_archivos,direccion_a,std::ref(primera_cadena));
    thread thread2(leer_archivos,direccion_b,std::ref(segunda_cadena));
    thread1.join();
    thread2.join();
    int comparador= primera_cadena.size()-segunda_cadena.size();
    int desigualdades=0;
    thread lista_de_threads[NUM_HILOS];
    int lista_de_resultados[NUM_HILOS]={0};
    if (comparador<=0){
        int limite=primera_cadena.size()/NUM_HILOS;
        for (int i=0;i<NUM_HILOS-1;i++){
            lista_de_threads[i]=thread(comparar_lineas,primera_cadena,segunda_cadena,i*limite,(i+1)*limite,std::ref(lista_de_resultados[i]));
        }
        lista_de_threads[NUM_HILOS-1]=thread(comparar_lineas,primera_cadena,segunda_cadena,(NUM_HILOS-1)*limite,primera_cadena.size(),std::ref(lista_de_resultados[NUM_HILOS-1]));
        for (int i=0;i<NUM_HILOS;i++){
            lista_de_threads[i].join();
        }
        desigualdades-=comparador;
    }else{
        int desigualdades2=0;
        for (int i=0;i<segunda_cadena.size();i++){
            if (primera_cadena[i]!=segunda_cadena[i]){
                desigualdades2++;
            }
        }
        cout<<desigualdades2<<endl;
        int limite=segunda_cadena.size()/NUM_HILOS;
        for (int i=0;i<NUM_HILOS-1;i++){
            lista_de_threads[i]=thread(comparar_lineas,primera_cadena,segunda_cadena,i*limite,(i+1)*limite,std::ref(lista_de_resultados[i]));
        }
        lista_de_threads[NUM_HILOS-1]=thread(comparar_lineas,primera_cadena,segunda_cadena,(NUM_HILOS-1)*limite,primera_cadena.size(),std::ref(lista_de_resultados[NUM_HILOS-1]));
        for (int i=0;i<NUM_HILOS;i++){
            lista_de_threads[i].join();
        }
        desigualdades+=comparador;
    }
    for (int i=0;i<NUM_HILOS;i++){
        desigualdades+=lista_de_resultados[i];
    }
    cout<<comparador<<endl;
    cout<<"numero de letras en texto1 "<<primera_cadena.size()<<"  numero de letras en texto2 "<< segunda_cadena.size()<<endl;
    
    return desigualdades;


}

int main(){
    string libro1="AY274119.txt";
    string libro2="AY278488.2.txt";
    cout<<get_porc_of_equality(libro1,libro2);

    
}