#pragma once
/*!
 *	\file my_stack.h - Plik zawiera definicje klasy my_stack
 */

#include <iostream>

#define ROZ 1000 //Definiowanie wielkosci stosu

using namespace std;

/*!
 *	\brief Szablon klasy my_stack pozwalajacy na stworzenie stosu operujacego na wybranej zmiennej
 */
template <class Var>
class my_stack
{
	Var tab[ROZ]; //tablice indeksujemy od 0
	int head; //indeks elementu na szczycie stosu

public:
	my_stack(); //Konstruktor
	int empty(); //sprawdzenie czy stos nie jest pusty
	int push(Var num);  //dodanie wartosci na szczyt stosu
	Var pop(); //zdjecie wartosci ze szczytu stosu
	Var top(); //wyswietlenie wartosci ze szczytu stosu
	int size(); //wyswietlenie ilosci elementow na stosie

};

/*!
 *	\brief Konstruktor klasy my_stack
 */
template<class Var>
my_stack<Var>::my_stack()
{
	head = -1;
	for (int i = 0; i < ROZ; i++)
	{
		tab[i] = 0;
	}
}

/*!
 *	\brief Sprawdza czy stos jest pusty
 *
 *	\retval Jezeli pusty to 1, a je¿eli nie to 0
 */
template <class Var>
int my_stack<Var>::empty()
{
	if (head == -1)
		return 1;
	else
		return 0;
}

/*!
 *	\brief Dodaje wartosc na szczyt stosu
 *
 *	\param[in] num - wartosc dodawana na stos
 *
 *	\retval Zwraca 1 jezeli udalo sie dodac wartosc, 0 jezeli nie
 */
template<class Var>
int my_stack<Var>::push(Var num)
{
	if (head < ROZ - 1) {
		head++;
		tab[head] = num;
		return 1;
	}
	else
	{
		cout << "Stos jest pelny, nie dodano wartosci" << endl;
		return 0;
	}
}

/*!
 *	\brief Usuwa wartosc ze szczytu stosu
 *
 *	\retval Zwraca usunieta wartosc, a jezeli sie nie udalo to 0
 */
template<class Var>
Var my_stack<Var>::pop()
{
	if (!empty())
	{
		head--;
		return tab[head + 1];
	}
	else
	{
		cout << "Stos jest pusty" << endl;
		return 0;
	}
}

/*!
 *	\brief Wyswietla wartosc znajdujaca sie na szczycie stosu
 *
 *	\retval Zwraca wartosc znajdujaca sie na szczycie stosu, a jezeli stos pusty to 0
 */
template<class Var>
Var my_stack<Var>::top()
{
	if (!empty())
	{
		cout << "Na szczycie stosu znajduje sie: " << tab[head] << endl;
		return tab[head];
	}
	else
		cout << "Stos jest pusty" << endl;
	return 0;
}

/*!
 *	\brief Wysietla ilosc elementow na stosie
 *
 *	\retval Ilosc elementow na stosie
 */
template <class Var>
int my_stack<Var>::size()
{
	if (!empty())
		return head + 1;
	else
		return 0;
}
