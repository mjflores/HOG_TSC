/*======================================================================
		Programa para generar caracteristicas HOG
Version: 1.0
Autor:   Marco Flores
Empresa: Tecnologias I&H
========================================================================*/


#ifndef _GUARDAR_ARCHIVO_H_
#define _GUARDAR_ARCHIVO_H_

#include"varios.h"

class CGuardarArchivo{

private:

	ofstream *archivo;

public:
	
	// Guarda los datos en fila con indicador (Matriz dispersa)
//	CGuardarArchivo(char *nombre,float *datosFila, int tm, int clase);

	CGuardarArchivo(char *nombre);
	void insertarHOG(float *datosFila,int tm,int clase);
	~CGuardarArchivo(void);
};

#endif
