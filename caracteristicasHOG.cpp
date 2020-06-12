/*======================================================================
		Programa para generar caracteristicas HOG
Version: 1.0
Autor:   Marco Flores
Empresa: Tecnologias I&H
========================================================================*/


#include "caracteristicasHOG.h"


TCaracteristicasHOG::TCaracteristicasHOG(void)
{
	miHOG     = new THOG(cvSize(ancho_Imagen, alto_Imagen), ancho_Celda,alto_Celda,ancho_Bloque,alto_Bloque, orientaciones);
	imgPatron = cvCreateImage(cvSize(ancho_Imagen, alto_Imagen),8,1);//CREO UNA IMAGEN CON MEDIDAS ESPECIFICAS
	leerImagenesNeg = new TLeerCarpeta(DIR_NEGATIVO);


	//PARA LEER BASE DE DATOS CEDA PASO
		//sprintf(nombreTiempo,"MF_TiempoCedaPasoHOG_Tam_%dx%d_Cel_%dx%d_Bloq_%dx%d_Or_%d.txt",ancho_Imagen,alto_Imagen,ancho_Celda,alto_Celda,ancho_Bloque,alto_Bloque,orientaciones);
	sprintf(nombreArch,DIR_BASE_HOG"%dx%d_Cel_%dx%d_Bloq_%dx%d_Or_%d.txt",ancho_Imagen,alto_Imagen,ancho_Celda,alto_Celda,ancho_Bloque,alto_Bloque,orientaciones);
//printf("Que sale: %s\n",nombreArch);
	guardarArchivo = new CGuardarArchivo(nombreArch);
}

TCaracteristicasHOG::~TCaracteristicasHOG(void)
{
	cvReleaseImage(&imgPatron);
	delete miHOG;
	delete leerImagenesNeg;
	delete guardarArchivo;
}

void TCaracteristicasHOG::hogCedaPaso(void)
{
	TLeerCarpeta *leerImagenesCP = new TLeerCarpeta(DIR_CEDA_PASO);
	

	for(int i=0;i<(int)leerImagenesCP->ltNomImagenes.size();i++)
	{
		IplImage *img1 = cvLoadImage(leerImagenesCP->ltNomImagenes[i].c_str(),CV_LOAD_IMAGE_GRAYSCALE);//CARGO IMAGEN EN ESCALA DE GRISES
		if(img1 == NULL)
		{
			printf("No existe la imagen....%s\n",leerImagenesCP->ltNomImagenes[i].c_str());
			exit(-1);
		}		

	    	ajustarTamano(img1,imgPatron);// AJUSTO EL TAMANO A IMAGENES DE 32X32
		cvReleaseImage(&img1);

		cvEqualizeHist(imgPatron,imgPatron);// ECUALIZO LA IMAGEN (ESCALA DE GRISES)
		
		t = (double)cvGetTickCount();
		miHOG->vectorHOG(imgPatron);
		t = (double)cvGetTickCount() - t;
		sprintf(tiempo,"Tiempo de HOG de CEDA PASO de la Imagen %d = %g ms\n",i, t/((double)cvGetTickFrequency()*1000.));
	    
	     //guardarTiempos(nombreTiempo,tiempo);
//		printf("Tiempo: %s\n",tiempo);
		//CGuardarArchivo(nombreArch,miHOG->V_HOG,miHOG->dim_hog,CEDAPASO);
		guardarArchivo->insertarHOG(miHOG->V_HOG,miHOG->dim_hog,CEDAPASO);

	    cvShowImage("CedaPaso",imgPatron);
	    cvWaitKey(10);

	}

printf("Fin Positivas\n");
getchar();

for(int i=0;i<leerImagenesNeg->ltNomImagenes.size();i++)
{
	IplImage *img1 = cvLoadImage(leerImagenesNeg->ltNomImagenes[i].c_str(),CV_LOAD_IMAGE_GRAYSCALE);//CARGO IMAGEN EN ESCALA DE GRISES
	if(img1 == NULL)
	{
		printf("No existe la imagen....%s\n",leerImagenesNeg->ltNomImagenes[i].c_str());
		exit(-1);
	}
	ajustarTamano(img1,imgPatron);// AJUSTO EL TAMANO A IMAGENES DE 32X32
        cvReleaseImage(&img1);
	
	cvEqualizeHist(imgPatron,imgPatron);// ECUALIZO LA IMAGEN (ESCALA DE GRISES)
	t = (double)cvGetTickCount();
	miHOG->vectorHOG(imgPatron);
	t = (double)cvGetTickCount() - t;
//	sprintf(tiempo,"Tiempo de HOG NEGATIVOS de la Imagen %d = %g ms\n",i, t/((double)cvGetTickFrequency()*1000.));
    //guardarTiempos(nombreTiempo,tiempo);
	printf("Tiempo: %s\n", tiempo);
	//CGuardarArchivo(nombreArch,miHOG->V_HOG,miHOG->dim_hog,NEGATIVO);
	guardarArchivo->insertarHOG(miHOG->V_HOG,miHOG->dim_hog,NEGATIVO);
	cvShowImage("Negativo",imgPatron);
	cvWaitKey(100);
}

printf("Fin Negativas\n");

/*
for(int i=1;i<=numImgCedaPaso;i++)
{
printf("Estoy aqui.....\n");
	leerImagen->leerCedaPaso(i,nomImagen);

	IplImage *img1 = cvLoadImage(nomImagen,CV_LOAD_IMAGE_GRAYSCALE);//CARGO IMAGEN EN ESCALA DE GRISES
	if(img1 == NULL)
	{
		printf("No existe la imagen....%s\n",nomImagen);
		exit(-1);
	}
	
	ajustarTamano(img1,imgPatron);// AJUSTO EL TAMANO A IMAGENES DE 32X32
        cvReleaseImage(&img1);

	cvEqualizeHist(imgPatron,imgPatron);// ECUALIZO LA IMAGEN (ESCALA DE GRISES)
	
	t = (double)cvGetTickCount();
	miHOG->vectorHOG(imgPatron);
	t = (double)cvGetTickCount() - t;
	sprintf(tiempo,"Tiempo de HOG de CEDA PASO de la Imagen %d = %g ms\n",i, t/((double)cvGetTickFrequency()*1000.));
    
     //guardarTiempos(nombreTiempo,tiempo);
	printf("Tiempo: %s\n",tiempo);
	CGuardarArchivo(nombreArch,miHOG->V_HOG,miHOG->dim_hog,CEDAPASO);
	guardarArchivo->insertarHOG(miHOG->V_HOG,miHOG->dim_hog,CEDAPASO);

    cvShowImage("CedaPaso",imgPatron);
	cvWaitKey(1);



}
*/


/*
for(int i=1;i<=numImgNegativa;i++)
{
	leerImagen->leerNegativas(i,nomImagen);
	IplImage *img1 = cvLoadImage(nomImagen,CV_LOAD_IMAGE_GRAYSCALE);//CARGO IMAGEN EN ESCALA DE GRISES
	if(img1 == NULL)
	{
		printf("No existe la imagen....%s\n",nomImagen);
		exit(-1);
	}
	ajustarTamano(img1,imgPatron);// AJUSTO EL TAMANO A IMAGENES DE 32X32
        cvReleaseImage(&img1);
	cvEqualizeHist(imgPatron,imgPatron);// ECUALIZO LA IMAGEN (ESCALA DE GRISES)
	t = (double)cvGetTickCount();
	miHOG->vectorHOG(imgPatron);
	t = (double)cvGetTickCount() - t;
	sprintf(tiempo,"Tiempo de HOG NEGATIVOS de la Imagen %d = %g ms\n",i, t/((double)cvGetTickFrequency()*1000.));
    //guardarTiempos(nombreTiempo,tiempo);
	printf("Tiempo: %s\n", tiempo);
	CGuardarArchivo(nombreArch,miHOG->V_HOG,miHOG->dim_hog,NEGATIVO);
    cvShowImage("Negativo",imgPatron);

	for(int j=1;j<=3;j++)
        {
	rotarImagen(imgPatron,imgPatron,90);
	t = (double)cvGetTickCount();
	miHOG->vectorHOG(imgPatron);
	t = (double)cvGetTickCount() - t;
	sprintf(tiempo,"Tiempo de HOG NEGATIVOS de la Imagen %d-%d = %g ms\n",i,90*j, t/((double)cvGetTickFrequency()*1000.));
    //guardarTiempos(nombreTiempo,tiempo);
	printf("Tiempo: %s\n", tiempo);
	CGuardarArchivo(nombreArch,miHOG->V_HOG,miHOG->dim_hog,NEGATIVO);
	guardarArchivo->insertarHOG(miHOG->V_HOG,miHOG->dim_hog,NEGATIVO);
    cvShowImage("Rotado",imgPatron);
	cvWaitKey(1);	
	}
}
*/

delete leerImagenesCP;


}


//======================================================
//======================================================

void TCaracteristicasHOG::hogPare(void)
{

}


void TCaracteristicasHOG::hogVelocidad(void)     //Obtiene parametros HOG para Velocidad
{
	hogVelocidad10();     //Obtiene parametros HOG para pare
	hogVelocidad20();     //Obtiene parametros HOG para pare
	hogVelocidad30();     //Obtiene parametros HOG para pare
	hogVelocidad40();     //Obtiene parametros HOG para pare
}

void TCaracteristicasHOG::hogVelocidad10(void) 
{
}

void TCaracteristicasHOG::hogVelocidad20(void) 
{
}

void TCaracteristicasHOG::hogVelocidad30(void) 
{
}

void TCaracteristicasHOG::hogVelocidad40(void) 
{
}
