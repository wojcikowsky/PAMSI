#pragma once
/*
 *  Plik zawiera definicje klasy AI i struktury AI_move
 */

#include "play_board.h"

/*Struktura przechowuje wspolrzedne ruchu i jego wartosc*/
struct AI_move
{
	AI_move(int s) { score = s; }; //Konstruktor struktury przpisujacy wartosc score
	int x, y, score; //Wspolrzedne i wartosc ruchu
};

class AI
{
	AI_move best_move(play_board& tab, char current_player, int depth); //Ruch gracza AI

public:
	void move(play_board& tab); //Algorytm rekurencyjny MinMax
};

