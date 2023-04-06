cmake_minimum_required(VERSION 3.24)
project(Proyecto_01_SO C)

set(CMAKE_C_STANDARD 11)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0)

include_directories(${GST_INCLUDE_DIRS})
link_directories(${GST_LIBRARY_DIRS})


add_executable(Proyecto_01_SO main.c Archivos/Archivo.h Negocio/LogicaJuego.h Listas/ListaMesa.h Listas/NodoMesa.h Listas/ListaPosibles.h Listas/NodoPosibles.h Sonidos/Sonido.h)
# Specify link libraries
target_link_libraries(Proyecto_01_SO ${GST_LIBRARIES})

