
#include"leerCarpeta.h"

TLeerCarpeta::TLeerCarpeta(string dr)
{
		direcCp = dr;
		directorio=opendir(direcCp.c_str());
		if (directorio==NULL)
		{   
			printf ("<TLeerCarpeta>: Error de Lectura en el Directorio \n");
			exit(-1);
		}

		 elemento = readdir(directorio);	
		 
		 leerElemento();	
}

void TLeerCarpeta::leerElemento(void)
{
		int i=1;
		string direc;

		while (elemento!=NULL) 
		{
			if (stat(elemento->d_name, &estado)!=0) 
			{		 

		  direc = direcCp + elemento->d_name;
		  /*
		   Mat  imgOrg = imread(direc);
	 	      imshow("ImgOrg",imgOrg);
	 		if(cvWaitKey(100) ==27) 
			     break;
		  */
		  ltNomImagenes.push_back(direc);

		}
			   
			elemento=readdir(directorio);
		} 
}

TLeerCarpeta::~TLeerCarpeta(void)
{
		if(directorio != NULL)
			closedir(directorio);
}
