#include "Menu.h"
#include "EntradaDatos.h"
#include "ValidacionFecha.h"
#include "FechaHora.h"
#include "Paciente.h"
#include "ListaDoble.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <cstring>


void Menu::mostrarMenu() {
    const char *opciones[] = {
        "Agregar turno",
        "Buscar turno por cedula",
        "Eliminar turno",
        "Reemplazar turno",
        "Mostrar todos los turnos",
        "Guardar  backup",
        "Cargar backup",
        "Mostrar ayuda",
        "Salir"
    };
    int n = 9;
    int seleccion = 0;
    int tecla;

    do {
        system("cls");  // limpia pantalla (en Windows)
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
                case 72:  // flecha arriba
                    seleccion--;
                    if (seleccion < 0) seleccion = n - 1;
                    break;
                case 80:  // flecha abajo
                    seleccion++;
                    if (seleccion >= n) seleccion = 0;
                    break;
            }
        } else if (tecla == 13) {  // ENTER
            system("cls");
            std::cout << "Opcion seleccionada: " << opciones[seleccion] << "\n";
            switch (seleccion) {
                case 0: agregarTurno(); break;
                case 1: buscarTurno(); break;
                case 2: eliminarTurno(); break;
                case 3: reemplazarTurno(); break;
                case 4: lista.mostrar(); break;
                case 5: guardarBackup(); break;
                case 6: cargarBackup(); break;
                case 7: mostrarAyuda(); break;
                case 8: 
                    std::cout << "Saliendo...\n";
                    return;
                default:
                    std::cout << "Opcion invalida\n";
            }
            system("pause");
        }

    } while (true);
}

void Menu::agregarTurno() {
    std::cin.ignore();
    std::string cedula    = std::string(validarCedula("Ingrese cédula: "));
    std::string telefono  = std::string(validarTelefono("Ingrese teléfono: "));
    std::string nombre    = std::string(validarNombre("Ingrese nombre: "));
    capitalizar(nombre);
    if (nombre.empty()) {
        std::cout << "Error: El nombre no puede estar vacío.\n";
        return;
    }
    std::string apellido  = std::string(validarLetras("Ingrese apellido: "));
    capitalizar(apellido);
    if (apellido.empty()) {
        std::cout << "Error: El apellido no puede estar vacío.\n";
        return;
    }
    std::string sexo;
    do {
        sexo = std::string(validarLetras("Ingrese sexo (M/F): "));
        if (sexo != "M" && sexo != "F") {
            std::cout << "Error: El sexo debe ser 'M' o 'F'.\n";
        }
    } while (sexo != "M" && sexo != "F");	
    std::string provincia = std::string(validarProvincia("Ingrese provincia: "));
    std::string ciudad    = std::string(validarCiudad("Ingrese ciudad: "));
    std::string correo    = std::string(validarCorreo("Ingrese correo: "));

    std::string direccion;
    do {
        std::cout << "Ingrese dirección: ";
        std::getline(std::cin, direccion);
        if (direccion.empty()) std::cout << "Error: La dirección no puede estar vacía.\n";
    } while (direccion.empty());

    int dia, mes, anio, hora, minuto;
    const char* input;

    do {
        input = validarNumeros("Ingrese día: ");
    } while (!esNumero(input));
    dia = std::stoi(input);

    do {
        input = validarNumeros("Ingrese mes: ");
    } while (!esNumero(input));
    mes = std::stoi(input);

    do {
        input = validarNumeros("Ingrese año: ");
    } while (!esNumero(input));
    anio = std::stoi(input);


    FechaHora fecha(dia, mes, anio, 0, 0);
    if (fecha.esNoValida()) {
        std::cout << "Fecha invalida: pasada o feriado\n";
        return;
    }

    hora = validarHora("Ingrese hora (0-23): ");
    minuto = validarMinuto("Ingrese minuto (0-59): ");


    fecha.setFechaHora(dia, mes, anio, hora, minuto);	

    if (lista.existeTurno(dia, mes, anio, hora, minuto, provincia, ciudad)) {
        std::cout << "Ya existe un turno en esa fecha, hora y provincia\n";
        return;
    }

    Paciente* paciente = new Paciente(
        nombre.c_str(),
        apellido.c_str(),
        cedula.c_str(),
        direccion.c_str(),
        correo.c_str(),
        telefono.c_str(),
        sexo.c_str()
    );
    Turno* turno = new Turno(*paciente, fecha, provincia, ciudad);
    lista.agregar(turno);

    std::cout << "Turno agregado correctamente.\n";
}

void Menu::buscarTurno() {
    std::string cedula = validarNumeros("Ingrese cedula para buscar: ");
    Turno* turnoPtr = lista.buscarPorCedula(cedula);
    if (turnoPtr) {
        turnoPtr->mostrar();
    } else {
        std::cout << "Turno no encontrado.\n";
    }
}

void Menu::eliminarTurno() {
    std::string cedula = validarNumeros("Ingrese cedula para eliminar: ");
    if (lista.eliminarPorCedula(cedula)) {
        std::cout << "Turno eliminado.\n";
    } else {
        std::cout << "No se encontro turno con esa cedula.\n";
    }
}

void Menu::reemplazarTurno() {
    std::string cedula = validarNumeros("Ingrese cedula del turno a reemplazar: ");
    Turno* turnoPtr = lista.buscarPorCedula(cedula);
    if (!turnoPtr) {
        std::cout << "No se encontro turno con esa cedula.\n";
        return;
    }

    std::cout << "Ingrese nuevos datos:\n";

    std::string nuevacedula    = std::string(validarCedula("Ingrese cédula: "));
    std::string telefono  = std::string(validarTelefono("Ingrese teléfono: "));
    std::string nombre    = std::string(validarNombre("Ingrese nombre: "));
    capitalizar(nombre);
    if (nombre.empty()) {
        std::cout << "Error: El nombre no puede estar vacío.\n";
        return;
    }
    std::string apellido  = std::string(validarLetras("Ingrese apellido: "));
    capitalizar(apellido);
    if (apellido.empty()) {
        std::cout << "Error: El apellido no puede estar vacío.\n";
        return;
    }
    std::string sexo      = std::string(validarLetras("Ingrese sexo: "));
    std::string provincia = std::string(validarProvincia("Ingrese provincia: "));
    std::string ciudad    = std::string(validarCiudad("Ingrese ciudad: "));
    std::string correo    = std::string(validarCorreo("Ingrese correo: "));
    std::string direccion;
    do {
        std::cout << "Ingrese direccion: ";
        std::getline(std::cin, direccion);
        if (direccion.empty()) std::cout << "Error: La dirección no puede estar vacía.\n";
    } while (direccion.empty());

    int dia, mes, anio, hora, minuto;
    const char* input;

    do {
        input = validarNumeros("Ingrese día: ");
    } while (!esNumero(input));
    dia = std::stoi(input);

    do {
        input = validarNumeros("Ingrese mes: ");
    } while (!esNumero(input));
    mes = std::stoi(input);

    do {
        input = validarNumeros("Ingrese año: ");
    } while (!esNumero(input));
    anio = std::stoi(input);


    FechaHora fecha(dia, mes, anio, 0, 0);
    if (fecha.esNoValida()) {
        std::cout << "Fecha invalida: pasada o feriado\n";
        return;
    }

    hora = validarHora("Ingrese hora (0-23): ");
    minuto = validarMinuto("Ingrese minuto (0-59): ");


    fecha.setFechaHora(dia, mes, anio, hora, minuto);

    if (lista.existeTurno(dia, mes, anio, hora, minuto, provincia, ciudad)) {
        std::cout << "Ya existe un turno en esa fecha, hora y provincia\n";
        return;
    }

    Paciente* paciente = new Paciente(
        nombre.c_str(),
        apellido.c_str(),
        cedula.c_str(),
        direccion.c_str(),
        correo.c_str(),
        telefono.c_str(),
        sexo.c_str()
    );
    Turno* turno = new Turno(*paciente, fecha, provincia, ciudad);
    lista.reemplazarPorCedula(cedula, turno);

    std::cout << "Turno reemplazado correctamente.\n";
}

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
    }

    archivo.close();
    std::cout << "Backup restaurado correctamente.\n";
}

void Menu::mostrarAyuda() {
    std::cout << "----- AYUDA DEL SISTEMA DE TURNOS MEDICOS -----\n";
    std::cout << "1. Agregar turno: Ingrese los datos del paciente y la fecha deseada.\n";
    std::cout << "2. Buscar turno: Permite buscar un turno por número de cédula.\n";
    std::cout << "3. Eliminar turno: Elimina un turno ingresando la cédula del paciente.\n";
    std::cout << "4. Reemplazar turno: Modifica un turno existente por uno nuevo.\n";
    std::cout << "5. Mostrar todos los turnos: Muestra todos los turnos agendados.\n";
    std::cout << "6. Guardar backup: Guarda todos los turnos en un archivo .bin.\n";
    std::cout << "7. Cargar backup: Recupera los turnos previamente guardados.\n";
    std::cout << "8. Salir: Cierra el programa.\n";
}

void Menu::capitalizar(std::string& texto) {
    std::transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
    if (!texto.empty())
        texto[0] = ::toupper(texto[0]);
    for (size_t i = 1; i < texto.length(); ++i) {
        if (texto[i - 1] == ' ')
            texto[i] = ::toupper(texto[i]);
    }
}
