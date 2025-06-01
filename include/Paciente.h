#ifndef PACIENTE_H
#define PACIENTE_H

/// @file Paciente.h
/// @brief Clase que representa a un paciente.

#include <string>

class Paciente {
private:
    std::string nombre;
    std::string apellido;
    std::string cedula;
    std::string direccion;
    std::string correo;
    std::string telefono;
    std::string sexo;

public:
    Paciente(const std::string& nombre, const std::string& apellido, const std::string& cedula,
             const std::string& direccion, const std::string& correo,
             const std::string& telefono, const std::string& sexo);

    ~Paciente();

    std::string getNombre() const;
    std::string getApellido() const;
    std::string getCedula() const;
    std::string getDireccion() const;
    std::string getCorreo() const;
    std::string getTelefono() const;
    std::string getSexo() const;

    void mostrar() const;
};

#endif