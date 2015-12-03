#include "Brazo.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

char vitalSign[] = "AYA";
char vitalResponse[] = "Y";
char received_OK[] = "SMM";
const double maxError = 1e-10;
const int nIterMax = 99;

double Brazo::fBeta(double angBeta){
	double y = pow(la,2) + pow(lb,2) - pow(R,2) + 2 * la * lb * cos(angBeta);
	return y;
}

double Brazo::dBeta(double angBeta){
	double y = - 2 * la * lb * sin (angBeta);
	return y;
}

double Brazo::fAlfa(double angAlfa){
	double y = la * sin(beta) - R * sin(theta - angAlfa);
	return y;
}

double Brazo::dAlfa(double angAlfa){
	double y = R * cos(theta - alfa);
	return y;
}

flag Brazo::calcBeta(double b){
	
	double x0      = b;
	double x1;
	
	int    numIter = 1;
	double errIter;
	
	do{
		if(fabs(dBeta(x0)) <= ZERO){
			return CALC_ERROR;
		}else{
			x1      = x0 - fBeta(x0) / dBeta(x0);
			errIter = fabs(x1 - x0);
			x0      = x1;
			numIter++;
		}
	}while(errIter > maxError && numIter <= nIterMax);
	
	if(numIter >= nIterMax){
		return ITERMAX;
	}else{
		beta = x1;
		betaErr = errIter;
		return OK;
	}
	
}

flag Brazo::calcAlfa(double a){
	
	double x0      = a;
	double x1;
	
	int    numIter = 1;
	double errIter;
	
	do{
		if(fabs(dAlfa(x0)) <= ZERO){
			return CALC_ERROR;
		}else{
			x1      = x0 - fAlfa(x0) / dAlfa(x0);
			errIter = fabs(x1 - x0);
			x0      = x1;
			numIter++;
		}
	}while(errIter > maxError && numIter <= nIterMax);
	
	if(numIter >= nIterMax){
		return ITERMAX;
	}else{
		alfa = x1;
		alfaErr = errIter;
		return OK;
	}
	
}

flag Brazo::Mover(double xTarget, double yTarget){
	
	R = sqrt(pow(xTarget,2)+pow(yTarget,2));
	theta = atan2(yTarget,xTarget);
	
	if(calcBeta(beta) != OK){
		return CALC_ERROR;
	}
	
	if(calcAlfa(alfa) != OK){
		return CALC_ERROR;
	}
		
	int tries = 0;
	while(tries < 3){
		char respuesta[5];
		
		micro->WriteData(vitalSign,sizeof(vitalSign));
		
		if(micro->WaitForAnswer(respuesta,5,TIMEOUT) == -1){
			return NO_SIGN;
		}
		
		if(strcmp(respuesta,vitalResponse) == 0){
			char coord[30];
			sprintf(coord,"%lf;%lf #",alfa,beta);
			micro->WriteData(coord,sizeof(coord));
		}
		
		if(micro->WaitForAnswer(respuesta,5,TIMEOUT) == -1){
			return NO_SIGN;
		}
		
		if(strcmp(respuesta,received_OK) == 0){
			x = xTarget;
			y = yTarget;
			return OK;
		}
		tries++;
	}
	
	return CANT_COM;
	
}

flag Brazo::Trazar(){
	
	double x;
	double y;
	
	double *module;
	double *angle;
	
	ifstream puntos;
	puntos.open(pathIn,ios::in);
	
	char nPuntos[10];
	int nP;
	puntos.getline(nPuntos,sizeof(nPuntos));
	sscanf(nPuntos,"%d;",&nP);
	module = new double[nP];
	angle = new double[nP];
	
	int counter = 0;
	
	while(!puntos.eof()){
		char linea[20];
		puntos.getline(linea,sizeof(linea));
		sscanf(linea,"%lf;%lf\n",&x,&y);
		
		module[counter] = sqrt(pow(x,2)+pow(y,2));
		angle[counter] = atan2(y,x);
		counter++;
	}
	puntos.close();
	
	ofstream salida;
	salida.open(pathOut,ios::out);
	
	char respuesta[5];
		
	micro->WriteData(vitalSign,sizeof(vitalSign));
		
	if(micro->WaitForAnswer(respuesta,5,TIMEOUT) == -1){
			return NO_SIGN;
	}
	if(strcmp(respuesta,vitalResponse) == 0){
		
		for(int i = 0; i < nP; i++){
		
			R = module[i];
			theta = angle[i];
				
			if(calcBeta(beta) != OK){
				return CALC_ERROR;
			}
			
			if(calcAlfa(alfa) != OK){
				return CALC_ERROR;
			}
				
			int tries = 0;
			
			while(tries < 3){
				
				char coord[30];
				sprintf(coord,"%lf;%lf #",alfa,beta);
				
				salida << coord << "\n";
				micro->WriteData(coord,sizeof(coord));
				
				if(micro->WaitForAnswer(respuesta,5,TIMEOUT)){
					return NO_SIGN;
				}
				
				if(strcmp(respuesta,received_OK) == 0){
					break;
				}
				tries++;
			}
			if(tries >= 3){
				return CANT_COM;
			}
		}
	}else{
		
		return NO_SIGN;
	}
	
	delete [] module;
	delete [] angle;
}
