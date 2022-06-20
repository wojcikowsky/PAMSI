#include "play_board.h"

/*!
 *  \brief Konstruktor klasy play_board
 */
play_board::play_board(int s, int w)
{
    size = s;
    winrow = w;
    tab = new char* [size]; //Stworzenie tablicy kwadratowej o podanych wymiarach

    for (int i = 0; i < size; i++)
    {
        tab[i] = new char[size];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            tab[i][j] = '\0';
    }
}

/*!
 *  \brief Funkcja wyswietla aktualny stan gry
 */
void play_board::display()
{
    system("cls");
        
    cout << "  |";
    for (int i = 0; i < size; i++)
    {
        if (i > 9)
        cout << " " << i << "|";
        else
        cout << " " << i << " |";
    }
    cout << endl;

    cout << "__|";
    for (int i = 0; i < size; i++)
    {
        cout << "___|";
    }
    cout << endl;
    
    for (int j = 0; j < size; j++)
    {
        
        if (j > 9)
        cout << j << "|";
        else
        cout << j << " |";

        for (int i = 0; i < size; i++)
        {
            if(tab[j][i]=='\0')
                cout << " " << " " << " |";
            else
            cout << " " << tab[j][i] << " |";
        }
        
        cout << endl << "__|";
        for (int i = 0; i < size - 1; i++)
        {
            cout << "___|";
        }
        cout << "___|" << endl;
    }

}

/*!
 *  \brief Funkcja zwraca znak jaki aktualnie znajduje sie w przekazanej komorce
 *
 *  \param[in] x - wspolrzedna x komorki
 *  \param[in] y - wspolrzedna y komorki
 *
 *  \retval Znak jaki znajduje sie w komorce lub 'E' jezeli cos nieprzewidywanego
 */
char play_board::check_cell(int x, int y)
{
    if (tab[x][y] == 'X')
        return 'X';
    if (tab[x][y] == 'O')
        return 'O';
    if (tab[x][y] == '\0')
        return '\0';

    return 'E';
}

/*!
 *  \brief Funkcja przypisuje przekazany znak przekazanej komorce
 *
 *  \param[in] x - wspolrzedna x komorki
 *  \param[in] y - wspolrzedna y komorki
 *  \param[in] c - znak jaki ma zostac wstawiony do komorki
 *
 */
void play_board::set(int x, int y, char c)
{
    tab[x][y] = c;
}

/*!
 *  \brief Funkcja sprawdza czy nie nastapil koniec gry przez wygrana lub remis
 * 
 *  \retval Zwraca znak wygranego, 'T' jezeli remis i '\0' jezeli nie nastapil koniec gry
 */
char play_board::check_win()
{
    int quanX = 0, quanO = 0, count = 0;
    int i = 0, j = 0;

    /*Sprawdzenie wierszy*/
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (tab[i][j] == 'X')
            {
                quanX++;
                quanO = 0;
            }

            if (tab[i][j] == 'O')
            {
                quanO++;
                quanX = 0;
            }

            if (tab[i][j] == '\0')
            {
                quanX = 0;
                quanO = 0;
                count++;
            }

            if (quanX >= winrow)
            {
                return 'X';
            }
            if (quanO >= winrow)
            {
                return 'O';
            }
        }
        quanX = 0;
        quanO = 0;
    }

    /*Sprawdzenie kolumn*/
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (tab[j][i] == 'X')
            {
                quanX++;
                quanO = 0;
            }

            if (tab[j][i] == 'O')
            {
                quanO++;
                quanX = 0;
            }

            if (tab[j][i] == '\0')
            {
                quanX = 0;
                quanO = 0;
            }

            if (quanX >= winrow)
            {
                return 'X';
            }
            if (quanO >= winrow)
            {
                return 'O';
            }
        }
        quanX = 0;
        quanO = 0;
    }

    /*Sprawdzenie przekatnych 1*/
    i = 0;
    j = size - winrow;
    int k = j;

    for (j = winrow - 1; j < size - 1; j++)
    {
        i = 0;
        k = j;
        while (i < size && k < size)
        {
            if (tab[i][k] == 'X')
            {
                quanX++;
                quanO = 0;
            }

            if (tab[i][k] == 'O')
            {
                quanO++;
                quanX = 0;
            }

            if (tab[i][k] == '\0')
            {
                quanX = 0;
                quanO = 0;
            }
            i++;
            k--;
            if (quanX >= winrow)
            {
                return 'X';
            }
            if (quanO >= winrow)
            {
                return 'O';
            }
        }
        quanX = 0;
        quanO = 0;
    }

    for (j = 0; j <= size - winrow; j++)
    {
        i = 0;
        k = j;
        while (i < size && k < size)
        {
            if (tab[i][k] == 'X')
            {
                quanX++;
                quanO = 0;
            }

            if (tab[i][k] == 'O')
            {
                quanO++;
                quanX = 0;
            }

            if (tab[i][k] == '\0')
            {
                quanX = 0;
                quanO = 0;
            }
            i++;
            k++;


            if (quanX >= winrow)
            {
                return 'X';
            }
            if (quanO >= winrow)
            {
                return 'O';
            }
        }
        quanX = 0;
        quanO = 0;
    }

    /*Sprawdzenie przekatnych 2*/
    for (j = size - winrow; j < size; j++)
    {
        i = 0;
        k = j;
        while (i < size && k < size)
        {
            if (tab[k][i] == 'X')
            {
                quanX++;
                quanO = 0;
            }

            if (tab[k][i] == 'O')
            {
                quanO++;
                quanX = 0;
            }

            if (tab[k][i] == '\0')
            {
                quanX = 0;
                quanO = 0;
            }
            i++;
            k++;
            if (quanX >= winrow)
            {
                return 'X';
            }
            if (quanO >= winrow)
            {
                return 'O';
            }
        }
        quanX = 0;
        quanO = 0;
    }

    for (j = 0; j <= size - winrow; j++)
    {
        i = size - 1;
        k = j;
        while (i < size && k < size)
        {
            if (tab[k][i] == 'X')
            {
                quanX++;
                quanO = 0;
            }

            if (tab[k][i] == 'O')
            {
                quanO++;
                quanX = 0;
            }

            if (tab[k][i] == '\0')
            {
                quanX = 0;
                quanO = 0;
            }
            i--;
            k++;
            if (quanX >= winrow)
            {
                return 'X';
            }
            if (quanO >= winrow)
            {
                return 'O';
            }
        }
        quanX = 0;
        quanO = 0;
    }

    if (count == 0)
        return 'T'; //Jezeli brak wolnych pol to zwracamy remis
    else
        return '\0'; //Jezeli brak wygranego i istnieja wolne pola to zwracamy '\0' 
}