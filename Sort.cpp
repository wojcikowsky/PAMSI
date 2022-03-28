#include "Sort.hh"
using namespace std;

template<typename type>
void tab_gen(type* tab, int n)
{
    srand(time(NULL)); //bez tego generowane liczby są takie same
    for (int i = 0; i < n; ++i)
    {
        tab[i] = rand();
    }
}

template<typename type>
void reverse(type* tab, int n)
{
    int tmp;
    for (int i = 0; i < n / 2; ++i)
    {
        tmp = tab[i];
        tab[i] = tab[n - 1 - i];
        tab[n - 1 - i] = tmp;
    }
}

/*Quick_sort wersja podzielona na dwie funkcje*/
template<typename type>
int partition(type* tab, int left, int right)
{
    if (left < right)
    {
        int p = left - 1;//bo we whilach mamy preinkrementację 
        int q = right + 1;
        int pivot = tab[(left + right) / 2];

        while (true)
        {
            while (pivot > tab[++p]);//szukaj elementu po lewej większego od pivota
            while (pivot < tab[--q]);
            if (p < q)//gdy p po lewej, q po prawej stronie pivota
            {
                swap(tab[p], tab[q]);
            }
            else
                return q;//gdy wszystkie elementy z lewej mniejsze od pivota... zwróć idx q
        }
    }
    return -1;
}

template<typename type>
void quick_sort(type* tab, int left, int right)
{
    int q = partition(tab, left, right);
    if (q > left)
        quick_sort(tab, left, q);//lewa połówka
    if ((q + 1) < right)
        quick_sort(tab, q + 1, right);//prawa połówka
}

/*Pierwsza wersja quicksorta, czyli partition i quick_sort w jednej
funkcji*/
template<typename type>
void quick_sort_reversed(type* tab, int left, int right, bool reverse)
{
    if (left >= right)
        return;

    int p = left - 1;
    int q = right + 1;
    int pivot = tab[(left + right) / 2];
    //Inwersja
    if (reverse) {
        while (true)
        {
            while (pivot < tab[++p]);
            while (pivot > tab[--q]);
            if (p <= q)
            {
                swap(tab[p], tab[q]);
            }
            else
                break;
        }
        /*Rozgałęzianie się funkcji*/
        if (q > left)
            quick_sort_reversed(tab, left, q, true);
        if (p < right)
            quick_sort_reversed(tab, p, right, true);
    }
    //Sortuj od najmniejszego do największego
    else {
        while (true)
        {
            while (pivot > tab[++p]);
            while (pivot < tab[--q]);
            if (p <= q)
            {
                swap(tab[p], tab[q]);
            }
            else
                break;
        }
        /*Rozgałęzianie się funkcji*/
        if (q > left)
            quick_sort_reversed(tab, left, q, false);
        if (p < right)
            quick_sort_reversed(tab, p, right, false);
    }
}

template<typename type>
void merge(type* tab, int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int L[n1], M[n2];//pomocnicze tablice mieszczące wszystkie elementy

    for (int i = 0; i < n1; ++i) {
        L[i] = tab[left + i];//z głównej do lewej tablicy
    }
    for (int j = 0; j < n2; ++j) {
        M[j] = tab[middle + 1 + j];//z głównej do prawej tablicy
    }
    int i, j, k;
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {//póki nie przekroczono zakresów tablic
        if (L[i] <= M[j]) {
            tab[k] = L[i];//wrzuć do głównej tablicy mniejszy element
            ++i;
        }
        else {
            tab[k] = M[j];
            ++j;
        }
        ++k;
    }
    //przepisz pozostałe elementy
    while (i < n1) {
        tab[k] = L[i];
        ++i;
        ++k;
    }
    //przepisz pozostałe elementy
    while (j < n2) {
        tab[k] = M[j];
        ++j;
        ++k;
    }
}

template<typename type>
void merge_sort(type* tab, int left, int right) {
    //Dziel problem aż do uzyskania pojedynczych elementów
    if (left < right) {
        int middle = (left + right) / 2;

        merge_sort(tab, left, middle);
        merge_sort(tab, middle + 1, right);

        //Podczas scalania sortuj
        merge(tab, left, middle, right);
    }
}

//Traktuje tablicę jako drzewo binarne
//heapify, czyli posortuj drzewo binarne od największego do najmniejszego
template<typename type>
void heapify(type* tab, int n, int i) {
    int largest = i;      //ojciec
    int left = 2 * i + 1; //dziecko po lewej
    int right = 2 * i + 2;//dziecko po prawej

    //dzieckoL<liczba elementow   wart.dzieckaL>wart.ojca
    if (left < n && tab[left] > tab[largest])
        largest = left; //ojciec = dziecko

    if (right < n && tab[right] > tab[largest])
        largest = right;

    // Jeśli nastąpiła zmiana w powyższych if-ach
    if (largest != i) {
        swap(tab[i], tab[largest]);//wrzuc nowego ojca na górę drzewa
        heapify(tab, n, largest);//rekurencyjne wywolanie
    }
}

//Traktuje tablicę jako drzewo binarne
template<typename type>
void heap_sort(type* tab, int n) {
    // max heap, czyli posortowane drzewo
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(tab, n, i);

    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
        swap(tab[0], tab[i]);//odłóż największą liczbę na koniec, zapomnij o niej

        // Posortuj drzewo od największego do najmniejszego
        heapify(tab, i, 0);
    }
}

//Wydajność O(n^2), więc tylko dla bardzo małych tablic
template<typename type>
void insertion_sort(type* tab, int size) {
    for (int i = 1; i < size; ++i) {
        int key = tab[i];
        int j = i - 1;
        //Porównuj klucz z każdym elementem po lewej dopóki nie trafisz na mniejszy od siebie
        while (key < tab[j] && j >= 0) {
            tab[j + 1] = tab[j];
            --j;
        }
        tab[j + 1] = key;
    }
}


template<typename type>
void intro_sort(type* tab, int size) {
    int partitionSize = partition(tab, 0, size - 1);

    if (partitionSize < 16)//wywoływane dla tablic poniżej 16 elementów
    {
        insertion_sort(tab, size);
    }
    else
    {
        quick_sort(tab, 0, size - 1);//standardowa sytuacja
    }
}

template<typename type>
int is_sorted_well(type* tab, int n, bool reverse)
{
    if (reverse) {
        for (int i = 0; i < n - 1; ++i)
        {
            if (tab[i] < tab[i + 1])
            {
                cout << "Something is working wrong!";
                return 1;
            }
        }
        return 0;
    }
    else {
        for (int i = 0; i < n - 1; ++i)
        {
            if (tab[i] > tab[i + 1])
            {
                cout << "Something is working wrong!";
                return 1;
            }
        }
        return 0;
    }
}



template void tab_gen<int>(int*, int);
template void reverse<int>(int*, int);
template int partition<int>(int*, int, int);
template void quick_sort<int>(int*, int, int);
template void merge<int>(int*, int, int, int);
template void merge_sort<int>(int*, int, int);
template void heapify<int>(int*, int, int);
template void heap_sort<int>(int*, int);
template void insertion_sort<int>(int*, int);
template void intro_sort<int>(int*, int);
template void quick_sort_reversed<int>(int*, int, int, bool);
template int is_sorted_well<int>(int*, int, bool);


template void tab_gen<double>(double*, int);
template void quick_sort_reversed<double>(double*, int, int, bool);
template int is_sorted_well<double>(double*, int, bool);
