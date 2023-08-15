#include "skiplist.h"
#include <time.h>
// Used this command to see mem leak on executable file with valgrind tool
//    valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind-out.txt -s --track-origins=yes --verbose ./main

int main(int argc, char *argv[]){ //arg1 = "../dataset/dictionary.txt" arg2 = "../dataset/correctme.txt"
    //1) MAX_HEIGHT = 20 -> readFile took 4.970000 / checkPhrase took 0.066000 / deallocazione took 0.377000
    //2) MAX_HEIGHT = 10 -> non riesce nemmeno a leggere il file
    //3) MAX_HEIGHT = 15 -> readFile took 5.155000 / checkPhrase took 0.079000 / deallocazione took 0.469000
    //4) MAX_HEIGHT = 30 -> readFile took 4.416000 (VM 3.151380) / checkPhrase took 0.066000 (VM 0.000597) / deallocazione took 0.394000 (VM 0.202734)

//Initializzating Skiplist
    clock_t t;
    double time_taken;

    char* datasetDictionary;
    char* datasetCorrectme;
    if(argc!=3) {
     printf("Parameters error %d\n", argc);
     exit(1);
   }
   datasetDictionary = argv[1];
   datasetCorrectme = argv[2];

    printf("Creating new skiplist\n");
    SkipList* skl = newSkipList(compareField1);
    printf("Skiplist created\n");


//Reading file Dictionary and Insering Item in the Skiplist
    printf("start reading dictionary\n");
    t = clock();
    readFile1(skl, datasetDictionary);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("\nreadFile1 took %f seconds to read the file: %s \n", time_taken, datasetDictionary);

//Printing the items in teh skiplist by levels (WARNING Use it ONLY with few Nodes in Linked List)
    //SkipList_print(skl);

// Reading file correctme
    // For each word read, call the search function
    // If IS NOT found, PRINT the item, Otherwise do nothing
    printf("start checking...\n");
    t = clock();
    checkPhrase(skl, datasetCorrectme);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("\ncheckPhrase took %f seconds to read the file: %s \n", time_taken, datasetCorrectme);


// Deallocating skiplist
    printf("\ndeallocating... \n");
    t = clock();
    deleteSkipList(skl);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("\ndeallocazione took %f seconds \n", time_taken);
    printf("end\n");
}

