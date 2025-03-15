#include <iostream>
#include <memory>
using namespace std;

struct node
{
    unique_ptr<node> next;
    int value;
};
struct list
{
    unique_ptr<node> head;
    int size;
};

unique_ptr<node> create_node(int value)
{
    unique_ptr<node> ptr_node = make_unique<node>();
    ptr_node->value = value;
    return ptr_node;
}

void push_front(list &l, int value)
{
    unique_ptr<node> new_node = create_node(value);
    new_node->next = move(l.head);
    l.head = move(new_node);
    l.size++;
}

void push_back(list &l, int value)
{
    unique_ptr<node> new_node = create_node(value);

    if (!l.head)
    {
        l.head = move(new_node);
    }
    else
    {
        unique_ptr<node> *temp = &l.head;
        while ((*temp)->next)
        {
            temp = &((*temp)->next);
        }
        (*temp)->next = move(new_node);
    }
    l.size++;
}

void insert(list &l, int value, int position)
{
    if (position <= 0)
    {
        push_front(l, value);
        return;
    }

    unique_ptr<node> new_node = create_node(value);
    unique_ptr<node> *temp = &l.head;
    int index = 0;

    while ((*temp)->next && index < position - 1)
    {
        temp = &((*temp)->next);
        index++;
    }

    new_node->next = move((*temp)->next);
    (*temp)->next = move(new_node);
    l.size++;
}

void erase(list &l, int position)
{
    if (position <= 0)
    {
        l.head = move(l.head->next);
        l.size--;
        return;
    }

    unique_ptr<node> *temp = &l.head;
    int index = 0;

    while ((*temp)->next && index < position - 1)
    {
        temp = &((*temp)->next);
        index++;
    }

    if ((*temp)->next)
    {
        (*temp)->next = move((*temp)->next->next);
        l.size--;
    }
}

void print_list(list &l)
{
    unique_ptr<node> *temp = &l.head;
    while (*temp)
    {
        cout << (*temp)->value;
        if ((*temp)->next)
            cout << " -> ";
        temp = &((*temp)->next);
    }
    cout << endl;
}

int main()
{
    list l;

    push_front(l, 3);
    push_front(l, 2);
    push_front(l, 1);
    print_list(l); // imprime 1 -> 2 -> 3

    push_back(l, 4);
    push_back(l, 5);
    print_list(l); // imprime 1 -> 2 -> 3 -> 4 -> 5

    insert(l, 10, 2);
    print_list(l); // imprime 1 -> 2 -> 10 -> 3 -> 4 -> 5

    erase(l, 3);
    print_list(l); // imprime 1 -> 2 -> 10 -> 4 -> 5

    return 0;
}