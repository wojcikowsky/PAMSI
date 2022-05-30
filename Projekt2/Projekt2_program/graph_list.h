#pragma once

#include <iostream>
#include <fstream>
#include "my_stack.h"
#include "my_doubly_list.h"

#define INF 10000000

using namespace std;

template <class Var>
class graph_list
{
	struct Cell
	{
		int num; //Wartosc
		Var weight;
		Cell* next; //Wskaznik na nastepny element
		Cell(int n, Var w) //Konstruktor struktury Cell
		{
			num = n;
			weight = w;
			next = nullptr;
		}
	};
	Cell** array;
	Var* cost;
	int tops;
	int edges;
	int init_top;
	int* prev;

public:
	void fill(double dens, int size);//
	void load(ifstream& file);//
	void print(ofstream& file);//
	void save(ofstream& file);
	void dijkstra();//
	void bellmanford();//
	void delete_graph();
};

template <class Var>
void graph_list<Var>::delete_graph()
{
	Cell *iter, *temp;
	
	for (int i = 0; i < tops; i++)
	{
		iter = array[i];
		array[i] = nullptr;
		while (iter != nullptr)
		{
		temp = iter;
		iter = iter->next;
		delete temp;
		}
	}
	delete[] array;
}

template <class Var>
void graph_list<Var>::fill(double dens, int size)
{
	tops = size;
	edges = (size * size - size) * dens;
	init_top = rand() % (size - 1);
	int remain = edges; //ile wierzcholkow zostalo do dodania

	array = new Cell * [tops];

	for (int i = 0; i < tops; i++)
	{
		array[i] = NULL;
	}

	for (int j = 1; j < tops && remain > 0; j++)
	{
		for (int i = 0; i < tops && remain > 0; i++)
		{
			Cell* temp = new Cell((i + j) % tops, rand() % size * 5);
			temp->next = array[i];
			array[i] = temp;
			remain--;
		}
	}
}

template<class Var>
void graph_list<Var>::load(ifstream& file)
{
	int  i = 0, j = 0;
	Var  k = 0;
	file >> tops;
	file >> edges;
	file >> init_top;

	array = new Cell * [tops];

	for (int i = 0; i < tops; i++)
	{
		array[i] = NULL;
	}

	while (!file.eof())
	{
		file >> i;
		file >> j;
		file >> k;
		Cell* temp = new Cell(j, k);
		temp->next = array[i];
		array[i] = temp;
	}
}

template <class Var>
void graph_list<Var>::print(ofstream& file)
{
	Cell* iter;
	file << tops << '\t' << edges << '\t' << init_top << endl;
	for (int i = 0; i < tops; i++)
	{
		iter = array[i];
		while (iter != nullptr)
		{
			file << i << " ";
			file << iter->num << " ";
			file << iter->weight << " ";
			file << endl;
			iter = iter->next;
		}
	}
}



template <class Var>
void graph_list<Var>::save(ofstream& file)
{
	my_stack<int> stack;
	int temp;
	file << "source: " << init_top << endl;

	for (int i = 0; i < tops; i++) //Przejscie po wszysykich wierzcholkach
	{
		if (prev[i] != -1 && i != init_top)
		{
			temp = i;

			while (prev[temp] != init_top)
			{
				temp = prev[temp];
				stack.push(temp);
			}

			file << i << " [" << init_top << ", ";

			while (!stack.empty())
			{
				file << stack.pop() << ", ";
			}


			file << i << "] " << cost[i] << endl;
		}
		if (i == init_top)
		{
			file << i << " " << "[" << prev[i] << "] " << cost[i] << endl;
		}
	}
}

template <class Var>
void graph_list<Var>::dijkstra()
{
	my_doubly_list<int> pr_list; //stworzenie listy ktora bedzie nasza kolejka priorytetowa
	int T; 
	bool* check = new bool[tops]; //odznaczamy sprawdzone sciezki

	cost = new Var[tops]; //zapis kosztkow sciezek
	prev = new int[tops]; //poprzednik wierzcholka pozwalajacy wyznaczyc sciezke

	for (int i = 0; i < tops; i++)
	{
		check[i] = false; //zaden z wierzcholkow nie jest jeszcze sprawdzony
		cost[i] = INF; //zadna sciezka nie jest jeszcze sprawdzona
		prev[i] = -1;
	}

	T = init_top;
	cost[T] = 0;
	prev[init_top] = init_top;
	pr_list.add_pr(T, INF);
	Cell* iter;

	while (!pr_list.empty())
	{
		check[T] = true;
		iter = array[T];
		while (iter != nullptr)
		{
			if (cost[iter->num] > cost[T] + iter->weight/* && T != init_top*/) //Pozostale wierzcholki
			{
				cost[iter->num] = cost[T] + iter->weight;
				prev[iter->num] = T;
				if (check[iter->num] == false) //jezeli nie odwiedzalismy wierzcholka	
					pr_list.add_pr(iter->num, cost[iter->num]); //dodajemy wierzcholek do listy z priorytetem	
			}
			iter = iter->next;
		}
		while (check[T] == true && !pr_list.empty())
			T = pr_list.remove_front();
	}
}

template <class Var>
void graph_list<Var>::bellmanford()
{
	cost = new Var[tops]; //zapisujemy koszty sciezki
	prev = new int[tops];
	int diff = 1;
	Cell* iter;

	for (int i = 0; i < tops; i++)
	{
		prev[i] = -1; //nie wiemy nic o poprzednikach
		cost[i] = INF; //zadna sciezka nie jest jeszcze sprawdzona
	}

	prev[init_top] = init_top;
	cost[init_top] = 0; //Dojscie do wierzcholka startowego   

	for (int iterator = 0; iterator < tops - 1 && diff != 0; iterator++) //Przechodzimy tops-1 razy po ka¿dej krawêdzi
	{
		diff = 0;
		for (int i = 0; i < tops; i++) //Przeszukujemy liste sasiedztwa
		{
			iter = array[i];
			while (iter != nullptr) //relaksowanie krawedzi
			{
				if (cost[iter->num] > cost[i] + iter->weight)
				{
					cost[iter->num] = cost[i] + iter->weight;
					prev[iter->num] = i;
					diff++;
				}
				iter = iter->next;
			}
		}
	}

	for (int i = 0; i < tops && diff != 0; i++) //Sprawdzanie istnienia cykli ujemnych
	{
		iter = array[i];
		while (iter != nullptr)
		{
			if (cost[iter->num] > cost[i] + iter->weight)
			{
				cout << endl << "W grafie wystêpuj¹ cykle ujemne, nie mo¿na go rozwi¹zaæ!" << endl;
				for (int iter = 0; iter < tops; iter++)
				{
					cost[iter] = INF;
					prev[iter] = init_top;
				}
				return;
			}
			iter = iter->next;
		}
	}
}