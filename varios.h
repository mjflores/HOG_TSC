/*======================================================================
		Programa para generar caracteristicas HOG
Version: 1.0
Autor:   Marco Flores
Empresa: Tecnologias I&H
========================================================================*/

#ifndef VARIOS_H
#define VARIOS_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <vector>
#include <dirent.h>
#include <sys/stat.h>




#include <opencv2/opencv.hpp>
/*
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc_c.h>
*/



using namespace std;
using namespace cv;

#define pi 3.14159265359

#define ancho_Imagen 32  // TAMAÑO DE LA IMAGEN EN PIXELES
#define alto_Imagen 32   // TAMAÑO DE LA IMAGEN EN PIXELES

#define ancho_Celda 8    //TAMAÑO DE LA CELDA EN PIXELES
#define alto_Celda 8     //TAMAÑO DE LA CELDA EN PIXELES

#define ancho_Bloque 2   //TAMAÑO DEL BLOQUE EN CELDAS
#define alto_Bloque 2    //TAMAÑO DEL BLOQUE EN CELDAS

#define orientaciones 9  //NUMERO DE ORIENTACION ENTRE EL RANGO -PI/2 A PI/2

#define caso 2           // Caso=1 ==>HOG Ceda Paso y Negativas... Caso=2 ==>HOG Pare y Negativas

#define kernel 1         // kernel=0 ==>Lineal ,kernel=1 ==>Polinomico,kernel=2 ==>BFC


//================================================================


// Para el entrenamiento y validacion de los metodos
static int numImgCedaPaso = 743;   //Numero de imagenes de ceda el paso en la base de datos  
static int numImgNegativa = 720;   //Numero de imagenes de pare en la base de datos  	
static int numImgPare     = 1000;  //Numero de imagenes negativas en la base de datos 
static int numImgTest     = 120;  

enum Tipo{NEGATIVO=-1,CEDAPASO=1,PARE=2,V10=3,V15=4,V20=5,V30=6,V35=7,V40=8,V45=9,V50=10,V60=11,V70=12,V80=13,V90=14,V100=15};



using namespace std;


#endif

