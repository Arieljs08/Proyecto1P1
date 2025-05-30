// ConfigDLL.h
#ifndef CONFIG_DLL_H
#define CONFIG_DLL_H

/// @file ConfigDLL.h
/// @brief Define macros para exportar funciones desde DLLs en diferentes plataformas.

#ifdef _WIN32
#ifdef BUILDING_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

#endif