#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../Resources/C/Unity/unity.h"
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



/*
Genera un csv con valori casuali del tipo indicato di dimensione (numero righe) pari alla size data in input
Criterio di generazione:
id: intero crescente sempre differente
field1: "field1_example"
field2: intero da size a 0
field3: float generato randomicamente
*/
static void generateCSVFile(int size) {
    FILE *fp;
    unsigned seed;

    if(!size){
       fp = fopen("dataset/test.csv", "w+");
       fclose(fp);
    }else{
        fp = fopen("dataset/test.csv", "w+");
        srand(seed);
        int i;
        /* Genero numeri inversament eproporzionali alla grandezza del file
           es size =4
              (id=i=0, char="field1_example", int=4, float= rand%)
              (id=i=1, char="field1_example", int=3, float= rand%)
              (id=i=2, char="field1_example", int=2, float= rand%)
              (id=i=3, char="field1_example", int=1, float= rand%)
        */
        for(i = 0; i < size; i++)
            fprintf(fp, "%d,%s,%d,%f\n", i, "field1_example", size-i, (float)rand()/(float)(RAND_MAX/100));
        fclose(fp);
    }
}

static void removeCSVFile() {
    system("rm ./dataset/test.csv");
}

//TODO: TESTS for Binary search / Binary Inserction sort


static void structureCreateZeroSizedArray() {


  compareFunction myCompareFunction = (compareFunction)compareField1;

  // compareFunction myCompareFunction = (compareFunction)compareField2;

  // compareFunction myCompareFunction = (compareFunction)compareField3;

  Structure* myStructure = structureNew();

  TEST_ASSERT_EQUAL(0, structureSize(myStructure));
  structureFree(myStructure);
}


static void structureSortOneSizedArray() {
  compareFunction myCompareFunction = (compareFunction)compareField1;
  // compareFunction myCompareFunction = (compareFunction)compareField2;
  // compareFunction myCompareFunction = (compareFunction)compareField3;

  Structure* myStructure = structureNew();
  Record* rec;

  //Creating the csv file and filling the structure with the records
  generateCSVFile(1);
  readFile(myStructure, "./dataset/test.csv");

  //Check if the size of the structure is equal to 1
  TEST_ASSERT_EQUAL(1, structureSize(myStructure));

  //Ordering with quicksort the field of type specified by the proper compare function
  genericQuickSort(myStructure, 0, structureSize(myStructure)-1, myCompareFunction);
  //Getting the 1st and only one record
  rec = structureGet(myStructure, 0);

  /* FOR DEBUG
  printf("rec->field1: %d, %s, %d, %f\n", rec->id, rec->field1, rec->field2, rec->field3);
  */

  //Checking if the result is what I expect it to be [FILL THE DOTS WITH THE VALUE I EXPECT]
  //TEST_ARRERT_EQUAL(" ", rec->field1) // string
  TEST_ASSERT_EQUAL(1, rec->field2); // int
  //TEST_ARRERT_EQUAL(, rec->field3) //floating point
  removeCSVFile();
  structureFree(myStructure);

  //Binary-Inserction-Sort section
  myStructure = structureNew();
  rec;

  generateCSVFile(1);
  readFile(myStructure, "./dataset/test.csv");

  TEST_ASSERT_EQUAL(1, structureSize(myStructure));
  insertionSort(myStructure, structureSize(myStructure), myCompareFunction);
  rec = structureGet(myStructure, 0);

  TEST_ASSERT_EQUAL(1, rec->field2);

  removeCSVFile();
  structureFree(myStructure);
}


static void structureSortGenericSizedArray() {

//compareFunction myCompareFunction = (compareFunction)compareField1;
 compareFunction myCompareFunction = (compareFunction)compareField2;
// compareFunction myCompareFunction = (compareFunction)compareField3;

  Structure* myStructure = structureNew();
  Record* rec;

  //Creating the csv file and filling the structure with the records
  generateCSVFile(5);
  readFile(myStructure, "./dataset/test.csv");


  TEST_ASSERT_EQUAL(5, structureSize(myStructure));
    /*Verifico l'ordinamento dei campi sul field 2 con l'insertion sort*/

  genericQuickSort(myStructure,0,structureSize(myStructure)-1, myCompareFunction);

//Checking if quicksort ordered the array in function of the field specified
//  in the compare function
  rec = structureGet(myStructure, 0);
  TEST_ASSERT_EQUAL(1,rec->field2);

  rec= structureGet(myStructure,1);
  TEST_ASSERT_EQUAL(2,rec->field2);

  rec= structureGet(myStructure,2);
  TEST_ASSERT_EQUAL(3,rec->field2);

  rec= structureGet(myStructure,3);
  TEST_ASSERT_EQUAL(4,rec->field2);

  rec= structureGet(myStructure,4);
  TEST_ASSERT_EQUAL(5,rec->field2);

  removeCSVFile();
  structureFree(myStructure);

//Binary-Insertion-Sort section
  myStructure = structureNew();
  rec;

  generateCSVFile(5);
  readFile(myStructure, "./dataset/test.csv");

  TEST_ASSERT_EQUAL(5, structureSize(myStructure));

  insertionSort(myStructure, structureSize(myStructure), myCompareFunction);

  rec = structureGet(myStructure, 0);
  TEST_ASSERT_EQUAL(1,rec->field2);

  rec= structureGet(myStructure,1);
  TEST_ASSERT_EQUAL(2,rec->field2);

  rec= structureGet(myStructure,2);
  TEST_ASSERT_EQUAL(3,rec->field2);

  rec= structureGet(myStructure,3);
  TEST_ASSERT_EQUAL(4,rec->field2);

  rec= structureGet(myStructure,4);
  TEST_ASSERT_EQUAL(5,rec->field2);

  removeCSVFile();
  structureFree(myStructure);

}


int main(){
  UNITY_BEGIN();

  RUN_TEST(structureCreateZeroSizedArray);
  RUN_TEST(structureSortOneSizedArray);
  RUN_TEST(structureSortGenericSizedArray);

  UNITY_END();
}
