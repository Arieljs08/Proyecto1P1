// ValidacionFecha.h
#ifndef VALIDACION_FECHA_H
#define VALIDACION_FECHA_H

/// @file ValidacionFecha.h
/// @brief Funciones para validación de fechas incluyendo feriados y años bisiestos.

#include "ConfigDLL.h"

#ifdef __cplusplus
extern "C" {
#endif

    DLL_EXPORT bool esBisiesto(int year);                       ///< Verifica si un año es bisiesto.
    DLL_EXPORT bool esFeriado(int day, int month, int year);    ///< Verifica si una fecha es feriado.
    DLL_EXPORT bool validarFecha(int dia, int mes, int anio);   ///< Valida una fecha completa.
    DLL_EXPORT bool esNumero(const char* texto);                ///< Verifica si un texto es numérico.

#ifdef __cplusplus
}
#endif

#endif