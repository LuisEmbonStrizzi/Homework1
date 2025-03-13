#include <iostream>
#include <array> 

using namespace std;

int** crear_matriz(int n) {
    try
    {
        if(n < 2) {
            throw "N debe ser un entero positivo mayor a 1";
        }

        int** matriz = new int*[n];
        
        for (int i = 0; i < n; i++) {
            matriz[i] = new int[n];
        }
    
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matriz[i][j] = (i * n) + j + 1;
            }
        }

        return matriz;
    }
    catch(const char* e)
    {
        cout << "Error: " << e << endl; 
        return nullptr;
    }
}

void liberar_memoria(int** matriz, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void imprimir_matriz(int** matriz, int n) {
    for (int k = n * n - 1; k >= 0; k--){
        int fila = k / n;
        int columna = k % n;
        cout << "M[" << fila << "][" << columna << "] = " << matriz[fila][columna] << endl;
    }
}

int main() {
    int n;
    cout << "Ingrese el valor de n: ";
    cin >> n;

    int** matriz = crear_matriz(n);
    imprimir_matriz(matriz, n);
    liberar_memoria(matriz, n);

    return 0;
}