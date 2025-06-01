#ifndef FECHAHORA_H
#define FECHAHORA_H

/// @file FechaHora.h
/// @brief Clase para representar y validar fechas y horas.

class FechaHora {
private:
    int dia, mes, anio, hora, minuto;
public:
    FechaHora();
    FechaHora(int d, int m, int a, int h, int min);

    void setFechaHora(int d, int m, int a, int h, int min);

    int getDia() const;
    int getMes() const;
    int getAnio() const;
    int getHora() const;
    int getMinuto() const;

    bool esPasada() const;
    bool esNoValida() const;

    void mostrar() const;
};

#endif