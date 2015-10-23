#ifndef BRAZO_H
#define BRAZO_H

#include "SerialClass.h"

#define ZERO 1e-15
#define TIMEOUT 1000

enum flag{OK,CALC_ERROR,ITERMAX,NOTCALC,CANT_COM,NO_SIGN};

class Brazo{
	
	private:
		double la;
		double lb;
		
		double R;
		double theta;
		
		double alfa;
		double alfaErr;
		double beta;
		double betaErr;
		
		double x;
		double y;
		
		double fAlfa(double);
		double dAlfa(double);
	
		double fBeta(double);
		double dBeta(double);
		
		flag calcBeta(double);
		flag calcAlfa(double);
		
		Serial *micro;
		
		char* pathIn;
		char* pathOut;
		

		

		
	public:
		
		Brazo (double longA, double longB, char *portName){
		 la = longA;
		 lb = longB;
		 alfa = 0;
		 beta = 0;
		 x = la + lb;
		 y = 0;
		 micro = new Serial(portName);
		 }
		 
		 ~Brazo(){
		 	delete micro;
		 	delete [] pathIn;
		 	delete [] pathOut;
		 }
		 
		 
		flag Mover(double,double);
		
		void setDataFile(char *data){
			pathIn = data;
		}
		
		void setTargetFile(char *target){
			pathOut = target;
		}
		
		flag Trazar();
		
		double getBeta(void){
			return beta;
		}
		
		double getAlfa(void){
			return alfa;
		}
		
};

#endif
