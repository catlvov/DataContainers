#include <iostream>
#include <initializer_list>
using std::cin;
using std::cout;
using std::endl;

#define DEBUG
#define tab "\t"
#define delimiter "\n-----------------------------------------\n"


class List
{
    //Объявлен в пространстве имен класса 'List'
    class Element
    {
        int Data;
        Element* pNext;
        Element* pPrev;
    public:
        Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
            Data(Data), pNext(pNext), pPrev(pPrev)
        {
#ifdef DEBUG
            cout << "EConstructor:\t" << this << endl;
#endif 
        }

        ~Element()
        {
#ifdef DEBUG
            cout << "EDestructor:\t" << this << endl;
#endif 
        }
        friend class List;
    }*Head, * Tail;
    size_t size;

public:
    class Iterator
    {
        Element* Temp;
    public:
        Iterator(Element* Temp = nullptr) : Temp(Temp) {}
        ~Iterator() {}
        Iterator& operator++()
        {
            Temp = Temp->pNext;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator old = *this;
            Temp = Temp->pNext;
            return old;
        }
        bool operator==(const Iterator& other)const
        {
            return this->Temp == other.Temp;
        }
        bool operator!=(const Iterator& other)const
        {
            return this->Temp != other.Temp;
        }

        int operator*()const
        {
            return Temp->Data;
        }
        int& operator*()
        {
            return Temp->Data;
        }
    };

    class ReverseIterator
    {
        Element* Temp;
    public:
        ReverseIterator(Element* Temp = nullptr) : Temp(Temp) {}
        ~ReverseIterator() {}
        ReverseIterator& operator++()
        {
            Temp = Temp->pPrev;
            return *this;
        }
        ReverseIterator operator++(int)
        {
            ReverseIterator old = *this;
            Temp = Temp->pPrev;
            return old;
        }
        bool operator==(const ReverseIterator& other)const
        {
            return this->Temp == other.Temp;
        }
        bool operator!=(const ReverseIterator& other)const
        {
            return this->Temp != other.Temp;
        }

        int operator*()const
        {
            return Temp->Data;
        }
        int& operator*()
        {
            return Temp->Data;
        }
    };

    Iterator begin()
    {
        return Head;
    }
    Iterator end()
    {
        return nullptr;
    }

    ReverseIterator rbegin()
    {
        return Tail;
    }

    ReverseIterator rend()
    {
        return nullptr;
    }

    List()
    {
        Head = Tail = nullptr;
        size = 0;
#ifdef DEBUG
        cout << "LConstructor:\t" << this << endl;
#endif 
    }

    List(const std::initializer_list<int>& il) :List()
    {
        for (int const* it = il.begin(); it != il.end(); it++)
            push_back(*it);
    }

    ~List()
    {
        while (Head)pop_front();
#ifdef DEBUG
        cout << "LDestructor:\t" << this << endl;
#endif 
    }

    //		add element:
    void push_front(int Data)
    {
        if (Head == nullptr && Tail == nullptr)
        {
            Head = Tail = new Element(Data);
        }
        else
        {
            Head = Head->pPrev = new Element(Data, Head);
        }
        size++;
    }

    void push_back(int Data)
    {
        if (Head == nullptr && Tail == nullptr)
        {
            Head = Tail = new Element(Data);
        }
        else
        {
            Tail = Tail->pNext = new Element(Data, nullptr, Tail);
        }
        size++;
    }

    void Insert(int Data, size_t index) 
    {
        if (index > size) return;
        if (index == 0)
        {
            push_front(Data);
            return;
        }
        if (index == size)
        {
            push_back(Data);
            return;
        }
        Element* current = Head;
        for (size_t i = 0; i < index; i++)
            current = current->pNext;
        current->pPrev = current->pPrev->pNext = new Element(Data, current, current->pPrev);
        size++;
    }

    //		remove elements
    void pop_front()
    {
        if (Head == nullptr && Tail == nullptr)return;
        if (Head == Tail)
        {
            delete Head;
            Head = Tail = nullptr;
            size = 0;
            return;
        }
        else
        {
            Head = Head->pNext;
            delete Head->pPrev;
            Head->pPrev = nullptr;
        }
        size--;
    }

    void pop_back()  
    {
        if (Head == nullptr && Tail == nullptr)return;
        if (Head == Tail)
        {
            delete Tail;
            Head = Tail = nullptr;
            size = 0;
            return;
        }
        else
        {
            Tail = Tail->pPrev;
            delete Tail->pNext;
            Tail->pNext = nullptr;
        }
        size--;
    }

    void Erase(size_t index)
    {
        if (index >= size) return;

        if (index == 0)
        {
            pop_front();
            return;
        }

        if (index == size - 1)
        {
            pop_back();
            return;
        }

        Element* toDelete = Head;
        for (size_t i = 0; i < index; i++)
            toDelete = toDelete->pNext;

        toDelete->pPrev->pNext = toDelete->pNext;
        toDelete->pNext->pPrev = toDelete->pPrev;

        delete toDelete;
        size--;
    }

    //		methods
    void print()const
    {
        cout << delimiter;
        for (Element* Temp = Head; Temp; Temp = Temp->pNext)
            cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        cout << "Количество элементов списка: " << size << endl;
        cout << delimiter;
    }

    void reverse_print()const
    {
        cout << delimiter;
        for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
            cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        cout << "Количество элементов списка: " << size << endl;
        cout << delimiter;
    }

    size_t getSize() const { return size; }
};

//#define BASE_CHECK

int main()  
{
    setlocale(LC_ALL, "");

#ifdef BASE_CHECK
    int n;
    cout << "Введите количество элементов списка: "; cin >> n;
    List list;
    for (int i = 0; i < n; i++)
    {
        //list.push_front(rand() % 100);
        list.push_back(rand() % 100);
    }
    list.print();
    list.reverse_print();

    int index;
    int value;
    cout << "Введите индекс добавляемого элемента: "; cin >> index;
    cout << "Введите значение добавляемого элемента: "; cin >> value;
    list.Insert(value, index);
    list.print();
    list.reverse_print();

#endif // BASE_CHECK

    cout << "=== Тестирование списка ===" << endl;

    // 1.  initializer_list
    List list = { 3,5,8,13,21 };
    cout << "\n1. Созданный список:" << endl;
    list.print();

    // 2. Тестирование прямого итератора
    cout << "\n2. Вывод через прямой итератор:" << endl;
    for (int i : list) cout << i << tab;
    cout << endl;

    // 3. Тестирование обратного итератора
    cout << "\n3. Вывод через обратный итератор:" << endl;
    for (List::ReverseIterator rit = list.rbegin(); rit != list.rend(); ++rit)
        cout << *rit << tab;
    cout << endl;

    // 4. Insert
    cout << "\n4. После Insert(100, 2):" << endl;
    list.Insert(100, 2);
    list.print();

    // 5. Erase
    cout << "\n5. После Erase(3):" << endl;
    list.Erase(3);
    list.print();

    // 6.  pop_front  pop_back
    cout << "\n6. После pop_front() и pop_back():" << endl;
    list.pop_front();
    list.pop_back();
    list.print();

    // 7. push_front  push_back
    cout << "\n7. После push_front(999) и push_back(777):" << endl;
    list.push_front(999);
    list.push_back(777);
    list.print();

    // 8. range-based
    cout << "\n8. Вывод через range-based for loop:" << endl;
    for (int i : list) cout << i << tab;
    cout << endl;

    return 0;
}