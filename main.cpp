#include "Sort.hh"
#include <chrono>

using namespace std;

int main() {
    int n = 1000000;
    int rows = 100;
    int** tab = new int* [rows];

    //Inicjalizacja
    for (int i = 0; i < rows;++i)
    {
        tab[i] = new int[n];
        tab_gen<int>(tab[i], n);
    }

    int preliminary_sort = n * 997 / 1000;//99,7% wstepnego posortowania
    for (int i = 0; i < rows;++i)
    {
        quick_sort(tab[i], 0, -1);
    }
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    //Sortowanie stu tablic
    for (int i = 0; i < rows;++i)
    {
        //merge_sort(tab[i], 0, n - 1);
        //quick_sort(tab[i], 0, n - 1);
        //reverse(tab[i], n);
        //insertion_sort(tab[i], n);
        //quick_sort_reversed<int>(tab[i], 0, n - 1, false);
        //heap_sort(tab[i], n);
        intro_sort(tab[i], n);
        is_sorted_well<int>(tab[i], n, false);
        /*cout << "\nPosortowane:\n";
        for (int j = 0; j < n; ++j)
        {
            cout << tab[i][j] << " ";
        }*/
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Czas sortowania = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;
    /*
        cout << "\nPosortowane:\n";
        for (int i = 0; i < n; ++i)
        {
            cout << tab[i] << " ";
        }
    */
}

