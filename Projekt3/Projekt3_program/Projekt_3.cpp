/**
 *  Projekt_3.cpp
 *  Purpose: Kolko i krzyzyk z wykorzystaniem algorytmu MinMax
 *  @author Pawel Wojcik
 */

#include <iostream>
#include "play_board.h"
#include "AI.h"

using namespace std;

int main()
{
    int size = 0;
    int winrow;
    char player_sign = '\0';
   
    cout << "Kolko i krzyzyk - Tic Tac Toe" << endl << endl;
    
    while (size <= 2) //Pobranie danych o wielkosci planszy, ilosci znakow i pierwszym graczu
    {
        cout << "Podaj wielkosc planszy: ";
        cin >> size;
        if (size <= 2)
            cout << "Zla wartosc" << endl; 
    }
    winrow = size + 1;
    while (winrow > size)
    {
        cout << "Podaj ilosc znakow potrzebna do wygranej: ";
        cin >> winrow;
        if(winrow > size)
            cout << "Zla wartosc" << endl;
    }
    while (player_sign != 'X' && player_sign != 'O')
    {
        cout << "Wybierz kto ma zaczac [O- gracz/X- AI]: ";
        cin >> player_sign;
        if (player_sign != 'X' && player_sign != 'O')
            cout << "Zly znak" << endl;

    }

    play_board board(size, winrow); //Powolanie tablicy do gry
    AI AI_player; //Powolanie gracza AI

    board.display(); //Wyswietlamy plansze gry
    
    int i, j;
    
    if (player_sign == 'X') //Jeżeli zaczyna AI to stawia znak na srodku planszy
    {
        board.set(size / 2, size / 2, 'X');
        board.display();
    }
    while (1)
    {
        cin >> i >> j;
        while (board.check_cell(i ,j) != '\0')
        {
            cout << " To pole jest juz zajete" << endl;
            cin >> i >> j;
        }
        board.set(i, j, 'O');
        board.display();
        
        if (board.check_win() == 'O')
        {
            cout << "Gra zakonczona, wygral O" << endl;
            return 1;
        }
        if (board.check_win() == 'T')
        {
            cout << "Gra zakonczona remisem";
            return 3;
        }

        AI_player.move(board);
        board.display();

        if (board.check_win() == 'X')
        {
            cout << "Gra zakonczona, wygral X" << endl;
            return 2;
        }
        if (board.check_win() == 'T')
        {
            cout << "Gra zakonczona remisem" << endl;
            return 3;
        }
    
    }
    return 0;
}
