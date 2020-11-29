template <typename T>
class Node
{
public:
    Node *pNext;
    T item;

    Node(T item = T(), Node *pNext = nullptr);
};

template <typename T>
class LinkedList
{
public:
    LinkedList();

    LinkedList(int limit);

    ~LinkedList();

    void doubleSize();

    bool isEmpty();

    int getSize();

    void clear();

    void show();

    void pushBack(T item);

    void pushFront(T item);

    void insert(T item, int index);

    void popFront();

    void popBack();

    void removeAt(int index);

    void removeVal(T item);

    bool search(T item);

private:
    Node<T> *head; //указатель на первый элемент
    int size;
    int limit;
};