#ifndef MENU_H
#define MENU_H

/// @file Menu.h
/// @brief Clase que gestiona la interfaz de usuario para agendar turnos.

#include "ListaDoble.h"
#include "Turno.h"
#include "Paciente.h"

class Menu {
private:
    ListaDoble lista;  ///< Lista de turnos médicos.
public:
    void mostrarMenu();
    void agregarTurno();
    void buscarTurno();
    void eliminarTurno();
    void reemplazarTurno();
    void guardarBackup();
    void cargarBackup();
    void mostrarAyuda();
    void capitalizar(std::string& nom);
};

#endif // MENU_H