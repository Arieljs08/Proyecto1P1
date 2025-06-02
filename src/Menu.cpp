#include "Menu.h"
#include "EntradaDatos.h"
#include "ValidacionFecha.h"
#include "FechaHora.h"
#include "Paciente.h"
#include "ListaDoble.h"
#include "ListaPacientes.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <cstring>


void Menu::mostrarMenu() {
    const char *opciones[] = {
        "Agregar paciente",
        "Agregar turno",
        "Buscar turno por cedula",
        "Eliminar turno",
        "Reemplazar turno",
        "Mostrar todos los turnos",
        "Mostrar todos los pacientes", 
        "Guardar backup",
        "Cargar backup",
        "Mostrar ayuda",
        "Salir"
    };
    int n = 11;
    int seleccion = 0;
    int tecla;

    do {
        system("cls");
        std::cout << "--- MENU DE TURNOS ---\n\n";
        for (int i = 0; i < n; ++i) {
            if (i == seleccion)
                std::cout << " -> ";
            else
                std::cout << "    ";
            std::cout << opciones[i] << "\n";
        }
        tecla = _getch();
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            switch (tecla) {
                case 72: seleccion--; if (seleccion < 0) seleccion = n - 1; break;
                case 80: seleccion++; if (seleccion >= n) seleccion = 0; break;
            }
        } else if (tecla == 13) {
            system("cls");
            std::cout << "Opcion seleccionada: " << opciones[seleccion] << "\n";
            switch (seleccion) {
                case 0: agregarPaciente(); break;
                case 1: agregarTurno(); break;
                case 2: buscarTurno(); break;
                case 3: eliminarTurno(); break;
                case 4: reemplazarTurno(); break;
                case 5: lista.mostrar(); break;
                case 6: mostrarPacientes(); break; 
                case 7: guardarBackup(); break;
                case 8: cargarBackup(); break;
                case 9: mostrarAyuda(); break;
                case 10:
                    std::cout << "Saliendo...\n";
                    return;
                default:
                    std::cout << "Opcion invalida\n";
            }
            system("pause");
        }
    } while (true);
}

// --- Agregar paciente ---
void Menu::agregarPaciente() {
    std::string cedula = validarCedula("Ingrese cédula: ");
    if (pacientes.buscarPorCedula(cedula)) {
        std::cout << "Ya existe un paciente con esa cédula.\n";
        return;
    }
    std::string telefono = validarTelefono("Ingrese teléfono: ");
    std::string nombre = validarNombre("Ingrese nombre: ");
    capitalizar(nombre);
    if (nombre.empty()) {
        std::cout << "Error: El nombre no puede estar vacío.\n";
        return;
    }
    std::string apellido = validarLetras("Ingrese apellido: ");
    capitalizar(apellido);
    if (apellido.empty()) {
        std::cout << "Error: El apellido no puede estar vacío.\n";
        return;
    }
    std::string sexo;
    do {
        sexo = validarLetras("Ingrese sexo (M/F): ");
        std::transform(sexo.begin(), sexo.end(), sexo.begin(), ::toupper);
        if (sexo != "M" && sexo != "F") {
            std::cout << "Error: El sexo debe ser 'M' o 'F'.\n";
        }
    } while (sexo != "M" && sexo != "F");
    std::string correo = validarCorreo("Ingrese correo: ");
    std::string direccion;
    do {
        std::cout << "Ingrese dirección: ";
        std::getline(std::cin, direccion);
        bool tieneEspecial = std::any_of(direccion.begin(), direccion.end(), [](char c) {
            return !isalnum(c) && c != ' ' && c != '#' && c != '-' && c != '.';
        });
        if (direccion.empty()) {
            std::cout << "Error: La dirección no puede estar vacía.\n";
        } else if (tieneEspecial) {
            std::cout << "Error: La dirección contiene caracteres inválidos.\n";
            direccion.clear();
        }
    } while (direccion.empty());

    Paciente* paciente = new Paciente(nombre, apellido, cedula, direccion, correo, telefono, sexo);
    pacientes.agregar(paciente);
    std::cout << "Paciente agregado correctamente.\n";
}

// --- Agregar turno solo para pacientes ya registrados ---
void Menu::agregarTurno() {
    std::string cedula = validarCedula("Ingrese cédula del paciente: ");
    Paciente* paciente = pacientes.buscarPorCedula(cedula);
    if (!paciente) {
        std::cout << "No existe un paciente con esa cédula. Debe agregarlo primero.\n";
        return;
    }
    std::string provincia = validarProvincia("Ingrese provincia: ");
    std::string ciudad = validarCiudad("Ingrese ciudad: ");

    int dia = -1, mes = -1, anio = -1, hora = -1, minuto = -1;
    FechaHora fecha;
    do {
        do {
            std::string input = validarNumeros("Ingrese año (>=2024): ");
            try {
                anio = std::stoi(input);
                if (!validarYear(anio) || anio < 2024) {
                    std::cout << "Error: El año debe ser 2024 o mayor.\n";
                    anio = -1;
                }
            } catch (...) {
                std::cout << "Error: Ingrese solo números.\n";
                anio = -1;
            }
        } while (anio == -1);

        do {
            std::string input = validarNumeros("Ingrese mes (1-12): ");
            try {
                mes = std::stoi(input);
                if (!validarMes(mes)) {
                    std::cout << "Error: El mes debe estar entre 1 y 12.\n";
                    mes = -1;
                }
            } catch (...) {
                std::cout << "Error: Ingrese solo números.\n";
                mes = -1;
            }
        } while (mes == -1);

        do {
            std::string input = validarNumeros("Ingrese el día (1-31): ");
            try {
                dia = std::stoi(input);
                if (!validarDia(dia, mes, anio)) {
                    std::cout << "Día inválido para ese mes y año.\n";
                    dia = -1;
                }
            } catch (...) {
                std::cout << "Error: Ingrese solo números.\n";
                dia = -1;
            }
        } while (dia == -1);

        fecha.setFechaHora(dia, mes, anio, 0, 0);
        if (fecha.esNoValida()) {
            std::cout << "Fecha inválida: ya pasó o es feriado.\n";
        }
    } while (fecha.esNoValida());

    hora = validarHora("Ingrese la hora (0-23): ");
    minuto = validarMinuto("Ingrese el minuto (0-59): ");
    fecha.setFechaHora(dia, mes, anio, hora, minuto);

    if (fecha.esNoValida()) {
        std::cout << "Fecha y hora inválida: ya pasó.\n";
        return;
    }

    if (lista.existeTurno(dia, mes, anio, hora, minuto, provincia, ciudad)) {
        std::cout << "Ya existe un turno en esa fecha, hora y provincia\n";
        return;
    }

    Turno* turno = new Turno(*paciente, fecha, provincia, ciudad);
    lista.agregar(turno);
    std::cout << "Turno agregado correctamente.\n";
}

// --- Buscar turno ---
void Menu::buscarTurno() {
    std::string cedula = validarNumeros("Ingrese cedula para buscar: ");
    Turno* turnoPtr = lista.buscarPorCedula(cedula);
    if (turnoPtr) {
        turnoPtr->mostrar();
    } else {
        std::cout << "Turno no encontrado.\n";
    }
}

// --- Eliminar turno ---
void Menu::eliminarTurno() {
    std::string cedula = validarNumeros("Ingrese cedula para eliminar: ");
    if (lista.eliminarPorCedula(cedula)) {
        std::cout << "Turno eliminado.\n";
    } else {
        std::cout << "No se encontro turno con esa cedula.\n";
    }
}

// --- Reemplazar turno (solo datos del turno, no del paciente) ---
void Menu::reemplazarTurno() {
    std::string cedula = validarCedula("Ingrese cedula del turno a reemplazar: ");
    Turno* turnoPtr = lista.buscarPorCedula(cedula);
    if (!turnoPtr) {
        std::cout << "No se encontro turno con esa cedula.\n";
        return;
    }
    std::string provincia = validarProvincia("Ingrese nueva provincia: ");
    std::string ciudad = validarCiudad("Ingrese nueva ciudad: ");

    int dia = -1, mes = -1, anio = -1, hora = -1, minuto = -1;
    FechaHora fecha;
    do {
        do {
            std::string input = validarNumeros("Ingrese año (>=2024): ");
            try {
                anio = std::stoi(input);
                if (!validarYear(anio) || anio < 2024) {
                    std::cout << "Error: El año debe ser 2024 o mayor.\n";
                    anio = -1;
                }
            } catch (...) {
                std::cout << "Error: Ingrese solo números.\n";
                anio = -1;
            }
        } while (anio == -1);

        do {
            std::string input = validarNumeros("Ingrese mes (1-12): ");
            try {
                mes = std::stoi(input);
                if (!validarMes(mes)) {
                    std::cout << "Error: El mes debe estar entre 1 y 12.\n";
                    mes = -1;
                }
            } catch (...) {
                std::cout << "Error: Ingrese solo números.\n";
                mes = -1;
            }
        } while (mes == -1);

        do {
            std::string input = validarNumeros("Ingrese el día (1-31): ");
            try {
                dia = std::stoi(input);
                if (!validarDia(dia, mes, anio)) {
                    std::cout << "Día inválido para ese mes y año.\n";
                    dia = -1;
                }
            } catch (...) {
                std::cout << "Error: Ingrese solo números.\n";
                dia = -1;
            }
        } while (dia == -1);

        fecha.setFechaHora(dia, mes, anio, 0, 0);
        if (fecha.esNoValida()) {
            std::cout << "Fecha inválida: ya pasó o es feriado.\n";
        }
    } while (fecha.esNoValida());

    hora = validarHora("Ingrese la hora (0-23): ");
    minuto = validarMinuto("Ingrese el minuto (0-59): ");
    fecha.setFechaHora(dia, mes, anio, hora, minuto);

    if (fecha.esNoValida()) {
        std::cout << "Fecha y hora inválida: ya pasó.\n";
        return;
    }

    if (lista.existeTurno(dia, mes, anio, hora, minuto, provincia, ciudad)) {
        std::cout << "Ya existe un turno en esa fecha, hora y provincia\n";
        return;
    }

    lista.reemplazarDatosTurnoPorCedula(cedula, fecha, provincia, ciudad);
    std::cout << "Datos del turno reemplazados correctamente.\n";
}

// --- Backup general (turno + paciente) ---
void Menu::guardarBackup() {
    std::string ruta;
    std::cout << "Ingrese la ruta completa donde desea guardar el backup (ej. C:\\\\Users\\\\TuNombre\\\\Desktop\\\\backup.bin):\n";
    std::getline(std::cin, ruta);

    std::ofstream archivo(ruta, std::ios::binary);
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo para guardar.\n";
        return;
    }

    Nodo* actual = lista.getCabeza();
    while (actual != nullptr) {
        Turno* t = actual->dato;
        Paciente p = t->getPaciente();
        FechaHora f = t->getFechaHora();

        archivo.write(reinterpret_cast<char*>(&f), sizeof(FechaHora));
        archivo.write(p.getNombre().c_str(), p.getNombre().size() + 1);
        archivo.write(p.getApellido().c_str(), p.getApellido().size() + 1);
        archivo.write(p.getCedula().c_str(), p.getCedula().size() + 1);
        archivo.write(p.getDireccion().c_str(), p.getDireccion().size() + 1);
        archivo.write(p.getCorreo().c_str(), p.getCorreo().size() + 1);
        archivo.write(p.getTelefono().c_str(), p.getTelefono().size() + 1);
        archivo.write(p.getSexo().c_str(), p.getSexo().size() + 1);
        archivo.write(t->getProvincia().c_str(), t->getProvincia().size() + 1);
        archivo.write(t->getCiudad().c_str(), t->getCiudad().size() + 1);

        actual = actual->siguiente;
    }

    archivo.close();
    std::cout << "Backup guardado correctamente.\n";
}

void Menu::cargarBackup() {
    std::string ruta;
    std::cout << "Ingrese la ruta completa del archivo de backup a recuperar:\n";
    std::getline(std::cin, ruta);

    std::ifstream archivo(ruta, std::ios::binary);
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo para leer.\n";
        return;
    }

    lista = ListaDoble(); // Limpia la lista actual

    while (archivo.peek() != EOF) {
        FechaHora fecha;
        archivo.read(reinterpret_cast<char*>(&fecha), sizeof(FechaHora));

        std::string nombre, apellido, cedula, direccion, correo, telefono, sexo, provincia, ciudad;

        std::getline(archivo, nombre, '\0');
        std::getline(archivo, apellido, '\0');
        std::getline(archivo, cedula, '\0');
        std::getline(archivo, direccion, '\0');
        std::getline(archivo, correo, '\0');
        std::getline(archivo, telefono, '\0');
        std::getline(archivo, sexo, '\0');
        std::getline(archivo, provincia, '\0');
        std::getline(archivo, ciudad, '\0');

        Paciente* p = new Paciente(nombre, apellido, cedula, direccion, correo, telefono, sexo);
        Turno* t = new Turno(*p, fecha, provincia, ciudad);
        lista.agregar(t);

        // Opcional: sincronizar lista de pacientes
        if (!pacientes.buscarPorCedula(cedula)) {
            pacientes.agregar(new Paciente(nombre, apellido, cedula, direccion, correo, telefono, sexo));
        }
    }

    archivo.close();
    std::cout << "Backup restaurado correctamente.\n";
}

// --- Mostrar ayuda ---
void Menu::mostrarAyuda() {
    std::cout << "----- AYUDA DEL SISTEMA DE TURNOS MEDICOS -----\n";
    std::cout << "1. Agregar paciente: Registra los datos de un paciente.\n";
    std::cout << "2. Agregar turno: Solo para pacientes ya registrados.\n";
    std::cout << "3. Buscar turno: Busca un turno por cédula.\n";
    std::cout << "4. Eliminar turno: Elimina un turno por cédula.\n";
    std::cout << "5. Reemplazar turno: Cambia la fecha, hora, provincia o ciudad de un turno.\n";
    std::cout << "6. Mostrar todos los turnos: Lista todos los turnos agendados.\n";
    std::cout << "7. Guardar backup: Guarda todos los turnos y pacientes en un archivo .bin.\n";
    std::cout << "8. Cargar backup: Recupera los turnos y pacientes desde un archivo .bin.\n";
    std::cout << "9. Salir: Cierra el programa.\n";
}

// --- Capitalizar nombres ---
void Menu::capitalizar(std::string& texto) {
    std::transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
    if (!texto.empty())
        texto[0] = ::toupper(texto[0]);
    for (size_t i = 1; i < texto.length(); ++i) {
        if (texto[i - 1] == ' ')
            texto[i] = ::toupper(texto[i]);
    }
}

// --- Mostrar todos los pacientes ---
void Menu::mostrarPacientes() {
    std::cout << "----- LISTA DE PACIENTES REGISTRADOS -----\n";
    pacientes.mostrar(); 
}
