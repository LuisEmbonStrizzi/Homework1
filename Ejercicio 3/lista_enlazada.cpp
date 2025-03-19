/*
    Implementación de una lista enlazada utilizando smart pointers (unique_ptr).
    Este programa implementa una lista enlazada simple con las siguientes funcionalidades especificadas en el homework:

    - create_node(): Crea un nodo con un valor dado.
    - push_front(): Inserta un nodo al frente de la lista.
    - push_back(): Inserta un nodo al final de la lista.
    - insert(): Inserta un nodo en una posición específica de la lista.
    - erase(): Elimina un nodo en una posición específica de la lista.
    - print_list(): Imprime la lista enlazada en formato visual.

    Como la implementación pedía que se use smart pointers que permite que la memoria se maneja automáticamente yo decidí usar unique_ptr.
*/

#include <iostream>
#include <memory>
using namespace std;

struct node
{
    unique_ptr<node> next; // unique_ptr al siguiente nodo de la lista
    int value;
};

// Definición de la lista enlazada
struct list
{
    unique_ptr<node> head; // unique_ptr al primer nodo de la lista
    int size = 0;
};

// Función para crear un nuevo nodo con un valor dado
unique_ptr<node> create_node(int value)
{
    unique_ptr<node> ptr_node = make_unique<node>();
    ptr_node->value = value;
    return ptr_node;
}

// Inserta un nodo al frente de la lista
void push_front(list &l, int value)
{
    unique_ptr<node> new_node = create_node(value);
    new_node->next = move(l.head); // transfiere la propiedad del nodo actual de la cabeza al nuevo nodo
    l.head = move(new_node);       // el nuevo nodo se convierte en la cabeza de la lista
    l.size++;
}

// Inserta un nodo al final de la lista
void push_back(list &l, int value)
{
    unique_ptr<node> new_node = create_node(value);

    if (!l.head) // si la lista está vacía, el nuevo nodo se convierte en la cabeza
    {
        l.head = move(new_node);
    }
    else
    {
        unique_ptr<node> *temp = &l.head; // puntero temporal para recorrer la lista
        while ((*temp)->next)             // avanza hasta el último nodo
        {
            temp = &((*temp)->next);
        }
        (*temp)->next = move(new_node); // inserta el nuevo nodo al final de la lista
    }
    l.size++;
}

// Inserta un nodo en una posición específica de la lista
void insert(list &l, int value, int position)
{
    if (position <= 0) // si la posición es menor o igual a 0, inserta al frente. Esto no lo aclara en la consigna
    //pero sigue la lógica de insertar cuando está fuera de rango, se implementó de la misma forma para erase.
    //Es decir que para la posición -7 por ejemplo se insertará al frente
    {
        push_front(l, value);
        return;
    }

    unique_ptr<node> new_node = create_node(value);
    unique_ptr<node> *temp = &l.head; // puntero para recorrer la lista
    int index = 0;

    while ((*temp)->next && index < position - 1) // recorre hasta la posición deseada o el final
    {
        temp = &((*temp)->next);
        index++;
    }

    if (index < position - 1) // si no llegó a la posición deseada, significa que la lista era más corta
    {
        cout << "Advertencia: Posición " << position << " fuera de rango. Insertando al final." << endl;
    }

    new_node->next = move((*temp)->next); // conecta el nuevo nodo con el siguiente
    (*temp)->next = move(new_node);       // inserta el nuevo nodo en la posición deseada
    l.size++;
    
}

// Elimina un nodo en una posición específica de la lista
void erase(list &l, int position)
{
    if (!l.head) // si la lista está vacía, no hay nada que eliminar
    {
        cout << "La lista está vacía. No se puede eliminar ningún elemento." << endl;
        return;
    }

    if (position <= 0) // si la posición es menor o igual a 0, elimina el primer nodo
    {
        l.head = move(l.head->next);
        l.size--;
        return;
    }

    unique_ptr<node> *temp = &l.head;
    int index = 0;

    while ((*temp)->next && index < position - 1) // avanza hasta la posición deseada o el último nodo
    {
        temp = &((*temp)->next);
        index++;
    }

    if (!(*temp)->next || !(*temp)->next->next) // si la posición está fuera de rango, eliminar el último nodo
    {
        cout << "Advertencia: Posición " << position << " fuera de rango. Eliminando el último nodo." << endl;
        temp = &l.head;
        while ((*temp)->next && (*temp)->next->next) // avanza hasta el anterior al último nodo
        {
            temp = &((*temp)->next);
        }
        (*temp)->next = nullptr; // manda el último nodo a null
    }
    else // si la posición es válida, elimina el nodo en esa posición
    {
        (*temp)->next = move((*temp)->next->next);
    }
    l.size--;
}

// Imprime la lista enlazada
void print_list(list &l)
{
    unique_ptr<node> *temp = &l.head; // puntero temporal para recorrer la lista
    while (*temp)
    {
        cout << (*temp)->value; // imprime el valor del nodo
        if ((*temp)->next)
            cout << " -> ";
        temp = &((*temp)->next);
    }
    cout << endl;
}

// Función principal para probar la lista enlazada
int main()
{
    list l;

    push_front(l, 3);
    push_front(l, 2);
    push_front(l, 1);
    print_list(l);

    push_back(l, 4);
    push_back(l, 5);
    print_list(l);

    cout << "Insertando en una posición válida (posición 2)" << endl;
    insert(l, 10, 2);
    print_list(l);

    cout << "Insertando en una posición fuera de rango (posición 10)" << endl;
    insert(l, 99, 10); // esto debe agregar el nodo al final con una advertencia
    // Aclaración importante: En la consigna decía "se debe indicar lo ocurrido", yo lo que decí hacer es
    // incluir un print cuando ocurre esto y usarlo a modo de advertencia. Ídem con el caso de erase
    print_list(l);
    
    cout << "Insertando en una posición fuera de rango (posición -7)" << endl;
    insert(l, 82, -7); 
    print_list(l);

    cout << "Borrando un elemento en una posición válida (posición 3)" << endl;
    erase(l, 3);
    print_list(l);

    cout << "Borrando en una posición fuera de rango (posición 10)" << endl;
    erase(l, 10);
    print_list(l);

    cout << "Borrando en una posición fuera de rango (posición -2)" << endl;
    erase(l, -2);
    print_list(l);

    cout << "Intentando borrar de una lista vacía" << endl;
    list emptyList;
    erase(emptyList, 2);
    print_list(emptyList); // esperado: No imprime nada

    return 0;
}
