#include "FechaHora.h"
#include "ValidacionFecha.h"
#include <iostream>
#include <ctime>

FechaHora::FechaHora() : dia(0), mes(0), anio(0), hora(0), minuto(0) {}

FechaHora::FechaHora(int d, int m, int a, int h, int min)
    : dia(d), mes(m), anio(a), hora(h), minuto(min) {}

void FechaHora::setFechaHora(int d, int m, int a, int h, int min) {
    
    dia = d;
    mes = m;
    anio = a;
    hora = h;
    minuto = min;
}

int FechaHora::getDia() const { return dia; }
int FechaHora::getMes() const { return mes; }
int FechaHora::getAnio() const { return anio; }
int FechaHora::getHora() const { return hora; }
int FechaHora::getMinuto() const { return minuto; }

bool FechaHora::esPasada() const {
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    int actualDia = now->tm_mday;
    int actualMes = now->tm_mon + 1;
    int actualAnio = now->tm_year + 1900;
    int actualHora = now->tm_hour;       //Biblioteca 
    int actualMinuto = now->tm_min;

    if (anio < actualAnio) return true;
    if (anio == actualAnio && mes < actualMes) return true;
    if (anio == actualAnio && mes == actualMes && dia < actualDia) return true;

    if (anio == actualAnio && mes == actualMes && dia == actualDia) {
        if (hora < actualHora) return true;
        if (hora == actualHora && minuto <= actualMinuto) return true;
    }

    return false;
}

bool FechaHora::esNoValida() const {
    return esPasada() || esFeriado(dia, mes, anio);  //VALIDACIONES
}

void FechaHora::mostrar() const {
    std::cout << (dia < 10 ? "0" : "") << dia << "/"
              << (mes < 10 ? "0" : "") << mes << "/"
              << anio << " "
              << (hora < 10 ? "0" : "") << hora << ":"
              << (minuto < 10 ? "0" : "") << minuto;
}
