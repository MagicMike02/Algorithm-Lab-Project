#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "sort_array.h"
#define CAPACITY    20000000


/*
 *
 */


struct record{
    char* string_field;
    int integer_field;
    float real_field;
};

//It takes as input two pointers to struct record.
//It returns 1 iff the integer field of the first record is less than
//the integer field of the second one (0 otherwise)
int precedes_record_int_field(void* r1_p,void* r2_p){
    if(r1_p == NULL){
        fprintf(stderr,"precedes_record_int_field: the first parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    if(r2_p == NULL){
        fprintf(stderr,"precedes_record_int_field: the second parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    struct record *rec1_p = (struct record*)r1_p;
    struct record *rec2_p = (struct record*)r2_p;
    if(rec1_p->integer_field > rec2_p->integer_field)
        return(1);
    else if (rec1_p->integer_field < rec2_p->integer_field)
        return(-1);
    else
        return (0);
}


//It takes as input two pointers to struct record.
//It returns 1 iff the float field of the first record is less than
//the float field of the second one (0 otherwise)
int precedes_record_real_field(void* r1_p,void* r2_p){
    if(r1_p == NULL){
        fprintf(stderr,"precedes_record_real_field: the first parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    if(r2_p == NULL){
        fprintf(stderr,"precedes_record_real_field: the second parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    struct record *rec1_p = (struct record*)r1_p;
    struct record *rec2_p = (struct record*)r2_p;
    if(rec1_p->real_field > rec2_p->real_field)
        return(1);
    else if (rec1_p->real_field < rec2_p->real_field)
        return(-1);
    else
        return (0);
}








///It takes as input two pointers to struct record.

static int precedes_record_string_field(void* r1_p,void* r2_p){
    if(r1_p == NULL){
        fprintf(stderr,"precedes_string: the first parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    if(r2_p == NULL){
        fprintf(stderr,"precedes_string: the second parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    struct record *rec1_p = (struct record*)r1_p;
    struct record *rec2_p = (struct record*)r2_p;
//    printf("str 1: %s, str 2: %s. result of comparison: %d \n", rec1_p->string_field,rec2_p->string_field, strcasecmp(rec1_p->string_field,rec2_p->string_field));

    return strcasecmp(rec1_p->string_field,rec2_p->string_field);
}




void print_array(void** array){
//    int el_num = 20 ;

    struct record *array_element;

    printf("\nARRAY OF RECORDS\n");

    for(int i=0;i<CAPACITY;i++){
        array_element = (struct record *)array[i];
//        printf("<%s,%d>\n",((struct record *)array[i])->string_field,((struct record *)array[i])->integer_field);
        printf("<%s,%d,%f>\n",array_element->string_field,array_element->integer_field,array_element->real_field);
    }
}

void load_array(const char* file_name, void** array){
    int el_counter = 0;
    char *read_line_p;
    char buffer[1024];
    int buf_size = 1024;
    FILE *fp;
    printf("\nLoading data from file...\n");
    fp = fopen(file_name,"r");
    if(fp == NULL){
        fprintf(stderr,"main: unable to open the file");
        exit(EXIT_FAILURE);
    }
    while(fgets(buffer,buf_size,fp) != NULL && el_counter<CAPACITY){
        read_line_p = malloc((strlen(buffer)+1)*sizeof(char));
        if(read_line_p == NULL){
            fprintf(stderr,"main: unable to allocate memory for the read line");
            exit(EXIT_FAILURE);
        }
        strcpy(read_line_p,buffer);
        strtok(read_line_p, ",");
        char *string_field_in_read_line_p = strtok(NULL,",");
        char *integer_field_in_read_line_p = strtok(NULL,",");
        char *real_field_in_get_line_p = strtok(NULL, ",");


        char *string_field = malloc((strlen(string_field_in_read_line_p)+1)*sizeof(char));
        if(string_field == NULL){
            fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
            exit(EXIT_FAILURE);
        }
        strcpy(string_field,string_field_in_read_line_p);
        int integer_field = atoi(integer_field_in_read_line_p);
        float real_field = (float) strtod(real_field_in_get_line_p, NULL);


        struct record *record_p = malloc(sizeof(struct record));
        if(record_p == NULL){
            fprintf(stderr,"main: unable to allocate memory for the read record");
            exit(EXIT_FAILURE);
        }
        record_p->string_field = string_field;
        record_p->integer_field = integer_field;
        record_p->real_field = real_field;
        array[el_counter]=(void*)record_p;
//        printf("<%s,%d,%f>\n",((struct record *)array[el_counter])->string_field,((struct record *)array[el_counter])->integer_field, ((struct record *)array[el_counter])->real_field);
        el_counter++;
        free(read_line_p);
    }
    fclose(fp);
    printf("\nData loaded\n");
}




//It should be invoked with one parameter specifying the filepath of the data file
int main(int argc, char const *argv[]) {
    if(argc < 2) {
        printf("Usage: sort_array_main <file_name>\n");
        exit(EXIT_FAILURE);
    }

    // VARIABLE DECLERATION //
    clock_t t;
    void** array = (void**)malloc(CAPACITY*sizeof(void*));
    load_array(argv[1], array);

//    printf("Before: \n");
//    print_array(array);
//    b_insertion_sort(array, CAPACITY, precedes_record_int_field);
    t = clock();
//    quick_sort_Lomuto(array, 0, CAPACITY-1, precedes_record_int_field);
//    quick_sort_Lomuto(array, 0, CAPACITY-1, precedes_record_real_field);
//    quick_sort_Lomuto(array, 0, CAPACITY-1, precedes_record_string_field);

//    quick_sort_Hoares(array, 0, CAPACITY-1, precedes_record_int_field);
//    quick_sort_Hoares(array, 0, CAPACITY-1, precedes_record_real_field);
//    quick_sort_Hoares(array, 0, CAPACITY-1, precedes_record_string_field);

//    quick_sort_Hoares_r(array, 0, CAPACITY-1, precedes_record_int_field);
//    quick_sort_Hoares_r(array, 0, CAPACITY-1, precedes_record_real_field);
//    quick_sort_Hoares_r(array, 0, CAPACITY-1, precedes_record_string_field);

//    b_insertion_sort(array, CAPACITY, precedes_record_int_field);
    b_insertion_sort(array, CAPACITY, precedes_record_real_field);
//    b_insertion_sort(array, CAPACITY, precedes_record_string_field);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("quick_sort took %f seconds to execute. \n", time_taken);
    


//    printf("After: \n");
//    print_array(array);
    return (EXIT_SUCCESS);
}





