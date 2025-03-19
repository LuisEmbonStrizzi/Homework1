#include <iostream>
#include <string>

using namespace std;

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
    string texto3 = "En abril de 1785, cuando tenía seis años, llegó con su familia a la ciudad española de Cádiz –previa estadía en Buenos Aires– y se radicó luego en la ciudad de Málaga.";
    string texto4 = "Participó en la defensa de Buenos Aires, capital del virreinato del Río de la Plata, en las dos invasiones inglesas —1806 y 1807— y promovió la emancipación de Hispanoamérica respecto de España en apoyo a las aspiraciones de la princesa Carlota Joaquina en la región, aunque sin éxito.";
    
    bool sonIguales1 = compararRecursivo(texto1, texto2);
    bool sonIguales2 = compararRecursivo(texto2, texto3);
    bool sonIguales3 = compararRecursivo(texto3, texto4);

    //Algunos tests

    cout << "Los textos son " << (sonIguales1 ? "iguales" : "diferentes") << endl;
    cout << "Los textos son " << (sonIguales2 ? "iguales" : "diferentes") << endl;
    cout << "Los textos son " << (sonIguales3 ? "iguales" : "diferentes") << endl;

    return 0;
}
