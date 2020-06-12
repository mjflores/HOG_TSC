/*======================================================================
		Programa para generar caracteristicas HOG
Version: 1.0
Autor:   Marco Flores
Empresa: Tecnologias I&H
========================================================================*/

#ifndef _ENTRENAMIENTO_H_
#define _ENTRENAMIENTO_H_

#include "hog.h"
#include "svm.h"
#include "leerCarpeta.h"
#include "direccion.h"
#include "guardarArchivo.h"
 

class TCaracteristicasHOG{
private:

THOG *miHOG;
IplImage *imgPatron;
TLeerCarpeta *leerImagenesNeg;

CGuardarArchivo *guardarArchivo;

double t;
char nombreArch[150];
char tiempo[150];


public:

TCaracteristicasHOG(void);
~TCaracteristicasHOG(void);
void hogCedaPaso(void); //Obtiene parametro HOG para ceda el paso
void hogPare(void);     //Obtiene parametros HOG para pare
void hogVelocidad(void);     //Obtiene parametros HOG para pare
void hogVelocidad10(void);     //Obtiene parametros HOG para pare
void hogVelocidad20(void);     //Obtiene parametros HOG para pare
void hogVelocidad30(void);     //Obtiene parametros HOG para pare
void hogVelocidad40(void);     //Obtiene parametros HOG para pare

};


#endif

