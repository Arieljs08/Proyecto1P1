@echo off
cls
echo ===========================================
echo     INSTALADOR DEL SISTEMA DE TURNOS
echo ===========================================

:: Crear carpeta bin si no existe
if not exist "bin" mkdir bin

echo.
echo Compilando programa...
g++ -o bin\main.exe ^
src\main.cpp src\Menu.cpp src\ListaDoble.cpp src\listaPacientes.cpp ^
src\FechaHora.cpp src\Paciente.cpp src\Turno.cpp ^
-Iinclude ^
-Lbin -lValidarEntrada -lvalidarFeriado

if %errorlevel% neq 0 (
    echo ERROR: Fallo la compilacion.
    pause
    exit /b
)

echo.
echo Copiando DLLs necesarias...
copy /Y ValidarEntrada.dll bin\
copy /Y validarFeriado.dll bin\

echo.
echo Instalacion completada con exito.
echo.

echo ===========================================
echo      CODIGOS DE LICENCIA GENERADOS
echo ===========================================
echo.

setlocal EnableDelayedExpansion

set "chars=0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
for /L %%j in (1,1,5) do (
    echo Codigo %%j

    set "part1="
    for /L %%i in (1,1,4) do (
        set /a "rand=!random! %% 36"
        for %%r in (!rand!) do set "part1=!part1!!chars:~%%r,1!"
    )

    set "part2="
    for /L %%i in (1,1,4) do (
        set /a "rand=!random! %% 36"
        for %%r in (!rand!) do set "part2=!part2!!chars:~%%r,1!"
    )

    set "part3="
    for /L %%i in (1,1,4) do (
        set /a "rand=!random! %% 36"
        for %%r in (!rand!) do set "part3=!part3!!chars:~%%r,1!"
    )

    echo !part1!-!part2!-!part3!
)

echo.
echo ===========================================
echo Guarda tus codigos para activacion/registro.
echo ===========================================
echo.
REM Ejecutar el programa compilado
echo Ejecutando el sistema...
cd bin
start main.exe
cd ..
pause