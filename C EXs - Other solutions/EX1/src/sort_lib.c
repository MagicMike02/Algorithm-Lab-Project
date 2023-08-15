#include "structure.h"
#include "sort_lib.h"

//TODO: Binary search / Binary Inserction sort codes

void swap(Structure* structure , int a, int b){
  // swap pointers
  void* temp;
  temp = structure->array[a];
  structure->array[a]=structure->array[b];
  structure->array[b]=temp;
}

int Random(int min, int max){
  int n = (rand() % (max - min + 1))+ min;
  return n;
}

int partitionLeft(Structure* structure, int min, int max, compareFunction cmpFun){
  int pivot = min; //elemento pi� a sinistra
  int i = (max + 1); //puntatore
  for(int j = max; j > min; j--){
    if(cmpFun( structureGet(structure,j) , structureGet(structure, pivot) ) >= 0){
    //if(structure-> array[j]>=pivot){ //se elemento >= pivot
      i--; //si sposta il puntatore
      swap(structure, i, j);
    }
  }
  swap(structure, (i-1), min);

  return (i-1);
}

int partitionRight(Structure* structure, int min, int max, compareFunction cmpFun){
	 // select the rightmost element as pivot
  int pivot = max;

  // pointer for greater element
  int i = (min - 1); //-1

  // traverse each element of the array
  // compare them with the pivot
  for (int j = min; j < max; j++) {

    if(cmpFun( structureGet(structure,j) , structureGet(structure, pivot) ) <= 0){
    //if (structure->array[j] <= pivot) {

      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++; // second pointer

      // swap element at i with element at j
      swap(structure, i, j);
    }
  }
  // swap the pivot element with the greater element at i
  swap(structure, (i+1), max);

  // return the partition point
  return (i + 1);
}

/*
  With large inputs, random partitions provide better performances in the average case.
  We pick as a pivot a random element in the array array[min, ..., max] instead of array[min] or array[max].
*/
int partitionRandom(Structure* structure, int min, int max, compareFunction cmpFun){
  int i = Random(min, max);
  swap(structure, max, i);
  return partitionRight(structure, min, max, cmpFun);
}



int is_sorted(Structure* structure, compareFunction cmpFun){
	int i ;
	for(i = 0; i < structureSize(structure) - 1; i ++){
		if(cmpFun(structureGet(structure, i), structureGet(structure, i)) > 0){
			return -1;
		}
	}
	return 1;
}

void threeWayPartition(Structure* structure, int bottom_bound, int upper_bound, compareFunction cmpFun){
	if(upper_bound <= bottom_bound){
		return;
	}
	int lowest_index = bottom_bound;
	int i = bottom_bound + 1;
	int top_index = upper_bound;
	void* pivot = structureGet(structure, bottom_bound);

	while(i <= top_index){
		if(cmpFun(structureGet(structure, i), pivot) < 0){
			swap(structure, lowest_index++, i++);
		}
    else if(cmpFun(structureGet(structure, i), pivot) >= 0){
			swap(structure, i, top_index--);
		}
    else{
			i++;
		}
	}
	threeWayPartition(structure, bottom_bound, lowest_index - 1, cmpFun);
	threeWayPartition(structure, top_index + 1, upper_bound, cmpFun);
}


void genericQuickSort(Structure* structure, int min, int max, compareFunction cmpFun){
  if (min < max) {
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot

    /*
    int pivot = partitionLeft(structure, min, max, cmpFun);
    // recursive call on the left of pivot
    genericQuickSort(structure, min, pivot - 1, cmpFun);
    // recursive call on the right of pivot
    genericQuickSort(structure, pivot + 1, max, cmpFun);
    */

    /*
    int pivot = partitionRandom(structure, min, max, cmpFun);

    genericQuickSort(structure, min, pivot - 1, cmpFun);

    genericQuickSort(structure, pivot + 1, max, cmpFun);

    */

    /*
    int pivot = partitionRight(structure, min, max, cmpFun);

    genericQuickSort(structure, min, pivot - 1, cmpFun);

    genericQuickSort(structure, pivot + 1, max, cmpFun);
    */

   int i, j;
   /*
   threeWayPartition(structure, min, max, &i, &j, cmpFun);
   genericQuickSort(structure, min, j, cmpFun);
   genericQuickSort(structure, i, max, cmpFun);
   */

   threeWayPartition(structure, min, max, cmpFun);
   genericQuickSort(structure, min, i, cmpFun);
   genericQuickSort(structure, j, max, cmpFun);

  }
}

int binarySearch(Structure* structure, void* item, int low, int high, compareFunction cmpFun){
  if( high <= low){
    //item > a[low]
    if( cmpFun(item, structureGet(structure, low)) > 0 )
      return (low + 1);
    else
      return low;
  }

  int mid = (low + high) / 2;

  if(cmpFun(item , structureGet(structure, mid)) == 0)
    return mid + 1;

  if( cmpFun(item, structureGet(structure, mid)) > 0)
    return binarySearch(structure, item, mid + 1, high, cmpFun);

  return binarySearch(structure, item, low, mid -1, cmpFun);
}


void insertionSort(Structure* structure, int size, compareFunction cmpFun){
  int i, loc, j, k;
  void* item; //[id, s, i,f]

  for(i = 1; i < size; ++i){
    j = i-1;
    item = structureGet(structure, i);

    loc = binarySearch(structure, item, 0, j, cmpFun);

    while(j >= loc){
      structure->array[(j+1)] = structure->array[(j)];
      j--;
    }
    structure->array[(j+1)] = item;
  }
}
