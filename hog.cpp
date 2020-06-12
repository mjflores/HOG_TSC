/*======================================================================
		Programa para generar caracteristicas HOG
Version: 1.0
Autor:   Marco Flores
Empresa: Tecnologias I&H
========================================================================*/


#include "hog.h"
#include "varios.h"

using namespace cv;

TGradientes::TGradientes(CvSize szImg)
{

	/*Parametros iniciales del gradiente*/
	tmImagen = szImg;

	/*Filtros derivativos en x y*/
	filter_x = cvCreateMat(1,3,CV_32FC1);
	filter_y = cvCreateMat(3,1,CV_32FC1);
	
	/*Mascara del filtro x*/
	CV_MAT_ELEM( *filter_x, float, 0, 0) = -1;
	CV_MAT_ELEM( *filter_x, float, 0, 1) = 0;
	CV_MAT_ELEM( *filter_x, float, 0, 2) = 1;

	/*Mascara del filtro y*/
	CV_MAT_ELEM( *filter_y, float, 0, 0) = 1;
	CV_MAT_ELEM( *filter_y, float, 1, 0) = 0;
	CV_MAT_ELEM( *filter_y, float, 2, 0) = -1;

	/*Imagenes para la convolucion de filtros*/
	img_diff_x = cvCreateImage(tmImagen,IPL_DEPTH_32F,1);
	img_diff_y = cvCreateImage(tmImagen,IPL_DEPTH_32F,1);
	img_32f    = cvCreateImage(tmImagen,IPL_DEPTH_32F,1);

	/*Imagenes que almacenan la magnitud y el angulo*/
	magnit = cvCreateImage(tmImagen,IPL_DEPTH_32F,1);
	angles = cvCreateImage(tmImagen,IPL_DEPTH_32F,1);	
}


void TGradientes::calcularImgMagAng(const IplImage *src)
{
	cvConvert(src,this->img_32f);

	/*Convolucion de los filtros en la imagen*/
	cvFilter2D(this->img_32f,this->img_diff_x,this->filter_x);
	//cvShowImage("Horizontal",img_diff_x);
	cvFilter2D(this->img_32f,this->img_diff_y,this->filter_y);
	//cvShowImage("Vertical",img_diff_y);
	// Calculo de la magnitud y el angulo
	imgMagnitudAngulo(this->img_diff_x,this->img_diff_y,this->angles,this->magnit); //Calcula la magnitud y el angulo a partir de las convoluciones
	//printf("Calculando las imagenes de magnitud y angulo\n");
}

void  TGradientes::imgMagnitudAngulo(IplImage *diff_x,IplImage *diff_y,IplImage *angs,IplImage *magt)
{
	for(int i=0;i<tmImagen.height;i++)
	{
		for(int j=0;j<tmImagen.width;j++)
		{

			//Calcula la magnitud y angulo para cada pixel
			float y = ((float*)(diff_y->imageData + diff_y->widthStep*i))[j];
			float x = ((float*)(diff_x->imageData + diff_x->widthStep*i))[j];

			((float*)(angs->imageData + angs->widthStep*i))[j] = atan2(y,x);
			//((float*)(angs->imageData + angs->widthStep*i))[j] = atan(y/x);
			((float*)(magt->imageData + magt->widthStep*i))[j] = sqrt(y*y + x*x);
			//printf("Valor de Magnitud en x:%d, en y: %d es: %f \n",j,i,((float*)(magt->imageData + magt->widthStep*i))[j]);
			//printf("Valor de Angulo en x:%d, en y: %d es: %f con %f,%f\n",j,i,((float*)(angs->imageData + angs->widthStep*i))[j],y,x);
			
		}
		
	}
	
}

TGradientes::~TGradientes(void)
{
	/*Destructores del gradiente*/
	cvReleaseMat(&filter_x);
	cvReleaseMat(&filter_y);

	cvReleaseImage(&img_diff_x);
	cvReleaseImage(&img_diff_y);
	cvReleaseImage(&img_32f);

	cvReleaseImage(&magnit);
	cvReleaseImage(&angles);
	
}

void ajustarTamano(IplImage *src,IplImage *dst)
{
	if(src->width != dst->width || src->height != dst->height)
		cvResize(src,dst);
	else
		cvCopy(src,dst);
}

void rotarImagen(IplImage *src,IplImage *dst,double angulo)
{
	printf("La funcion rotarImagen No esta operativa...\n");
/*

//SOLO FUNCIONO EN WINDOWS LOS COMANDOS
Mat src1=src;
 //imshow("src", src1);
Mat dst1;
IplImage *dst2=cvCreateImage(cvSize(src->height, src->width),8,1);
Point2f pt(src1.cols/2., src1.rows/2.);;
Mat r = getRotationMatrix2D(pt,angulo, 1.0);
warpAffine(src1, dst1, r, Size(src1.cols, src1.rows));
 //imshow("dst", dst1);
dst2->imageData = (char *) dst1.data;
cvCopy(dst2,dst);*/
}


TCeldas::TCeldas(CvSize Img, int celda_ancho,int celda_alto, int num_orientacion){
	tmImg = Img;
	celda_x=tmImg.width/celda_ancho; //Numero de celdas en x
	celda_y=tmImg.height/ celda_alto; //numero de celdas en y
	orientacion=num_orientacion;
	//printf("Numero de celdas en x %d \n",celda_x);
	//printf("Numero de celdas en y %d \n",celda_y);
	
	/*Creo matriz dinamica a base del tama�o de celda*/
	divisionCeldas = new CvRect*[celda_y];
	HistCelda= new struct HistogramaCelda*[celda_y];
	for(int i=0;i<celda_y;i++){
	divisionCeldas[i] = new CvRect[celda_x];
	HistCelda[i]= new struct HistogramaCelda[celda_x];
	}

	for(int i=0;i<celda_y;i++)
	{
		for(int j=0;j<celda_x;j++)
			divisionCeldas[i][j]=cvRect(j*celda_ancho,i*celda_alto,celda_ancho, celda_alto);
	}


	/*Creo el rango de orientaciones de -pi/2 a pi/2 en base al numero de orientaciones*/
	divisionOrientacion = new double[orientacion+1];
	for(int i=0;i<orientacion+1;i++){
			divisionOrientacion[i]=(-pi/2)+(pi/orientacion)*i;
		}
	/*
	for(int i=0;i<orientacion+1;i++){
		printf("Valor vector orientaciones %f\n",divisionOrientacion[i]);
	}
	*/
	mscGrad = new TGradientes(tmImg);
	tplAng = cvCreateImage(cvSize(celda_ancho, celda_alto),IPL_DEPTH_32F,1);
	tplMag = cvCreateImage(cvSize(celda_ancho, celda_alto),IPL_DEPTH_32F,1);

}



void TCeldas::matrizHistogramaCelda(const IplImage *src)
{		
		// Calculo de los gradientes

	mscGrad->calcularImgMagAng(src);
	//cvShowImage("Angulos",mscGrad->angles);
	//cvShowImage("magnitud",mscGrad->magnit);

	//===============================================================
	// Calculo del histograma por cada celda a partir de las imagenes angles y magnit
	//===============================================================

	for(int i=0;i<celda_y;i++)
	{
		for(int j=0;j<celda_x;j++)
		{
			cvSetImageROI(mscGrad->angles,divisionCeldas[i][j]);
			cvCopy( mscGrad->angles, tplAng, NULL );
			//cvShowImage("Angulo parcial",tplAng);
			cvResetImageROI(mscGrad->angles);

			cvSetImageROI(mscGrad->magnit,divisionCeldas[i][j]);
			cvCopy( mscGrad->magnit, tplMag, NULL );
			//cvShowImage("Magnitud parcial",tplMag);
			cvResetImageROI(mscGrad->magnit);
			
			//==========================================
			
			HistCelda[i][j].Hcelda= new float[orientacion];
			//printf("Calculo Histograma en celda %d,%d\n",i+1,j+1);
			calcularHistogramaCelda(tplMag,tplAng,HistCelda[i][j].Hcelda);	

		}
	}
	 
	}

void TCeldas::calcularHistogramaCelda(IplImage *magt,IplImage *angs, float Hcel[])
{
	
	for(int i=0;i<orientacion;i++){
		Hcel[i]=0;
	}
	
	for(int k=1;k<orientacion+1;k++)
	{
		for(int i=0;i<angs->height;i++)
		{
			for(int j=0;j<angs->width;j++)
			{
     			float ang = ((float*)(angs->imageData + angs->widthStep*i))[j];

				if( ang>=divisionOrientacion[k-1] && ang<divisionOrientacion[k])
				{
					Hcel[k-1] += ((float*)(magt->imageData + magt->widthStep*i))[j];
				}
			}
		}
	}
	/*
	for(int i=0;i<orientacion;i++){
		printf("Histograma por celda en orientacion %d= %f\n",i+1,Hcel[i]);
	}
	*/
}


TCeldas::~TCeldas(void){
	delete mscGrad;
	cvReleaseImage(&tplAng);
	cvReleaseImage(&tplMag);
}


THOG::THOG(CvSize Img, int celda_ancho,int celda_alto,int bloque_ancho,int bloque_alto, int num_orientacion){
	
	/*Valores iniciales para el HOG*/
	bloque_xx=bloque_ancho;
	bloque_yy=bloque_alto;
	micelda=new TCeldas(Img, celda_ancho,celda_alto, num_orientacion);
	dim_bloq=bloque_xx*bloque_yy*micelda->orientacion;
	HsN=new float[dim_bloq];
	HcN=new float[dim_bloq];
	bloque_x=micelda->celda_x-bloque_xx+1;
	bloque_y=micelda->celda_y-bloque_yy+1;
	dim_hog=bloque_x*bloque_y*dim_bloq;
	V_HOG=new float[dim_hog];
	

	//printf("Tama�o del bloque en X = %d celdas \n",bloque_xx);
	//printf("Tama�o del bloque en Y = %d celdas \n",bloque_yy);
	
	
}

void THOG::vectorHOG(const IplImage *src){
	
	micelda->matrizHistogramaCelda(src);

	/*Muestro los valores del histograma por celda*/
	/*
	for(int i=0;i<micelda->celda_y;i++)
	{
		for(int j=0;j<micelda->celda_x;j++)
		{
			for(int k=0;k<micelda->orientacion;k++)
			{
			printf("En celda %d,%d el histograma orientado %d = %f \n",i+1,j+1,k+1,micelda->HistCelda[i][j].Hcelda[k]);
			}

		}
	}
	*/


//printf("El numero de bloques en X = %d  \n",bloque_x);
//printf("El numero de bloques en Y = %d  \n",bloque_y);
//printf("El Tama�o vector del bloque es = %d  \n",bloque_xx*bloque_yy*micelda->orientacion);
	
/*Formo el histograma para cada bloque*/
for(int i=0;i<bloque_y;i++)
	{
		for(int j=0;j<bloque_x;j++)
		{
			for(int ly=0;ly<bloque_yy;ly++)
			{
				for(int lx=0;lx<bloque_xx;lx++)
				{
					for(int k=0;k<micelda->orientacion;k++)
					{
						HsN[micelda->orientacion*(lx+bloque_xx*ly)+k]=micelda->HistCelda[i+ly][j+lx].Hcelda[k];
					}

				}

			}

			float normal=normalizar(HsN);
			//printf("La normal inversa es %f\n",normal);
			for(int ln=0;ln<dim_bloq;ln++){
			V_HOG[dim_bloq*(j+bloque_x*i)+ln]=HsN[ln]*normal; //Concateno los histogramas normalizados (HOG FInal)
			//V_HOG[dim_bloq*(j+bloque_x*i)+ln]=HsN[ln];
			}

		}
	}

/*
for(int i=0;i<dim_bloq;i++){
	//printf(" %f  \n",HsN[i]);	
	//printf("El elemento %d del vector sin normalizar es = %f  \n",i+1,HsN[i]);
		//printf("El elemento %d del vector normalizado es = %f  \n",i+1,HcN[i]);
	}
*/

//IMPRIMIR VECTOR HOG NORMALIZADO
/*
for(int i=0;i<dim_hog;i++){
			printf("El elemento %d del vector HOG es = %f  \n",i+1,V_HOG[i]);
	}
*/



	}

float THOG::normalizar(float *H2){
	
	float sum_H2=0.f;
	for(int k=0;k<dim_bloq;k++)
		sum_H2 += (H2[k]*H2[k]);
		return 1.f/float(sqrt(sum_H2)+0.001);
	}

THOG::~THOG(void){

delete micelda;

}
