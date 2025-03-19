#include <iostream>

using namespace std;

/*
Para pensar este ejercicio pensé en hacer tres funciones para dividir mejor la lógica:
una para crear la matriz, otra liberar memoria y otra para imprimir la matriz.
*/

/*
Función que crea una matriz tamaño n x n

El parámetro que recibe es el tamaño de la matriz.
Devuelve un puntero a la matriz
Hace throws de errores:
- invalid_argument si n es menor a 2.
- runtime_error si no hay suficiente memoria para la asignación.

*/
int **crear_matriz(int n)
{
    if (n < 2)
    {
        throw invalid_argument("N debe ser un entero positivo mayor a 1");
    }

    // se reserva memoria para un array de punteros a filas.
    int **matriz = new int *[n];

    try
    {
        // se reserva memoria para cada fila de la matriz.
        for (int i = 0; i < n; i++)
        {
            matriz[i] = new int[n];
        }
    }
    catch (const bad_alloc &)
    {
        // si hay un error de asignación de memoria, liberamos lo ya reservado y lanzamos una excepción.
        for (int i = 0; i < n; i++)
        {
            delete[] matriz[i];
        }
        delete[] matriz;
        throw runtime_error("No hay memoria suficiente");
    }

    // se inicializa la matriz con valores.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz[i][j] = (i * n) + j + 1;
        }
    }

    return matriz;
}

/*
Función que libera la memoria de la matriz.
Los parámetros que recibe son un puntero a la matriz que se va a liberar y el tamaño de esta.
*/
void liberar_memoria(int ***matriz, int n)
{
    if (!(*matriz)) // verifica que la matriz no sea nullptr antes de liberar.
        return;

    for (int i = 0; i < n; i++)
    {
        delete[] (*matriz)[i]; // se libera cada fila de la matriz.
    }
    delete[] (*matriz); // se libera el array de punteros.
    *matriz = nullptr;  // se establece el puntero a nullptr para evitar accesos a memoria liberada.
}

/*
Función que imprime la matriz en orden inverso.
Los parametros que recibe son la matriz a imprimir y el tamaño de esta
*/

void imprimir_matriz(int **matriz, const int n)
{
    // se recorre la matriz en orden inverso.
    for (int k = n * n - 1; k >= 0; k--)
    {
        int fila = k / n;    //fila
        int columna = k % n; //columna
        cout << "M[" << fila << "][" << columna << "] = " << matriz[fila][columna] << endl;
    }
}

int main()
{
    int n;
    cout << "Ingrese el valor de n: ";
    cin >> n;

    int **matriz = nullptr;

    try
    {
        // se crea la matriz y se muestra.
        matriz = crear_matriz(n);
        imprimir_matriz(matriz, n);
    }
    catch (const exception &e)
    {
        // captura de excepciones en caso de error en la asignación de memoria o entrada inválida.
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    // se libera la memoria de la matriz
    liberar_memoria(&matriz, n);

    return 0;
}
