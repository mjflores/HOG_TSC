#===================================================
#     Programa para generar caracteristicas HOG

# Aplicacion: Senales de trafico del Ecuador
# Nombre: CaracteristicasHOG_ST

#Version: 1.1
#Autor:   Marco Flores
#         floresmj2@hotmail.com 
#Empresa: Tecnologias I&H

#===================================================

PROJECT(CaracteristicasHOG_ST)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#INCLUDE_DIRECTORIES(${Principal_Segmentacion_SOURCE_DIR})

#La extensión se encuentra automáticamente
ADD_EXECUTABLE(CaracteristicasHOG_ST PrincipalHOG.cpp varios.h direccion.h caracteristicasHOG.h caracteristicasHOG.cpp hog.h hog.cpp svm.h svm.cpp leerCarpeta.h leerCarpeta.cpp guardarArchivo.h guardarArchivo.cpp)
 

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

#Enlaza el ejecutable con la librería
target_link_libraries(CaracteristicasHOG_ST ${OpenCV_LIBS} ) 
#TARGET_LINK_LIBRARIES(EntrenarSenales ${IRRKLANG_LIBRARIES})

