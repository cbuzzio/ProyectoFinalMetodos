#include "Newton_Raphson.h"

/* Funcion para ejecutar el metodo de Newton Raphson. A continuacion esta el caso mas general:
   Se pasa por copia el valor inicial en la variable 'x'
   Se pasan por referencia 3 variables para sacar los resultados al exterior
   Se pasa por copia la multiplicidad de la raiz en la variable 'm' */
   
int Newton_Raphson::calculate(double x, double &solExt, double &errorExt, int &iterExt){
	
	// Se inicializan las variables x0 y x1 que se utilizaran en las iteraciones
	double x0   = x;
	double x1;
	
	// Se inicializa el numero de iteraciones a 1
	int numIter = 1;
	
	double errIter;
	
	// Comienzo del bucle
	do{
		if(fabs(derivada(x0)) <= ZERO){                      // Si la derivada es muy proxima a cero en el punto a calcular en la iteracion
			resul = ERROR;                                   // el metodo diverge y devuelve la flag ERROR
			return resul;
		}else{
			x1      = x0 - func(x0) / derivada(x0);      // En caso contrario, se calcula la siguiente iteracion del método
			errIter = fabs(x1 - x0);                         // Se calcula el error de la iteracion
			x0      = x1;                                    // Se transfiere el valor calculado al valor inicial de la siguiente iteracion
			numIter++;                                       // Se incrementa el numero de iteraciones
		}
	}while(errIter > maxError && numIter <= nIterMax); // Se declara la condicion de escape del bucle
	
	if(numIter >= nIterMax){                                 
		resul = ITERMAX;									 // Si se alcanzo el numero maximo de iteraciones se devuelve la flag ITERMAX
	}else{
		resul = OK;                                          // Si no, la salida es OK
	}
	
	Solution  = solExt  = x1;                                  // La salida se guarda en las variables de la clase y en las externas
	Error     = errorExt = errIter;
	nIter     = iterExt  = numIter;
	InitPoint = x;
	
	return resul;
}

int Newton_Raphson::calculate(double x){
	
	double x0      = x;
	double x1;
	
	int    numIter = 1;
	double errIter;
	
	do{
		if(fabs(derivada(x0)) <= ZERO){
			resul = ERROR;
			return resul;
		}else{
			x1      = x0 - func(x0) / derivada(x0);
			errIter = fabs(x1 - x0);
			x0      = x1;
			numIter++;
		}
	}while(errIter > maxError && numIter <= nIterMax);
	
	if(numIter >= nIterMax){
		resul = ITERMAX;
	}else{
		resul = OK;
	}
	
	Solution  = x1;
	Error     = errIter;
	nIter     = numIter;
	InitPoint = x;

	return resul;
}


