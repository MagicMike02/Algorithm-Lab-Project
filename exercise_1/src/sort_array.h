#ifndef SORT_ARRAY_H
#define SORT_ARRAY_H

#include <stdio.h>
#include <stdlib.h>


// Sorts a given array based on Insertion sort algorighm
void b_insertion_sort(void ** base, size_t n_elem, int (* cmpar)(void *, void *));

// Sorts a given array based on Quinck sort algorighm. This method uses the first element in the array as pivot
void quick_sort_Hoares(void ** base, int low, int high, int (* cmpr)(void *, void *));

// Sorts a given array based on Quinck sort algorighm. This method uses a random element in the array as pivot
void quick_sort_Hoares_r(void ** base, int low, int high, int (* cmpr)(void *, void *));

// Sorts a given array based on Quinck sort algorighm. This method uses the last element in the array as pivot
void quick_sort_Lomuto(void ** base, int low, int high, int (* cmpr)(void *, void *));

#endif

