#pragma once
/*!
 *	\file my_doubly_list.h - Plik zawiera definicje klasy my_doubly_list (lista dwukierunkowa)
 */

#include <iostream>

using namespace std;

template<class Var>
class my_doubly_list
{
	struct Cell //Struktura definiujaca jeden element listy
	{
		Var value; //Wartosc
		Var weight;
		Cell* front_pointer; //Wskaznik na nastepny element
		Cell* back_pointer; //Wskaznik na poprzedni element
		Cell(Var d, Var w) //Konstruktor struktury Cell
		{
			weight = w;
			value = d;
			front_pointer = nullptr;
			back_pointer = nullptr;
		}
	};
	Cell* head; //Wskaznik na poczatek listy
	Cell* tail; //Wskaznik na koniec listy

public:
	my_doubly_list(); //Konstruktor
	int empty(); //Sprawcza czy lista jest pusta
	void insert_front(Var num, Var weight); //Dodaje element na pocz¹tek listy
	void insert_back(Var num, Var weight); //Dodaje element na koniec listy
	Var remove_front(); //Usuwa element z pocz¹tku listy
	Var remove_back(); //Usuwa element z konca listy
	int remove_key(Var key); //Usuwa z listy element z zadanym kluczem
	void display(); //Wyswietla zawartosc listy
	void add_pr(Var num, Var weight); //kolejka priorytetowa
	Var front_weight(); //Zwraca wage pierwszego elementu listy
	int size();
	Var ret_weight(int iter);
};



/*!
 *	\brief Konstruktor klasy my_doubly_list
 */
template<class Var>
my_doubly_list<Var>::my_doubly_list()
{
	head = nullptr;
	tail = nullptr;
}

/*!
 *	\brief Sprawdza czy lista jest pusta
 *
 *	\retval Zwraca 1 jezeli lista pusta, 0 jezeli nie
 */
template<class Var>
int my_doubly_list<Var>::empty()
{
	if (head == nullptr && tail == nullptr)
		return 1;
	else
		return 0;
}

/*!
 *	\brief Dodaje wartosc na poczatek listy
 *
 *	\param[in] num - wartosc dodawana na poczatek listy
 */
template<class Var>
void my_doubly_list<Var>::insert_front(Var num, Var weight)
{
	if (head == nullptr)
	{
		head = new Cell(num, weight);
		tail = head;
	}
	else
	{
		Cell* temp = new Cell(num, weight);
		temp->front_pointer = head;
		head->back_pointer = temp;
		head = temp;
	}
}

/*!
 *	\brief Dodaje wartosc na koniec listy
 *
 *	\param[in] num - wartosc dodawana na koniec listy
 */
template <class Var>
void my_doubly_list<Var>::insert_back(Var num, Var weight)
{
	if (tail == nullptr)
	{
		tail = new Cell(num, weight);
		head = tail;
	}
	else
	{
		Cell* temp = new Cell(num, weight);
		temp->back_pointer = tail;
		tail->front_pointer = temp;
		tail = temp;
	}
}

/*!
 *	\brief Usuwa element z poczatku listy
 *
 *	\retval Zwraca 1 je¿eli uda³o siê usun¹æ, jeœli nie to 0
 */
template <class Var>
Var my_doubly_list<Var>::remove_front()
{
	Var ret;
	if (!empty())
	{
		if (head->front_pointer == nullptr)
		{
			ret = head->value;
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			ret = head->value;
			head = head->front_pointer;
			delete head->back_pointer;
			head->back_pointer = nullptr;
		}
		return ret;
	}
	else
	{
		cout << "Lista jest pusta" << endl;
		return 0;
	}
}

/*!
 *	\brief Usuwa wartosc z konca kolejki
 *
 *	\retval Jezeli uda sie usunac to zwraca 1, jezeli nie to 0
 */
template <class Var>
Var my_doubly_list<Var>::remove_back()
{
	Var ret;
	if (!empty())
	{
		if (tail->back_pointer == nullptr)
		{
			ret = tail->value;
			delete tail;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			ret = tail->value;
			tail = tail->back_pointer;
			delete tail->front_pointer;
			tail->front_pointer = nullptr;
		}
		return ret;
	}
	else
	{
		cout << "Lista jest pusta" << endl;
		return 0;
	}
}

/*!
 *	\brief Usuwa wartosc z listy zgodnie z przekazanym kluczem
 *
 *	\param[in] key - przekazany klucz
 *
 *	\retval Jezeli uda sie usunac to zwraca 1, jezeli nie to 0
 */
template <class Var>
int my_doubly_list<Var>::remove_key(Var key)
{
	Cell* iter = head;
	Cell* backup = head;
	if (!empty())
	{
		while (iter != nullptr)
		{
			if (iter->value == key)
			{
				if (tail == head)
				{
					delete iter;
					tail = nullptr;
					head = nullptr;
					iter = head;
				}
				else
				{
					if (iter == head)
					{
						head = head->front_pointer;
						head->back_pointer = nullptr;
						delete iter;
						iter = head;
					}
					else
					{
						backup = iter->back_pointer;
						backup->front_pointer = iter->front_pointer;
						delete iter;
						if (backup->front_pointer == nullptr)
						{
							tail = backup;
							iter = backup;
						}
						else
						{
							iter = backup->front_pointer;
							iter->back_pointer = backup;
						}
					}
				}
			}
			else
			{
				iter = iter->front_pointer;
			}
		}
		return 1;
	}
	else
	{
		cout << "Lista jest pusta" << endl;
		return 0;
	}
}

/*!
 *	\brief Wyswietla liste
 */
template <class Var>
void my_doubly_list<Var>::display()
{
	Cell* iter = head;
	if (!empty())
	{
		while (iter != nullptr)
		{
			cout << iter->value << endl;
			iter = iter->front_pointer;
		}
	}
	else
		cout << "Lista jest pusta" << endl;
}

template<class Var>
Var my_doubly_list<Var>::front_weight() 
{
	if (!empty())
		return head->weight;
}

template<class Var>
void my_doubly_list<Var>::add_pr(Var num, Var weight)
{
	Cell* iter = head;
	Cell* temp = nullptr;

	if (empty()) //jezeli pusta to po prostu wstawiamy
	{
		insert_back(num, weight);
		return;
	}
	else 
	{
		while (iter != nullptr) //idziemy po liscie
		{
			if (iter->value == num) //je¿eli znajdziemy taki sam element to nie dodajemy
			{
				if (iter->weight > weight)
				{
					iter->weight = weight;
				}
				return;
			}
			if (iter->weight > weight) //znajdujemy element wiekszy od podanego
			{
				if (iter == head || tail == head) //jezeli jest to pierwszy element to wstawiamy na poczatek
				{
					insert_front(num, weight);
					return;
				}
				else {
					Cell* temp = new Cell(num, weight);
					temp->front_pointer = iter;
					temp->back_pointer = iter->back_pointer;
					iter->back_pointer = temp;
					iter = iter->back_pointer;
					iter = iter->back_pointer;
					iter->front_pointer = temp;
					return;
				}
			}
			iter = iter->front_pointer;
		}
		insert_back(num, weight);
		return;
	}
}

/*!
 *	\brief Zwraca ilosc elementow w liscie 
 */
template <class Var>
int my_doubly_list<Var>::size()
{
	int size = 0;
	Cell* iter = head;
	if (!empty())
	{
		while (iter != nullptr)
		{
			size++;
			iter = iter->front_pointer;
		}
		return size;
	}
	else
		return 0;
}
