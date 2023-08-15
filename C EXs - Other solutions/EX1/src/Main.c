#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "structure.h"
#include "sort_lib.h"
#define MAX_BUF_LEN 1024

// Compara il primo campo, tipo char
int compareField1(Record* rec1, Record* rec2) {

  // strcmp(s1, s2) restituisce un valore:
  // -) <0 se s1 � minore di s2
  // -) =0 se s1 � uguale a s2
  // -) >0 se s1 � maggiore di s2

  return strcmp(rec1->field1, rec2->field1);

}

// Compara secondo campo, tipo int
int compareField2(Record* rec1, Record* rec2) {
  return rec1->field2 - rec2->field2;
}

// Compara terzo campo, tipo float
int compareField3(Record* rec1, Record* rec2){

       if(rec1->field3 == rec2->field3) { return  0; }
  else if(rec1->field3 >  rec2->field3) { return  1; }
  else if(rec1->field3 <  rec2->field3) { return -1; }

}


// Stampa tutti i record della struttura
void printRecords(Structure* myStruct) {
  for(int i=0; i<structureSize(myStruct); i++){
    Record* tempRec = structureGet(myStruct, i);
    printf("%d,     %s,     %d,     %f\n", tempRec->id, tempRec->field1, tempRec->field2, tempRec->field3);
  }
}

void main(int argc, char *argv[]){
  clock_t t;
  double time_taken;
  compareFunction myCompareFunction;
  Structure* myStruct;


  char* datasetPath;
  if(argc!=2) {
   printf("Parameters error\n");
   exit(1);
 }
 datasetPath = argv[1];

/* --------- Load File -----------*/
myStruct= structureNew();

printf("\n load data...\n");
  t = clock();
  readFile(myStruct, datasetPath);
  t = clock() - t;
time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
printf("readFile took %f seconds to read the file: %s \n", time_taken, datasetPath);

  //prints the unordered array
  //printf("Unordered redcords:\n");
  //printRecords(myStruct);
/* ------------------------------ */


/* -------- COMPARING FIELD 1 -------- */


  myCompareFunction = (compareFunction)compareField1;

  printf("\nQuicksort: Ordering FIRST field...\n");
    t = clock();
    genericQuickSort(myStruct, 0, structureSize(myStruct)-1, myCompareFunction);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("Quicksort took %f FIRST to sort field1 \n", time_taken);

  printf("\nQuicksort: Ordered FIRST field with quicksort\n");
  //printRecords(myStruct);

  if(is_sorted(myStruct, myCompareFunction) > 0){
		printf("Is sorted\n");
	}else{
		printf("Not sorted\n");
	}

/*
  printf("Quicksort: free struct...\n");
  structureFree(myStruct);
*/
/* -------- END COMPARE FIELD 1 -------- */



/* -------- COMPARING FIELD 2 -------- */
//myStruct= structureNew();

  myCompareFunction = (compareFunction)compareField2;

  printf("\nQuicksort: Ordering Second field...\n");
    t = clock();
  genericQuickSort(myStruct, 0, structureSize(myStruct)-1, myCompareFunction);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("Quicksort took %f seconds to order 2nd field \n", time_taken);

  printf("\nQuicksort: Ordered SECOND field with quicksort\n");
  //printRecords(myStruct);

  printf("Quicksort: free struct...\n");
//structureFree(myStruct);

/* -------- END COMPARE FIELD 2 -------- */



/* --------COMPARING FIELD 3-------- */
//myStruct= structureNew();

  myCompareFunction = (compareFunction)compareField3;

  printf("\nQuicksort: Ordering THIRD field...\n");
    t = clock();
    genericQuickSort(myStruct, 0, structureSize(myStruct)-1, myCompareFunction);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  printf("Quicksort took %f seconds to read the file \n", time_taken);

  printf("\nQuicksort: Ordered THIRD field with quicksort\n");
  //printRecords(myStruct);

  printf("Quicksort: free struct...\n");
//structureFree(myStruct);

/* -------- END COMPARE FIELD 3 -------- */

structureFree(myStruct);


/* -------- BINARY INSERTION SORT --------
myStruct= structureNew();

  myCompareFunction = (compareFunction)compareField1;
  printf("\nB InsertionsSort: Ordering 1 field...\n");

    insertionSort(myStruct, structureSize(myStruct), myCompareFunction);
  printf("\nB InsertionsSort: Ordered 1 field with B InsertionsSort\n");
  printRecords(myStruct);


  myCompareFunction = (compareFunction)compareField2;
  printf("\nB InsertionsSort: Ordering 2 field...\n");

    insertionSort(myStruct, structureSize(myStruct), myCompareFunction);
  printf("\nB InsertionsSort: Ordered 2 field with B InsertionsSort\n");
  printRecords(myStruct);


  myCompareFunction = (compareFunction)compareField3;
  printf("\nB InsertionsSort: Ordering 3 field...\n");

    insertionSort(myStruct, structureSize(myStruct), myCompareFunction);
  printf("\nB InsertionsSort: Ordered 3 field with B InsertionsSort\n");
  printRecords(myStruct);


  printf("B InsertionsSort: free struct...\n");
  structureFree(myStruct);

*/

printf("COMPARING FIELDS FINISHED\n");
}
