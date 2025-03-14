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
    CRITICAL,
    SECURITY
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
    case SECURITY:
        return "SECURITY";
    default:
        return "UNKNOWN";
    }
}

void logMessage(const string &mensaje, NivelSeveridad nivel)
{
    ofstream logFile("log_b.txt", ios::app);
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

void logMessage(const string &mensaje, const string &archivo, int linea)
{
    ofstream logFile("log_b.txt", ios::app);
    if (logFile.is_open())
    {
        logFile << "[ERROR] " << mensaje << " | Archivo: " << archivo << " | Línea: " << linea << endl;
        logFile.close();
        cout << "Error registrado en el log." << endl;
    }
    else
    {
        cerr << "Error al abrir el archivo de log." << endl;
    }
}

void logMessage(const string &mensaje, const string &usuario, NivelSeveridad nivel = SECURITY)
{
    ofstream logFile("log_b.txt", ios::app);
    if (logFile.is_open())
    {
        logFile << "[" << obtenerEtiqueta(nivel) << "] Usuario: " << usuario << " - " << mensaje << endl;
        logFile.close();
        cout << "Acceso de usuario registrado en el log." << endl;
    }
    else
    {
        cerr << "Error al abrir el archivo de log." << endl;
    }
}

int main()
{
    try
    {
        logMessage("Este es un mensaje de depuración", DEBUG);
        logMessage("El sistema ha iniciado correctamente", INFO);
        logMessage("Se ha detectado un posible problema", WARNING);
        logMessage("Error al conectar con la base de datos", ERROR);
        logMessage("Fallo crítico: el sistema debe reiniciarse", CRITICAL);

        logMessage("Archivo de configuración no encontrado", "config.txt", 42);

        logMessage("Access Granted", "admin");
        logMessage("Access Denied", "hacker123");

        throw runtime_error("Se ha producido un error crítico en el sistema");
    }
    catch (const exception &e)
    {
        logMessage(e.what(), __FILE__, __LINE__);
        cerr << "Error en tiempo de ejecución: " << e.what() << endl;
        return 1;
    }

    return 0;
}
