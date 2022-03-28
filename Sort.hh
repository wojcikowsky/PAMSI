#pragma once

#include <iostream>
#include <cmath>

template<typename type>
void tab_gen(type* tab, int n);

template<typename type>
void reverse(type* tab, int n);

template<typename type>
int partition(type* tab, int left, int right);
template<typename type>
void quick_sort(type* tab, int left, int right);

template<typename type>
void quick_sort_reversed(type* tab, int left, int right, bool reverse);

template<typename type>
void merge(type* tab, int left, int middle, int right);
template<typename type>
void merge_sort(type* tab, int left, int right);

template<typename type>
void heapify(type* tab, int n, int i);
template<typename type>
void heap_sort(type* tab, int n);

template<typename type>
void insertion_sort(type* tab, int size);

template<typename type>
void intro_sort(type* tab, int size);

template<typename type>
int is_sorted_well(type* tab, int n, bool reverse);
