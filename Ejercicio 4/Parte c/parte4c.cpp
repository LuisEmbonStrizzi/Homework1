#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono; 
/*
Función constexpr que compara dos cadenas de caracteres en tiempo de compilación.
Los parámetros que recibe son dos cadenas y el índice actual en la comparación (por defecto inicia en 0).
Devueve true si las cadenas son iguales, false en caso contrario.
*/

constexpr bool compararRecursivoCompilacion(const char *s1, const char *s2, int index = 0)
{
    if (s1[index] != s2[index]) // si los caracteres en la posición actual son diferentes, retorna false.
    {
        return false;
    }

    if (s1[index] == '\0') // si se llega al final de ambas cadenas, significa que son iguales.
    // Digo que llego al final de ambas cadenas porque si una cadena es más corta que la otra, el '\0' aparecerá primero en una de ellas, lo que provocará que s1[index] != s2[index] y este es el if anterior
    {
        return true;
    }

    return compararRecursivoCompilacion(s1, s2, index + 1); // llamado recursivo para comparar el siguiente carácter.
}

constexpr const char texto1[] = "En abril de 1784, cuando tenía seis años, llegó con su familia a la ciudad española de Cádiz –previa estadía en Buenos Aires– y se radicó luego en la ciudad de Málaga.​";
constexpr const char texto2[] = "En abril de 1784, cuando tenía seis años, llegó con su familia a la ciudad española de Cádiz –previa estadía en Buenos Aires– y se radicó luego en la ciudad de Málaga.​";

// evaluación de la comparación en tiempo de compilación.
constexpr bool sonIguales = compararRecursivoCompilacion(texto1, texto2);

int main()
{
    auto startTime = high_resolution_clock::now();
    bool resultado = sonIguales; // ya fue evaluado en compilación.

    auto endTime = high_resolution_clock::now();

    auto elapsedTime = duration_cast<nanoseconds>(endTime - startTime);

    cout << "Los textos son " << (resultado ? "iguales" : "diferentes") << endl;
    cout << "A la función compararRecursivoCompilacion le tomó " << elapsedTime.count() << " nanosegundos" << endl;

    return 0;
}

// Ejecuté una vez cada archivo y me dieron los siguientes números:
// Tiempo de código en ejecutado completamente en ejecución: 26540 nanosegundos
// Tiempo de código en ejecutado parcialmente en compilación y en ejecución: 90 nanosegundos
// Aunque no siempre me da el mismo número (habría que hacer un experimento con muchos casos y ver los valores)
// se vé claramente que la diferencia es grande

/* Conclusión:
1. La versión recursiva normal realiza la comparación en tiempo de ejecución, recorriendo los caracteres uno por uno.
   Como utiliza 'string', que maneja memoria dinámica, las operaciones requieren acceso en tiempo de ejecución, lo que genera un mayor tiempo de procesamiento.
2. La versión con 'constexpr' es evaluada completamente en tiempo de compilación, por lo que su tiempo de ejecución es cero.
3. Usar 'constexpr' permite eliminar el cálculo en tiempo de ejecución y mejorar el rendimiento si conocemos los valores en compilación.
   Esto funciona porque 'constexpr' opera sobre 'char' en arrays de tamaño fijo ('char[]'), permitiendo que las comparaciones se resuelvan en la fase de compilación sin necesidad de asignaciones dinámicas.
*/