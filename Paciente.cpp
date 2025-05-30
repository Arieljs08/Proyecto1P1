#include "Paciente.h"
#include <iostream>

Paciente::Paciente(const std::string& nombre,
                   const std::string& apellido,
                   const std::string& cedula,
                   const std::string& direccion,
                   const std::string& correo,
                   const std::string& telefono,
                   const std::string& sexo)
    : nombre(nombre), apellido(apellido), cedula(cedula),
      direccion(direccion), correo(correo), telefono(telefono), sexo(sexo) {}

Paciente::~Paciente() {

}

std::string Paciente::getNombre() const { return nombre; }
std::string Paciente::getApellido() const { return apellido; }
std::string Paciente::getCedula() const { return cedula; }
std::string Paciente::getDireccion() const { return direccion; }
std::string Paciente::getCorreo() const { return correo; }
std::string Paciente::getTelefono() const { return telefono; }
std::string Paciente::getSexo() const { return sexo; }

void Paciente::mostrar() const {
    std::cout << "Cédula     : " << cedula << "\n";
    std::cout << "Nombre     : " << nombre << " " << apellido << "\n";
    std::cout << "Dirección  : " << direccion << "\n";
    std::cout << "Correo     : " << correo << "\n";
    std::cout << "Teléfono   : " << telefono << "\n";
    std::cout << "Sexo       : " << sexo << "\n";
    std::cout << "-------------------------------------\n";
}
