
#include "caracteristicasHOG.h"
#include "leerCarpeta.h"


int main(void)
{

     printf("\tEntrenamiento de HOG con SVM para reconocimiento de\n");
     printf("\tsenales de trafico\n");

     TCaracteristicasHOG caracteristicasHOG;
     caracteristicasHOG.hogCedaPaso(); //Obtiene parametro HOG para ceda el paso
     
//     caracteristicasHOG.hogPare();     //Obtiene parametros HOG para pare

/*
     TLeerCarpeta leer("/home/deee/Documentos/Mi BaseDatos/Imagenes/BD_Regulatorias/");

	for(int i = 0; i< (int)leer.ltNomImagenes.size();i++)
		printf("Q sale %d: %s\n",i,leer.ltNomImagenes[i].c_str());
	printf("Tamano: %d\n",(int)leer.ltNomImagenes.size());	
*/
       return 0;	
}
