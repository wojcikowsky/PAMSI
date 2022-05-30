#include <iostream>
#include <fstream>
#include <chrono>
#include "graph_matrix.h"
#include "graph_list.h"
#include "my_doubly_list.h"

#define QUAN 100

using namespace std;

int main()
{
	double dens;
	int tops;
	char menu = '\0';
	string in_file_name = "input.txt";
	string out_file_name = "output.txt";
	ifstream in_file;
	ofstream out_file;
	srand(time(NULL));

	clock_t start;

	graph_matrix<int> matrix[QUAN];
	graph_list<int> list[QUAN];

	while (menu != 'k') {

		cout << "a - Dijkstra, macierz, pliki" << endl;
		cout << "b - Bellman-Ford, macierz, pliki" << endl;
		cout << "c - Dijkstra, macierz, pomiar" << endl;
		cout << "d - Bellman-Ford, macierz, pomiar" << endl;
		cout << "e - Dijkstra, lista, pliki " << endl;
		cout << "f - Bellman-Ford, lista, pliki" << endl;
		cout << "g - Dijkstra, lista, pomiar" << endl;
		cout << "h - Bellman-Ford, lista, pomiar" << endl;
		cin >> menu;
		switch (menu)
		{
		case 'a':
			in_file.open(in_file_name);
			matrix[0].load(in_file);
			in_file.close();

			matrix[0].dijkstra();

			out_file.open(out_file_name);
			matrix[0].save(out_file);
			matrix[0].print(out_file);
			out_file.close();
			matrix[0].delete_graph();
			break;
		case 'b':
			in_file.open(in_file_name);
			matrix[0].load(in_file);
			in_file.close();

			matrix[0].bellmanford();

			out_file.open(out_file_name);
			matrix[0].save(out_file);
			out_file.close();
			matrix[0].delete_graph();
			break;
		case 'c':
			cout << "Podaj gestosc i ilosc wierzcholkow grafu" << endl;
			cin >> dens;
			cin >> tops;
			for (int i = 0; i < QUAN; i++)
			{
				matrix[i].fill(dens, tops); //gestosc i wierzcholki
				cout << i << " ";
			}
			cout << endl;
			start = clock();
			for (int i = 0; i < QUAN; i++)
			{
				matrix[i].dijkstra();
				cout << i << " ";
			}
			cout << endl << "Operacja trwala: " << clock() - start << "ms" << endl;

			//dodatkowy zapis macierzy do pliku "macierz.txt"
			out_file.open("macierz.txt");
			matrix[0].print(out_file);
			out_file.close();

			for (int i = 0; i < QUAN; i++)
			{
				matrix[i].delete_graph();
				cout << i << " ";
			}
			cout << endl;
			
			break;
		case 'd':
			cout << "Podaj gestosc i ilosc wierzcholkow grafu" << endl;
			cin >> dens;
			cin >> tops;
			for (int i = 0; i < QUAN; i++)
			{
				matrix[i].fill(dens, tops); //gestosc i wierzcholki
				cout << i << " ";
			}
			cout << endl;
			start = clock();
			for (int i = 0; i < QUAN; i++)
			{
				matrix[i].bellmanford();
				cout << i << " ";
			}
			cout << endl << "Operacja trwala: " << clock() - start << "ms" << endl;

			for (int i = 0; i < QUAN; i++)
			{
				matrix[i].delete_graph();
				cout << i << " ";
			}
			cout << endl;
			break;
		case 'e':
			in_file.open(in_file_name);
			list[0].load(in_file);
			in_file.close();

			list[0].dijkstra();

			out_file.open(out_file_name);
			list[0].save(out_file);
			out_file.close();
			list[0].delete_graph();
			break;
		case 'f':
			in_file.open(in_file_name);
			list[0].load(in_file);
			in_file.close();

			list[0].bellmanford();

			out_file.open(out_file_name);
			list[0].save(out_file);
			out_file.close();
			list[0].delete_graph();
			break;
		case 'g':
			cout << "Podaj gestosc i ilosc wierzcholkow grafu" << endl;
			cin >> dens;
			cin >> tops;
			for (int i = 0; i < QUAN; i++)
			{
				list[i].fill(dens, tops); //gestosc i wierzcholki
				cout << i << " ";
			}
			cout << endl;
			start = clock();
			for (int i = 0; i < QUAN; i++)
			{
				list[i].dijkstra();
				cout << i << " ";
			}
			cout << endl << "Operacja trwala: " << clock() - start << "ms" << endl;

			for (int i = 0; i < QUAN; i++)
			{
				list[i].delete_graph();
				cout << i << " ";
			}
			cout << endl;
			break;
		case 'h':
			cout << "Podaj gestosc i ilosc wierzcholkow grafu" << endl;
			cin >> dens;
			cin >> tops;
			for (int i = 0; i < QUAN; i++)
			{
				list[i].fill(dens, tops); //gestosc i wierzcholki
				cout << i << " ";
			}
			cout << endl;
			start = clock();
			for (int i = 0; i < QUAN; i++)
			{
				list[i].bellmanford();
				cout << i << " ";
			}
			cout << endl << "Operacja trwala: " << clock() - start << "ms" << endl;

			for (int i = 0; i < QUAN; i++)
			{
				list[i].delete_graph();
				cout << i << " ";
			}
			cout << endl;
			break;
		}
	}
	return 0;
}
