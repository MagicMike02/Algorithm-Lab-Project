
//Effettua la swap tra due oggetti di indice i e j nella struttura passata in input
void swap(Structure* , int , int );

//Funzione di appoggio per il quicksort
int partitionRight(Structure* , int , int, compareFunction);
int partitionLeft(Structure* , int , int, compareFunction);
int partitionRandom(Structure* , int , int, compareFunction);

/*int threeWayPartition(Structure* , int , int , int* , int* , compareFunction );*/

int is_sorted(Structure* , compareFunction );

void threeWayPartition(Structure* , int , int , compareFunction );

void genericQuickSort(Structure* , int , int, compareFunction);

int binarySearch(Structure* , void* , int , int , compareFunction );

void insertionSort(Structure* , int , compareFunction );
