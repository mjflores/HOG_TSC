
#include"guardarArchivo.h"

	
CGuardarArchivo::CGuardarArchivo(char *nombre)
{
	archivo = new ofstream(nombre,ios::app);		
/*
	if( !archivo )
	{
		cerr<<"Error <CGuardarArchivo> No se abrio el archivo de escritura"<<endl;
		getchar();
		exit(-1);
	}
*/
	if(!archivo->is_open())
	{	
		cerr<<"Error <CGuardarArchivo> No esta abierto el archivo de escritura"<<endl;
		getchar();
		exit(-1);
	}
}

CGuardarArchivo::~CGuardarArchivo(void)
{
	archivo->close();
	if( archivo != NULL )
		delete archivo;
}

void CGuardarArchivo::insertarHOG(float *datosFila,int tm,int clase)
{
	*archivo<<clase<<" ";
	int i;
	for(i=0;i<tm;i++)
		*archivo<<i+1<<":"<<datosFila[i]<<" ";
	*archivo<<endl;
}

