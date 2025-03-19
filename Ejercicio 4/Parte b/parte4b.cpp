#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*
Función recursiva que compara dos cadenas de texto carácter por carácter.
Los parámetros que recibe son dos cadenas y el índice actual en la comparación (por defecto inicia en 0).
Devueve true si las cadenas son iguales, false en caso contrario.
*/
bool compararRecursivo(const string &s1, const string &s2, int index = 0)
{
    if (s1.length() != s2.length()) // si las cadenas tienen distinta longitud, no pueden ser iguales.
        return false;
    if (index == s1.length()) // si se recorrió toda la cadena sin diferencias, son iguales.
        return true;
    if (s1[index] != s2[index]) // si hay una diferencia en un carácter, las cadenas no son iguales.
        return false;
    return compararRecursivo(s1, s2, index + 1); // llamado recursivo para comparar el siguiente carácter.
}

int main()
{
    string texto1 = "En abril de 1784, cuando tenía seis años, llegó con su familia a la ciudad española de Cádiz –previa estadía en Buenos Aires– y se radicó luego en la ciudad de Málaga.";
    string texto2 = "En abril de 1784, cuando tenía seis años, llegó con su familia a la ciudad española de Cádiz –previa estadía en Buenos Aires– y se radicó luego en la ciudad de Málaga.";

    auto startTime = high_resolution_clock::now();

    bool sonIguales = compararRecursivo(texto1, texto2);

    auto endTime = high_resolution_clock::now();

    auto elapsedTime = duration_cast<nanoseconds>(endTime - startTime);

    cout << "Los textos son " << (sonIguales ? "iguales" : "diferentes") << endl;
    cout << "A la función compararRecursivo le tomó " << elapsedTime.count() << " nanosegundos" << endl;

    return 0;
}
