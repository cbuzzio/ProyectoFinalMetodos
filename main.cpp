#include <iostream>
#include <fstream>
#include <String.h>
#include <stdio.h>
#include "Brazo.h"
using namespace std;

char pathnombre[50];
char *pathData = NULL;
char *pathSalida = NULL;
Brazo *brazo;
int nPuerto;
char portName[13];
double longA;
double longB;

int main(int argc,char *argv[]){
	
	if(argc == 1){
		cout << "Ingrese el path del archivo a trazar: "<<endl;
		cin >> pathnombre;
		pathData = new char[strlen(pathnombre)+1];
		strcpy(pathData,pathnombre);
	}else{
		pathData = argv[1];
	}
	
	cout << endl << "Ingrese el numero del puerto serie donde esta conectado el microcontrolador";
	cin >> nPuerto;
	if(nPuerto < 10){
			sprintf(portName,"COM%d",nPuerto);
		}else{
			sprintf(portName,"////.//COM%d",nPuerto);
		}
	
	cout << endl << endl << "Ingrese las longitudes de los brazos, separados por coma";
	scanf("%lf,%lf",&longA,&longB);
	
	brazo = new Brazo(longA,longB,portName);
	brazo->setDataFile(pathData);
	
	cout << "Ingrese el nombre del archivo de salida: "<<endl;
	cin >> pathnombre;
	pathSalida = new char[strlen(pathnombre)+1];
	strcpy(pathSalida,pathnombre);
	
	brazo->setTargetFile(pathSalida);
		
	cin.get();
}
