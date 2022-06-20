#pragma once
/* 
 * Plik zawiera definicje klasy play_board 
 */

#include <iostream>

using namespace std;

class play_board
{
	char** tab; //Tablica przechowujaca stan gry
	int size, winrow; //Rozmiar tablicy i rzad potrzebny do wygrania

public: 
	play_board(int s, int w);
    void display();
	char check_cell(int x, int y);
	void set(int x, int y, char c);
	int get_size() { return size; }; //Zwraca wilkosc tablicy
	int get_row() { return winrow; }; //Zwraca wielkosc rzedu potrzebnego do wygrania
	char check_win();
};