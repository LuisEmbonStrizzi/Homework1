/*

El propósito de este código es implementar un sistema de registro de eventos en un archivo de log.
La idea principal es que los eventos se clasifiquen según su nivel de severidad y se guarden en
un archivo de texto llamado "log_a.txt". Para ello:

1. Definí un enum NivelSeveridad con distintos niveles de importancia de los mensajes.
2. Creé la función obtenerEtiqueta() para obtener la etiqueta correspondiente a cada nivel,
logMessage(), que escribe los mensajes en el archivo de log, agregando su nivel
de severidad al inicio.
4. Finalmente, en el main(), se registran algunos mensajes de prueba con distintos niveles de severidad.
En mi caso, cómo no estaba explicitado cómo hay que testear las funcionalidades, llamé a logMessage con todos los posibles valores de entrada sin intervención de un usuario.

*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
enum para representar los niveles de severidad de los mensajes de log.
*/
enum NivelSeveridad
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

/*
Función que devuelve la etiqueta de texto correspondiente a un nivel de severidad.
Recibe un valor del enum NivelSeveridad y devuelve su representación en string. Para facilitar la implementación decidí utilizar un switch
*/
string obtenerEtiqueta(NivelSeveridad nivel)
{
    switch (nivel)
    {
    case DEBUG:
        return "DEBUG";
    case INFO:
        return "INFO";
    case WARNING:
        return "WARNING";
    case ERROR:
        return "ERROR";
    case CRITICAL:
        return "CRITICAL";
    default:
        return "VALOR INESPERADO"; // en caso de un valor inesperado
    }
}

/*
Función que registra un mensaje en un archivo de log.

Los parámetros de la función son el texto del mensaje a registrar y su nivel de severidad
 */
void logMessage(const string &mensaje, NivelSeveridad nivel)
{
    // abre el archivo en modo de "append" (agregar al final sin sobrescribir).
    ofstream logFile("log_a.txt", ios::app);

    if (logFile.is_open())
    {
        logFile << "[" << obtenerEtiqueta(nivel) << "] " << mensaje << endl;
        logFile.close();

        cout << "Mensaje registrado en el log" << endl;
    }
    else
    {
        cout << "Error al abrir el archivo de log" << endl;
    }
}

int main()
{
    // se registran diferentes mensajes con distintos niveles de severidad.
    logMessage("Este es un mensaje de depuración", DEBUG);
    logMessage("El sistema ha iniciado correctamente", INFO);
    logMessage("Se ha detectado un posible problema", WARNING);
    logMessage("Error al conectar con un servicio", ERROR);
    logMessage("Fallo crítico", CRITICAL);

    return 0;
}
