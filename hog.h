/*======================================================================
		Programa para generar caracteristicas HOG
Version: 1.0
Autor:   Marco Flores
Empresa: Tecnologias I&H
========================================================================*/


#ifndef _HOG_H_
#define _HOG_H_

#include "varios.h"

struct HistogramaCelda{
	float *Hcelda;
};

class TGradientes{
	public:
	CvMat *filter_x;
	CvMat *filter_y;
	CvSize tmImagen;
	public:
	IplImage *img_diff_x;
	IplImage *img_diff_y;
	IplImage *img_32f;
	private:
	void  imgMagnitudAngulo(IplImage *diff_x,IplImage *diff_y,IplImage *angs,IplImage *magt); //Obtener la magnitud y la orientacion de una imagen a travez de las convoluciones
	public:
	IplImage *magnit;
	IplImage *angles;
	public:
	TGradientes(CvSize szImg);
	void calcularImgMagAng(const IplImage *src);	//Calcula la magnitud y angulo del gradiente de una imagen
	~ TGradientes(void);		
};

void ajustarTamano(IplImage *src,IplImage *dst);
void rotarImagen(IplImage *src,IplImage *dst,double angulo); //Solo funciono en windows

class TCeldas{

	private:
	CvSize tmImg;
	CvRect **divisionCeldas;
	double *divisionOrientacion;
	
public:
	int celda_x;  // tamaño de celda en x
	int celda_y;  // tamaño de celda en y
	struct HistogramaCelda **HistCelda; //Matriz dinamica para almacenar el histograma de cada celda
	int orientacion;
	IplImage *tplAng;
	IplImage *tplMag;

	TGradientes *mscGrad;	//Elemento de gradiente

        void calcularHistogramaCelda(IplImage *magt,IplImage *angs, float Hcel[]);//Calcula el histograma de cada celda a travez de la magnitud y el angulo de gradiente
	void matrizHistogramaCelda(const IplImage *src);//Crea y guarda el histograma para cada celda a partir del calculo del histograma de celda

public:	
	TCeldas(CvSize Img, int celda_ancho,int celda_alto, int num_orientacion);//Constructor de celda	
	~TCeldas(void);
};

class THOG {

public:

	int bloque_x;   // numero de bloques en x
	int bloque_y;   // numero de bloques en y
	int bloque_xx;   // tamano del bloque en celdas (ancho)
	int bloque_yy;   // tamano del bloque en celdas (alto)
	float *HsN;		// vector por bloque sin normalizar
	float *HcN;		// vector por bloque normalizado
	TCeldas *micelda;	//nuevo elemento de celda
	float *V_HOG; // vector con caracteristicas HOG
	int dim_bloq; // dimension del vector por bloque
	int dim_hog; // dimension del vector HOG

	THOG(CvSize Img, int celda_ancho,int celda_alto,int bloque_ancho,int bloque_alto, int num_orientacion);// Contructor HOG
	~THOG(void);

	void vectorHOG(const IplImage *src); //extrae las caracteristicas HOG
	float normalizar(float *H2); //Normaliza el bloque
};

#endif
