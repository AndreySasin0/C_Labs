#include "LinkedList.h"
#include <iostream>
#include <string>

const int OVERFLOW_EXCPT = 1;
const int OUT_OF_BOUNDS_EXCPT = 2;
const int WRONG_INDEX_EXCPT = 3;
using namespace std;

template <typename T>
Node<T>::Node(T item, Node *pNext)
{
    this->item = item;
    this->pNext = pNext;
}

template <typename T>
LinkedList<T>::LinkedList(int limit)
{
    size = 0;
    this->limit = limit;
    head = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList()
{
    size = 0;
    limit = 5;
    head = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template <typename T>
int LinkedList<T>::getSize()
{
    return size;
}

template <typename T>
void LinkedList<T>::pushBack(T item)
{
    if (size < limit)
    {
        if (head == nullptr)
        {
            head = new Node<T>(item);
        }
        else
        {
            Node<T> *currentNode = this->head;
            while (currentNode->pNext != nullptr)
            { //проходим по узлам и присваеваем адреса следующих элементов
                // пока не наткнемся на узел без следующего поинтера
                currentNode = currentNode->pNext;
            }
            currentNode->pNext = new Node<T>(item); //добавляем новый элемент, указываем на него
        }
        size++;
    }
    else
    {
        throw OVERFLOW_EXCPT;
    }
}

template <typename T>
void LinkedList<T>::popFront()
{
    if (!isEmpty())
    {
        Node<T> *temp = head; //запоминаем первый узел списка
        head = head->pNext;   //делаем следующий узел первым

        delete temp;

        size--;
    }
    else
    {
        throw OUT_OF_BOUNDS_EXCPT;
    }
}

template <typename T>
void LinkedList<T>::clear()
{
    while (!isEmpty())
    {
        popFront();
    }
}

template <typename T>
void LinkedList<T>::pushFront(T item)
{
    if (size < limit)
    {
        head = new Node<T>(item, head); //делаем новый элемент хедом, указывая на старый хед
        size++;
    }
    else
    {
        throw OVERFLOW_EXCPT;
    }
}

template <typename T>
void LinkedList<T>::popBack()
{
    if (!isEmpty())
    {
        removeAt(size - 1);
    }
    else
    {
        throw OUT_OF_BOUNDS_EXCPT;
    }
}

template <typename T>
void LinkedList<T>::insert(T item, int index)
{
    if (index >= 0 && index <= size - 1)
    {
        if (size < limit)
        {
            if (index == 0)
            {
                pushFront(item);
            }
            else
            {
                Node<T> *prev = this->head; //создаем временный указатель, который становится хедом

                for (int i = 0; i < index - 1; i++)
                {                       //находим узел с индексом на один меньше чем переданный index
                    prev = prev->pNext; //запоминаем в prev адрес узла, на один меньше чем переданный index
                }

                prev->pNext = new Node<T>(item, prev->pNext); //передаем прошлому узлу адрес нового

                size++;
            }
        }
        else
        {
            throw OVERFLOW_EXCPT;
        }
    }
    else
    {
        throw WRONG_INDEX_EXCPT;
    }
}

template <typename T>
void LinkedList<T>::removeAt(int index)
{
    if (index >= 0 && index <= size - 1)
    {
        if (index == 0)
        {
            popFront();
        }
        else
        {
            Node<T> *prev = this->head;
            for (int i = 0; i < index - 1; i++)
            {                       //находим узел с индексом на один меньше чем переданный index
                prev = prev->pNext; //запоминаем в prev адрес узла, на один меньше чем переданный index
            }
            Node<T> *toRemove = prev->pNext; //в toRemove сохраняем адрес, на который указывал удаляемый элемент
            prev->pNext = toRemove->pNext;   //передаем в узлу на один меньше удаляемого, адрес, на окторый указывал удаляемый узел

            delete toRemove;
            size--;
        }
    }
    else
    {
        throw WRONG_INDEX_EXCPT;
    }
}

template <typename T>
bool LinkedList<T>::search(T item)
{
    Node<T> *temp = head;
    for (int i = 0; i < size; i++)
    {
        if (temp->item == item)
        {
            return true;
        }
        temp = temp->pNext;
    }
    return false;
}

template <typename T>
void LinkedList<T>::doubleSize()
{
    limit = limit * 2;
}

template <typename T>
void LinkedList<T>::show()
{
    Node<T> *currentNode = this->head;
    while (currentNode != nullptr)
    {
        cout << currentNode->item;
        cout << " ";
        currentNode = currentNode->pNext; //идем дальше в следующий узел
    }
    cout << endl;
}

template <typename T>
bool LinkedList<T>::isEmpty()
{
    if (size != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*
template<typename T>
void LinkedList<T>::removeVal(T item) {
    int index = 0;
    Node<T> *temp = head;
    while (search(item) == true) {
        if (temp->item == item) {
            removeAt(index);
            index = 0;
        } else {
            temp = temp->pNext;
            index++;
        }
    }
}
*/

template <typename T>
void LinkedList<T>::removeVal(T item)
{
    while (head->item == item)
    {
        Node<T> *temp = this->head;
        head = head->pNext;
        delete temp;
        size--;
    }
    Node<T> *temp = this->head;
    while (temp->pNext != nullptr)
    {
        if (temp->pNext->item == item)
        {
            Node<T> *tempNew = temp->pNext;
            temp->pNext = temp->pNext->pNext;
            delete tempNew;
            size--;
        }
        else
        {
            temp = temp->pNext;
        }
    }
}

int main()
{
    cout << "Choose the size of your list" << endl;
    int length;
    if (cin >> length)
    {
        LinkedList<int> lst(length);
        cout
            << "Choose an option:\n 1. add a node at the beginning\n 2. add a node at the end\n 3. add a node at a certain index\n 4. remove a node from the beginning\n"
               " 5. remove a node from the end\n 6. remove a node from a certain index\n 7. show list\n 8. get size of the list\n 9. double size of the list\n "
               "10. search certain value\n 11. delete all nodes\n 12. delete node with certain value\n 0. exit"
            << endl;
        int destiny = -999;

        while (destiny != 0)
        {
            cout << "> \n";
            cin >> destiny;
            if (destiny == 1)
            {
                try
                {
                    int data;
                    cout << "Enter a value" << endl;
                    cin >> data;
                    lst.pushFront(data);
                }
                catch (int OVERFLOW_EXCPT)
                {
                    cout << "You try to overfill the list, use the function to increase the size of the list"
                         << endl;
                }
            }
            else if (destiny == 2)
            {
                try
                {
                    int data;
                    cout << "Enter a value" << endl;
                    cin >> data;
                    lst.pushBack(data);
                }
                catch (int OVERFLOW_EXCPT)
                {
                    cout << "You try to overfill the list, use the function to increase the size of the list"
                         << endl;
                }
            }
            else if (destiny == 3)
            {
                try
                {
                    int data;
                    int index;
                    cout << "Enter a value" << endl;
                    cin >> data;
                    cout << "Enter an index" << endl;
                    cin >> index;
                    lst.insert(data, index);
                }
                catch (int OVERFLOW_EXCPT)
                {
                    cout
                        << "You try to overfill the list or no such index in the list!\nUse the function to increase the size of the list or try to enter another index"
                        << endl;
                }
            }
            else if (destiny == 4)
            {
                try
                {
                    lst.popFront();
                }
                catch (int OUT_OF_BOUNDS_EXPT)
                {
                    cout << "List is empty" << endl;
                }
            }
            else if (destiny == 5)
            {
                try
                {
                    lst.popBack();
                }
                catch (int OUT_OF_BOUNDS_EXPT)
                {
                    cout << "List is empty" << endl;
                }
            }
            else if (destiny == 6)
            {
                try
                {
                    int index;
                    cout << "Enter an index" << endl;
                    cin >> index;
                    lst.removeAt(index);
                }
                catch (int WRONG_INDEX_EXPT)
                {
                    cout << "No such index in the list!" << endl;
                }
            }
            else if (destiny == 7)
            {
                lst.show();
            }
            else if (destiny == 8)
            {
                cout << "Size of your list is " << lst.getSize() << endl;
            }
            else if (destiny == 9)
            {
                lst.doubleSize();
                cout << "The size of list doubled" << endl;
            }
            else if (destiny == 10)
            {
                int value;
                cout << "Enter the value that you are searching\n";
                cin >> value;
                if (lst.search(value))
                {
                    cout << "This value is in the list\n";
                }
                else
                {
                    cout << "There is no such value in the list\n";
                }
            }
            else if (destiny == 11)
            {
                lst.clear();
                cout << "All nodes have been deleted\n";
            }
            else if (destiny == 12)
            {
                try
                {
                    cout << "Enter a value\n";
                    int value;
                    cin >> value;
                    lst.removeVal(value);
                }
                catch (int WRONG_INDEX_EXCPT)
                {
                    cout << "Wrong index!" << endl;
                }
            }
            else if (destiny == 0)
            {
            }
            else
            {
                cout << "Wrong command\n";
            }
        }
    }
    else
    {
        cout << "You entered the wrong value!\n";
    }
}