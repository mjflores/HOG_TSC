
#ifndef _LEER_CARPETA_RESIZE_H_
#define _LEER_CARPETA_RESIZE_H_

/*
	Ref:
	http://foro.chuidiang.org/ccplusplus-linux/listar-archivos-dentro-de-un-directorio/
*/

#include"varios.h"

class TLeerCarpeta{

private:

	DIR* directorio;
	struct dirent* elemento;
	struct stat estado;

        string direcCp;
	void leerElemento(void);
public:
	vector<string> ltNomImagenes;

public:

	TLeerCarpeta(string dr);
	~TLeerCarpeta(void);

};

#endif
