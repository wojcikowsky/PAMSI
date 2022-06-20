#include "AI.h"
#include <vector>

/*!
 *  \brief Funkcja oblicza glebokosc rekurencji, oblicza najlepszy ruch i go wykonuje
 */
void AI::move(play_board& tab)
{
	int depth = 30/(3 * tab.get_size() - 2 * tab.get_row() + 1);
	AI_move final_move = best_move(tab, 'X', depth);
	tab.set(final_move.x, final_move.y, 'X');
}

/*!
 *  \brief Funkcja analizje stan gry i szuka najbardziej optymalnegu ruchu
 *
 *  \param[in] tab - tablica gry
 *  \param[in] current_player - gracz, ktory aktualnie wykonuje ruch
 *  \param[in] depth - glebokosc wykonwyania reukrencji
 *
 *  \retval Zwraca optymalny ruch i jego wartoœæ
 */
AI_move AI::best_move(play_board& tab, char current_player, int depth)
{
	char score = tab.check_win(); //Sprawdzamy koniec rekurencji

	depth--;
	if (depth < 0) //Sprawdzamy glebokosc rekurencji
	{
		return AI_move(0);
	}

	/*Sprawdzamy, czy ktorys z graczy nie wygral lub nie ma remisu*/
	if (score == 'X') 
	{
		return AI_move(100 + depth);
	}
	if (score == 'O')
	{
		return AI_move(-100 + depth);
	}
	if (score == 'T')
	{
		return AI_move(depth);
	}

	std::vector<AI_move> moves_mem; //Vector przechowujacy sciezke ruchow

	/*Analizujemy wszystkie mo¿liwe konfiguracje ruchow poszukujac optymalnego ruchu*/
	for (int i = 0; i < tab.get_size(); i++)
	{
		for (int j = 0; j < tab.get_size(); j++)
		{
			if (tab.check_cell(i, j) == '\0')
			{
				AI_move move(0);
				move.x = i; 
				move.y = j;
				tab.set(i, j, current_player); //Stawiamy znak iterujac dalej

				if (current_player == 'X') //Ruchy w analizie uwzgledniaja zmiane graczy
				{
					move.score = best_move(tab, 'O', depth).score;
				}
				else
				{
					move.score = best_move(tab, 'X', depth).score;
				}
				moves_mem.push_back(move);
				tab.set(i, j, '\0'); //Przywracamy tablice sprzed analizy
			}
		}
	}

	int best_index = 0;

	if (current_player == 'X') //Wybranie optymalnego ruchu dla kazdego z graczy
	{
		int best_score = -1000000; //Optymalny ruch dla AI
		for (int i = 0; i < moves_mem.size(); i++)
		{
			if (moves_mem[i].score > best_score)
			{
				best_index = i;
				best_score = moves_mem[i].score;
			}
		}
	}
	else
	{
		int best_score = 1000000; //Optymalny ruch dla przeciwnika
		for (int i = 0; i < moves_mem.size(); i++)
		{
			if (moves_mem[i].score < best_score)
			{
				best_index = i;
				best_score = moves_mem[i].score;
			}
		}
	}
	return moves_mem[best_index]; //Zwracamy najlepszy znaleziony ruch
}
