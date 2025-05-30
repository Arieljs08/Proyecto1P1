// ListaDoble.h
#ifndef LISTADOBLE_H
#define LISTADOBLE_H

/// @file ListaDoble.h
/// @brief Lista doblemente enlazada de turnos médicos.

#include <string>
#include <iostream>
#include "Nodo.h"
#include "FechaHora.h"
#include "Turno.h"

class ListaDoble {
private:
    Nodo* cabeza;   ///< Puntero al primer nodo de la lista.
    Nodo* cola;     ///< Puntero al último nodo de la lista.
    int size;       ///< Cantidad de elementos en la lista.

public:
    ListaDoble();
    ~ListaDoble();

    void agregar(Turno* dato);
    bool eliminarPorCedula(const std::string& cedula);
    Turno* buscarPorCedula(const std::string& cedula);
    bool reemplazarPorCedula(const std::string& cedula, Turno* nuevoDato);
    void mostrar();
    Nodo* getCabeza();
    bool existeTurno(int dia, int mes, int anio, int hora, int minuto, const std::string& provincia, const std::string& ciudad);
    int getSize() const;
    void guardarBackup(const std::string& archivo);
    void cargarBackup(const std::string& archivo);
    
};

#endif
