#include <iostream>

using namespace std;

int **crear_matriz(int n)
{
    if (n < 2)
    {
        throw invalid_argument("N debe ser un entero positivo mayor a 1");
    }

    int **matriz = new int *[n];

    try
    {
        for (int i = 0; i < n; i++)
        {
            matriz[i] = new int[n];
        }
    }
    catch (const bad_alloc &)
    {
        for (int i = 0; i < n; i++)
        {
            delete[] matriz[i];
        }
        delete[] matriz;
        throw runtime_error("No hay memoria suficiente.");
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz[i][j] = (i * n) + j + 1;
        }
    }

    return matriz;
}

void liberar_memoria(int ***matriz, int n)
{
    if (!(*matriz))
        return;

    for (int i = 0; i < n; i++)
    {
        delete[] (*matriz)[i];
    }
    delete[] (*matriz);
    *matriz = nullptr;
}

void imprimir_matriz(int **matriz, const int n)
{
    for (int k = n * n - 1; k >= 0; k--)
    {
        int fila = k / n;
        int columna = k % n;
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
        matriz = crear_matriz(n);
        imprimir_matriz(matriz, n);
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    liberar_memoria(&matriz, n);

    return 0;
}
