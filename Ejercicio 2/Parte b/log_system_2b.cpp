/*
Este código implementa un sistema de registro de eventos en un archivo de log.
La idea principal es clasificar los eventos según su nivel de severidad y guardarlos
en un archivo de texto llamado "log_b.txt". Para ello:

1. Definí un enum NivelSeveridad con diferentes niveles de importancia,
   incluyendo el hardcodeado o personalizado SYSTEM.
2. Creé La función obtenerEtiqueta() devuelve la etiqueta correspondiente a cada nivel.
3. Se sobrecarga la función logMessage() para registrar eventos en diferentes formatos:
   - Con un nivel de severidad estándar.
   - Especificando el archivo y la línea de código donde ocurrió un error.
   - Registrando accesos de usuarios, asumiendo un nivel de seguridad por defecto.
4. En main(), se prueban diferentes registros de eventos, incluyendo errores y accesos de usuarios.
En mi caso, cómo no estaba explicitado cómo hay que testear las funcionalidades, llamé a logMessage con todos los posibles valores de entrada sin intervención de un usuario.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// enum para representar los niveles de severidad de los mensajes de log.
enum NivelSeveridad
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
    SECURITY,
    SYSTEM // Evento propio personalizado
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
    case SECURITY:
        return "SECURITY";
    case SYSTEM:
        return "SYSTEM";
    default:
        return "UNKNOWN"; // para valores inesperados
    }
}

/*
Función que registra un mensaje en un archivo de log.
Los parámetros de la función son el texto del mensaje a registrar y su nivel de severidad
*/
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
        cout << "Error al abrir el archivo de log." << endl;
    }
}

/*
Función sobrecargada para registrar errores con información adicional del archivo y línea.
Los parámetros de la función son el mensaje, el archivo y la línea
*/
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
        cout << "Error al abrir el archivo de log." << endl;
    }
}

/*
Función sobrecargada para registrar accesos de usuarios.
Los parámetros de la función son el mensaje, el usuario y el nivel de seguridad que por defector es SECURIY
*/
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
        cout << "Error al abrir el archivo de log." << endl;
    }
}

int main()
{
    try
    {
        // registro de eventos con distintos niveles de severidad
        logMessage("Este es un mensaje de depuración", DEBUG);
        logMessage("El sistema ha iniciado correctamente", INFO);
        logMessage("Se ha detectado un posible problema", WARNING);
        logMessage("Error al conectar con un servicio", ERROR);
        logMessage("Fallo crítico", CRITICAL);

        // registro de error con detalles del archivo y línea
        logMessage("Archivo de configuración no encontrado", "config.txt", 42);

        // registro de accesos de usuario
        logMessage("Access Granted", "admin");
        logMessage("Access Denied", "hacker123");

        // registro de evento del sistema (evento hardcodeado/personalizado)
        logMessage("Tenemos una actualización de Windows 11 pendiente", SYSTEM);

        // simulación de un error crítico capturado con try-catch
        throw runtime_error("Se ha producido un error crítico en el sistema");
    }
    catch (const exception &e)
    {
        // registro del error en el log con detalles de la línea de código
        logMessage(e.what(), "log_system_2b.cpp", 107);
        cout << "Error en tiempo de ejecución: " << e.what() << endl;
        return 1;
    }

    return 0;
}
