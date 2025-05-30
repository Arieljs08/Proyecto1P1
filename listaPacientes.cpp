#include "ListaPacientes.h"
#include <iostream>

ListaPacientes::ListaPacientes() : cabeza(nullptr) {}

ListaPacientes::~ListaPacientes() {
    NodoPaciente* actual = cabeza;
    while (actual != nullptr) {
        NodoPaciente* siguiente = actual->siguiente;
        delete actual->dato;
        delete actual;
        actual = siguiente;
    }
}

void ListaPacientes::agregar(Paciente* p) {
    if (buscarPorCedula(p->getCedula()) != nullptr) {
        std::cerr << "Error: Ya existe un paciente con la cédula " << p->getCedula() << std::endl;
        delete p;
        return;
    }
    NodoPaciente* nuevo = new NodoPaciente(p);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

Paciente* ListaPacientes::buscarPorCedula(const std::string& cedula) {
    NodoPaciente* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato->getCedula() == cedula) {
            return actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void ListaPacientes::mostrar() {
    NodoPaciente* actual = cabeza;
    while (actual != nullptr) {
        actual->dato->mostrar();
        actual = actual->siguiente;
    }
}