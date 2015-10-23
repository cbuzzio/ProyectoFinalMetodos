#include <iostream>
#include <fstream>
#include <String.h>
#include <stdio.h>
#include "Brazo.h"
using namespace std;

char pathnombre[50];
char *path = NULL;
char port[] = "COM5";
Brazo brazo(10,5,port);

int main(int argc,char *argv[]){
	
	if(argc == 1){
		cout << "Ingrese el path del archivo a imprimir: "<<endl;
		cin >> pathnombre;
		path = new char[strlen(pathnombre)+1];
		strcpy(path,pathnombre);
	}else{
		path = argv[1];
	}
	
	ifstream data;
	cout << endl << path << endl << endl;
	data.open(path);
	
	if(data.fail()){
		cout << "Error al abrir el archivo";
		cin.get();
		cin.get();
		return 0;
	}else{
		while(!data.eof()){
			char linea[60];
			double x;
			double y;
			data.getline(linea,sizeof(linea));
			sscanf(linea,"%lf;%lf\n",&x,&y);
			if(!brazo.Mover(x,y)){
				cout << "Error, punto no alcanzable!"<<endl;
				cin.get();
				cin.get();
				return 0;
			}
		}
	}
	data.close();
	cin.get();
}
