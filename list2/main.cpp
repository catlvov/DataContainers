#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define DEBUG
#define tab "\t"
#define delimeter "\n-----------------------------------------------------------------\n"

//globel score - глобальное пространтво имен
class List
{
	//ќбъ€влен в пространтсве имен класа 'list'
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr):
			Data(Data),pNext(pNext),pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << endl;
#endif 
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << endl;
#endif 
		}
		friend class List;
	}*Head,*Tail;
	size_t size; //size_t - unsigned int
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
#ifdef DEBUG
		cout << "lConstructor:\t" << endl;
#endif 
	}
	~List()
	{
		//while (Tail)pop_Back();
		while (Head)pop_front();
#ifdef DEBUG
		cout << "lDestructor:\t" << endl;
#endif 
	}
	//		add element:
	void push_front(int Data)
	{
		if (Head == nullptr and Tail == nullptr) 
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
		Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = New;
		}
		else
		{
			// Adding it to the end
			Tail->pNext = New;
			New->pPrev = Tail;
			Tail = New;
		}
		size++;
	}
	//		remove elements
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		else if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
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
	void pop_Back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
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
	//		methods
	void print()
	{
		cout << delimeter;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << delimeter;
		cout << "size list:\t" << size << endl;
	}

	void reverse_print()
	{
		cout << delimeter;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		}
		cout << delimeter;
		cout << "size list:\t" << size << endl;
	}
};

#define PUSH_FRONT

void main()
{
#ifndef PUSH_FRONT
	int n;
	cout << "perhaps you can see the size of the list: "; cin >> n; cout << endl;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}

	list.print();

	list.reverse_print();
#endif 

	int n;
	cout << "perhaps you can see the size of the list: "; cin >> n; cout << endl;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.pop_Back();
	list.reverse_print();
}

