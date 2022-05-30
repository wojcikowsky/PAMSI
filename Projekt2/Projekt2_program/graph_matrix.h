#pragma once

#include <iostream>
#include <fstream>
#include "my_stack.h"
#include "my_doubly_list.h"
#include <chrono>

#define INF 10000000

using namespace std;

template <class Var>
class graph_matrix
{
	Var*** matrix;
	int tops;
	int edges;
	int init_top;
	Var* cost;
	int* prev;

public:
	void load(ifstream &file);
	void fill(double dens, int size);
	void print(ofstream& file);
	void dijkstra();
	void bellmanford();
	void save(ofstream& file);
	void delete_graph();
};

template <class Var>
void graph_matrix<Var>::delete_graph()
{

	for (int i = 0; i < tops; i++)
	{
		for (int j = 0; j < tops; j++)
		{
			if (matrix[i][j] != nullptr)
				delete[] matrix[i][j];
		}
		delete[] matrix[i];
	}
	delete [] matrix;
}


template <class Var>
void graph_matrix<Var>::fill(double dens, int size)
{
	tops = size;
	edges = (size * size - size) * dens;
	init_top = rand() % (size - 1);
	int remain = edges;
	srand(time(NULL));

	matrix = new Var ** [tops];
	for (int i = 0; i < tops; i++)
		matrix[i] = new Var*[tops]; //Powo³anie dynamicznej macierzy s¹siedztwa

	for (int j = 0; j < tops; j++) //Wstêpnie zape³nienie macierzy
	{
		for (int i = 0; i < tops; i++)
		{
			matrix[j][i] = nullptr;
		}
	}

	for (int j = 0; j < tops && remain > 0; j++)
	{
		for (int i = 0; i < tops && remain > 0; i++) //polaczenie wszystkich wierzcholkow
		{
			remain--;
			matrix[i][(i + j + 1) % tops] = new Var;
			*(matrix[i][(i + j + 1) % tops]) = rand() % size * 5;
		}
	}
}

template <class Var>
void graph_matrix<Var>::load(ifstream &file)
{
	int i = 0, j = 0;
	file >> tops;
	file >> edges;
	file >> init_top;

	matrix = new Var * *[tops];
	for (int i = 0; i < tops; i++)
		matrix[i] = new Var * [tops]; //Powo³anie dynamicznej macierzy s¹siedztwa

	for (j = 0; j < tops; j++)
	{
		for (i = 0; i < tops; i++)
		{
			matrix[j][i] = nullptr;
		}
	}

	while (!file.eof())
	{
		file >> i;
		file >> j;
		matrix[j][i] = new Var;
		file >> *(matrix[j][i]);
	}
}

template <class Var>
void graph_matrix<Var>::print(ofstream& file)
{
	file << tops << '\t' << edges << '\t' << init_top << endl;
	for (int j = 0; j < tops; j++)
	{
		for (int i = 0; i < tops; i++)
		{
			if(matrix[j][i] != nullptr)
			file << *(matrix[j][i]) << '\t';
			else
			file << "NULL" << '\t';
		}
		file << endl; 
	}
}

template <class Var>
void graph_matrix<Var>::dijkstra()
{
	my_doubly_list<int> pr_list;
	int T;
	cost = new Var[tops]; //zapisujemy koszty sciezki
	bool* check = new bool[tops]; //odznaczamy sprawdzone wierzcholki
	prev = new int[tops];

	for (int i = 0; i < tops; i++)
	{
		check[i] = false; //zaden z wierzcholkow nie jest jeszcze sprawdzony
		cost[i] = INF; //zadna sciezka nie jest jeszcze sprawdzona
		prev[i] = -1;
	}

	T = init_top; //zaczynamy z wierzcholka poczatkowego
	cost[T] = 0;
	prev[init_top] = init_top;
	pr_list.add_pr(T, INF);

	while (!pr_list.empty()) 
	{
		check[T] = true;
		for (int i = 0; i < tops; i++) {
			if (matrix[i][T] != nullptr) {
				if (T == init_top) //pierwszy wierzcho³ek
				{
				cost[i] = *(matrix[i][T]);
				prev[i] = T;
				pr_list.add_pr(i, cost[i]); //dodajemy wierzcholek do listy z priorytetem
				}
				if (T != init_top && cost[i] > cost[T] + *(matrix[i][T])) //Pozostale wierzcholki
				{
				cost[i] = cost[T] + *(matrix[i][T]);
				prev[i] = T;
				if (!check[i]) //jezeli nie odwiedzalismy wierzcholka	
					pr_list.add_pr(i, cost[i]); //dodajemy wierzcholek do listy z priorytetem
				}
			}
		}
		while(check[T] == true && !pr_list.empty())
		T = pr_list.remove_front(); //Wyjmujemy z listy pierwszy elemeny wiec o najmniejszym koszcie sciezki
	}
	return;
}

template <class Var>
void graph_matrix<Var>::bellmanford()
{
	cost = new Var[tops]; //zapisujemy koszty sciezki
	prev = new int[tops];
	int diff = 1;

	for (int i = 0; i < tops; i++)
	{
		prev[i] = -1; //nie wiemy nic o poprzednikach
		cost[i] = INF; //zadna sciezka nie jest jeszcze sprawdzona
	}

	prev[init_top] = init_top;
	cost[init_top] = 0; //Dojscie do wierzcholka startowego   

	for (int iter = 0; iter < tops - 1 && diff != 0; iter++) //Przechodzimy tops-1 razy po ka¿dej krawêdzi
	{
		diff = 0;
		for (int i = 0; i < tops; i++) //Przeszukujemy macierz i relaksujemy krawedzie
		{
			for (int j = 0; j < tops; j++) 
			{
				if (cost[i] != INF && 
					matrix[j][i] != nullptr && 
					cost[j] > cost[i] + *(matrix[j][i]))
				{
					cost[j] = cost[i] + *(matrix[j][i]);
					prev[j] = i;
					diff++;
				}
			}
		}
	}
	
	for (int i = 0; i < tops && diff != 0; i++) //Sprawdzanie istnienia cykli ujemnych
	{
		for (int j = 0; j < tops; j++)
		{
			if (cost[i] != INF &&
				matrix[j][i] != nullptr &&
				cost[j] > cost[i] + *(matrix[j][i]))
			{
				cout << endl << "W grafie wystêpuj¹ cykle ujemne, nie mo¿na go rozwi¹zaæ!" << endl;
				for (int iter = 0; iter < tops; iter++)
				{
					cost[iter] = INF;
					prev[iter] = init_top;
				}
				return;
			}
		}
	}
}


template <class Var>
void graph_matrix<Var>::save(ofstream& file)
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