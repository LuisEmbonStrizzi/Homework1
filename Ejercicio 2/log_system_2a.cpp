#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum NivelSeveridad
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

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
        return "UNKNOWN";
    }
}

void logMessage(const string &mensaje, NivelSeveridad nivel)
{
    ofstream logFile("log_a.txt", ios::app);
    if (logFile.is_open())
    {
        logFile << "[" << obtenerEtiqueta(nivel) << "] " << mensaje << endl;
        logFile.close();
        cout << "Mensaje registrado en el log." << endl;
    }
    else
    {
        cerr << "Error al abrir el archivo de log." << endl;
    }
}

int main()
{
    logMessage("Este es un mensaje de depuración", DEBUG);
    logMessage("El sistema ha iniciado correctamente", INFO);
    logMessage("Se ha detectado un posible problema", WARNING);
    logMessage("Error al conectar con un servicio", ERROR);
    logMessage("Fallo crítico", CRITICAL);

    return 0;
}
