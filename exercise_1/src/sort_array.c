
#include <time.h>
#include "sort_array.h"

int binary_search(void ** base, void * item, int low, int high, int (* cmpr)(void *, void *));
int partition_Lomuto(void ** base, int low, int high, int (* cmpr)(void *, void *));
int partition_Hoares(void ** base, int low, int high, int (* cmpr)(void *, void *));
int partition_Hoares_r(void ** base, int low, int high, int (* cmpr)(void *, void *));
void swap(void * a, void * b);

void b_insertion_sort(void ** base, size_t n_elem, int (* cmpr)(void *, void *)){
	if(base == NULL) {
		fprintf(stderr, "b_insertion_sort: base can not be NULL. \n");
		exit(EXIT_FAILURE);
	}
	if(cmpr == NULL) {
        fprintf(stderr, "b_insertion_sort: base can not be NULL. \n");
        exit(EXIT_FAILURE);
    }
	int i, j, index;
	void * key;
	for (i=1; i<n_elem; i++) {
		key = base[i];
		j = i-1;
		index = binary_search(base, key, 0, j, cmpr);
		while(j>=index) {		/*base[j]>key*/
			//printf("swap\n");
			base[j+1] = base[j];
			j--;
		}
		base[j+1]=key;
	}
}

void quick_sort_Lomuto(void ** base, int low, int high, int (* cmpr)(void *, void *)){
    //termination condition
    if (low<high){
        //placing pivot element and storing its position
        int p = partition_Lomuto(base, low, high, cmpr);
        //recursively doing it for the both the halves on
        //either side of the lo element
        quick_sort_Lomuto(base, low, p - 1, cmpr);
        quick_sort_Lomuto(base, p + 1, high, cmpr);
    }
}


void quick_sort_Hoares(void ** base, int low, int high, int (* cmpr)(void *, void *)){
    if(low < high){
        int pi = partition_Hoares(base, low, high, cmpr);
        quick_sort_Hoares(base, low, pi, cmpr);
        quick_sort_Hoares(base, pi+1, high, cmpr);
    }
}

void quick_sort_Hoares_r(void ** base, int low, int high, int (* cmpr)(void *, void *)){
    if(low < high){
        int pi = partition_Hoares_r(base, low, high, cmpr);

        quick_sort_Hoares(base, low, pi, cmpr);
        quick_sort_Hoares(base, pi+1, high, cmpr);
    }
}

int binary_search(void ** base, void * item, int low, int high, int (* cmpr)(void *, void *)){
    if (high <= low) {
        if (((cmpr)(base[low], item)) < 0)
            return low + 1;
        else
            return low;
    }
	int mid = (low + high) / 2;
    int a = ((cmpr)(item, base[mid]));
	if (a == 0)
		return mid + 1;

	if (a > 0)
		return binary_search(base, item, mid+1, high, cmpr);
	return binary_search(base, item, low, mid-1, cmpr);
}

int partition_Lomuto(void ** base, int low, int high, int (* cmpr)(void *, void *)){
    void * temp;
    void * pivot = base[high];
    int i = low-1;

    for (int j=low; j<=high-1; j++) {
        if((cmpr(base[j], pivot)) <= 0){
            i++;
            temp=base[i];
            base[i]=base[j];
            base[j]=temp;
        }
    }
    temp=base[i+1];
    base[i+1]=base[high];
    base[high]=temp;
    return (i+1);
}

int partition_Hoares(void ** base, int low, int high, int (* cmpr)(void *, void *)){
    void * pivot = base[low];
    void * temp;
    int i = low-1, j = high+1;
    while (1){
        do {
            i++;
        } while((cmpr(base[i], pivot))<0);

        do {
            j--;
        } while((cmpr(base[j], pivot))>0);

        if (i>=j)
            return j;
        temp=base[i];
        base[i]=base[j];
        base[j]=temp;
    }
}


int partition_Hoares_r(void ** base, int low, int high, int (* cmpr)(void *, void *)){
    srand(time(0));
    int random = low + rand() % (high - low);
    void *temp = base[random];
    base[random] = base[low];
    base[low] = temp;

    void *pivot = base[low];
    int i = low-1, j = high+1;
    while (1){
        do {
            i++;
        } while((cmpr(base[i], pivot))<0);

        do {
            j--;
        } while((cmpr(base[j], pivot))>0);

        if (i>=j)
            return j;
        temp=base[i];
        base[i]=base[j];
        base[j]=temp;
    }
}
