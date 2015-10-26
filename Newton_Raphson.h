#ifndef NEWTON_RAPHSON_H
#define NEWTON_RAPHSON_H

#include <math.h>

// Defino un valor de "cero" para tener de referencia en la implementacion
#define ZERO 1e-60

// Valores de retorno del metodo, para control de ejecucion
enum flag {OK,ERROR,ITERMAX,NOTCALC};

class Newton_Raphson
{
	public:
		// Constructor: genera un puntero a la funcion a evaluar y a su derivada,
		// y setea el numero maximo de iteraciones y el error maximo tolerado
		Newton_Raphson(double (*f)(double),double (*d)(double),int nIterMaxIn = 99,double maxErrorIn = 1e-10){
			maxError = maxErrorIn;
			nIterMax = nIterMaxIn;
			func     = f;
			derivada = d;
			resul    = NOTCALC;
		}
		
		Newton_Raphson(){
			maxError = 0;
			nIterMax = 0;
			func     = 0;
			derivada = 0;
			resul    = NOTCALC;
		}
				
		/* Funcion sobrecargada que ejecuta el metodo de Newton Raphson comun o modificado, segun se indique.
		   Admite pasarle 3 variables por referencia para guardar los resultados, pero
		   de todos modos, los resultados son guardados en variables propias del objeto. */
		int calculate(double, double &, double &, int &);
		int calculate(double);
		
		/* Metodos para LEER las variables privadas de la clase 
		   IMPORTANTE: si nunca se llamo a la funcion calculate(), la llamada
		   a las siguientes funciones devuelven 0 */
		double getSolution(){
			if(resul != NOTCALC) return Solution;
			return 0;
		}
		
		double getError(){
			if(resul != NOTCALC) return Error;
			return 0;
		}
		
		int getIter(){
			if(resul != NOTCALC) return nIter;
			return 0;
		}
		
		double getInitPoint(){
			if(resul != NOTCALC) return InitPoint;
			return 0;
		}
		
		flag getFlag(){
			return resul;
		}
		
		/* El error maximo y el numero maximo de iteraciones puede ser elegido en tiempo de
		   ejecucion a traves del operador punto (.) */
		double maxError;
		int    nIterMax;
		
	private:
		
		// Variables para guardar el resultado del calculo 
		double Error;                   // Error propio del calculo
		double Solution;                // Solucion encontrada
		int    nIter;                   // Numero de iteraciones utilizadas
		double InitPoint;               // Punto inicial pasado a la funcion (para llevar registro)
		
		// Punteros a la funcion y su derivada, inicializados en el constructor
		double (*func)(double);
		double (*derivada)(double);
		
		// Indicador de estado una vez terminado el calculo
		flag resul;
				
};

#endif
