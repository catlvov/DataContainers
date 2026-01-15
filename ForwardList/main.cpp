#include <iostream>

using namespace std;
#define tab "\t"

class Element
{
private:
	int Data; //значения элемента
	Element* pNext;

public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		cout << "EContructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;
		cout << "Lconstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "Ldeconstructor:\t" << this << endl;
	}
	//	adding elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);

		New->pNext = Head;

		Head = New;
	}
	//	metgods:
	void print()const
	{
		Element* temp = Head;
		while (temp)
		{
			cout << temp << tab << temp->Data << tab << temp->pNext << endl;
			temp = temp->pNext;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int listSize;
	cout << "Видите размер списка: "; cin >> listSize;
	ForwardList list;
	for (int i = 0; i < listSize; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
}