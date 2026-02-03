#include <iostream>
#include <ctime>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
private:
	int Data; //значения элемента
	Element* pNext;
	static int count ;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
#ifdef DEBUG
		cout << "EContructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor\t" << this << endl;
#endif //DEBUG
	}
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) : Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDesctructor:\t" << this << endl;
	}
	//	operators:
	Iterator& operator ++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	
	bool operator ==(const Iterator& other) const
	{
		return this->Temp == other.Temp;
	}
	bool operator !=(const Iterator& other) const
	{
		return this->Temp != other.Temp;
	}

	int& operator*()
	{
		return Temp->Data;

	}
	const int& operator*() const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;
	int size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "Lconstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();*/
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		//initializer_list - это контейнер
		//Контейнер - это обект который рганизует хранение других объектов в памяти
		//у любого контейнера есть методы begin() и end()
		//begin() - возвращает отератор на начало контейнера
		//end() - возвращает итератор на конец контейнера
			for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "Ldeconstructor:\t" << this << endl;
	}
	// opertors;
	ForwardList& operator = (const ForwardList& other)
	{
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_front(Temp->Data);
		reverse();
		return *this;
	}
	//	adding elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);

		New->pNext = Head;

		Head = New;

		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		Element* temp = Head;

		while (temp->pNext)
		{
			temp = temp->pNext;
		}

		temp->pNext = New;

		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index > size)return;
		Element* New = new Element(Data);
		Element* Temp = Head;

		for (int i = 0; i < Index-1; ++i)Temp = Temp->pNext;

		New->pNext = Temp->pNext;

		Temp->pNext = New;
		size++;
	}
	// remove element:
	void pop_front()
	{
		Element* Eresed = Head;

		Head = Head->pNext;

		delete Eresed;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;

		while (Temp->pNext->pNext)Temp = Temp->pNext;

		Temp->pNext;

		delete Temp;
		size--;
	}
	//	methods:
	void print()const
	{
		Element* temp = Head;
		while (temp)
		{
			cout << temp << tab << temp->Data << tab << temp->pNext << endl;
			temp = temp->pNext;
		} 
		cout << "Size list: " << size << endl ;
	}

	void reverse()
	{
		ForwardList buf;
		while (Head)
		{
			buf.push_front(Head->Data);
			/*&pop_front;*/
		}
		Head = buf.Head;
		buf.Head = nullptr;
	}
};

//#define BASE_CHECK
//#define COPY_METHODS_CHECK
//#define MULTIPLE_LISTS
//#define RANGE_BASED_FOR_ARRAY

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK

	int listSize;
	cout << "Int size list: "; cin >> listSize;
	clock_t start = clock();
	ForwardList list;
	for (int i = 0; i < listSize; i++)
	{
		list.push_front(rand() % 100);
	}

	clock_t end = clock();
	////list.print();
	///*list.push_back(123);
	//list.print();*/
	///*list.pop_front();
	//list.print();*/
	///*list.pop_back();
	//list.print();*//*
	//int index, value;
	//cout << ""; cin >> index;
	//cout << ""; cin >> value;
	//list.insert(value, index);
	//list.print();*/
	cout << "Create list complite" << endl;
	cout << "time spent on creation:\t" << double(end-start)/CLOCKS_PER_SEC << "\t" << endl;
#endif

#ifdef COPY_METHODS_CHECK
	system("PAUSE");
	start = clock();
	ForwardList list2;
	//list2 = list;
	list2.print();
	end = clock();
	cout << "copy list" << "time spent on copied:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
#endif 

#ifdef MULTIPLE_LISTS
	ForwardList list1;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_back(5);
	list1.push_back(6);
	list1.print();
	ForwardList list2;
	list2.push_back(7);
	list2.push_back(8);
	list2.push_back(9);
	list2.push_back(10);
	list2.push_back(11);
	list2.push_back(12);
	list2.print();
#endif

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

	ForwardList list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
}