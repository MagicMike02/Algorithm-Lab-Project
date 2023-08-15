#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "skiplist.h"

#define BUFF_SIZE   512


//It returns a number less than zero iff the first string is less than
//the second one , 0 iff both are equal and  greater than zero otherwise.
static int precedes_record_string_field(void *s1_p, void *s2_p) {
    if (s1_p == NULL) {
        fprintf(stderr, "precedes_string: the first parameter is a null pointer");
        exit(EXIT_FAILURE);
    }
    if (s2_p == NULL) {
        fprintf(stderr, "precedes_string: the second parameter is a null pointer");
        exit(EXIT_FAILURE);
    }

    return strcmp((char *) s1_p, (char *) s2_p);
}

int precedes_record_int_field(void *i1_p, void *i2_p) {
    int *i1 = (int *) i1_p;
    int *i2 = (int *) i2_p;

    if (*i1 > *i2)
        return (1);
    else if (i1 < i2)
        return (-1);
    else
        return (0);
}


void load_skipList(const char *file_name, Skiplist* list) {
    FILE *fp;

    printf("\nLoading data from file...\n");
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        fprintf(stderr, "main: unable to open the file");
        exit(EXIT_FAILURE);
    }

    while(!feof(fp)){
        char buf[BUFF_SIZE];
        fscanf(fp, "%s", buf); //legge le stringhe
        char *new_str_p = (char *) malloc(sizeof(char) * BUFF_SIZE);
        strcpy(new_str_p, buf);
        insertSkiplist(list, (void *) new_str_p);
    }
    fclose(fp);
    printf("\nData loaded\n");
}

void find_errors(const char* file_name, Skiplist* list){
    FILE* file;
    if( (file=fopen(file_name, "r")) == NULL) {
        printf("Error in Opening file 2'\n");
        exit(1);
    }
    while(!feof(file)) { // Se a volte l'ultima parola viene stampata 2 volte, è perche il file correct me ha la 2a riga vuota
        char buf[BUFF_SIZE];

        fscanf(file, "%s", buf); //legge le stringhe  format:("%[^.,:]") ?

        for (int i=0; buf[i]!='\0'; i++){
            if(buf[i] == '.' /*|| buf[i] == ':'*/|| buf[i] == ',') buf[i] = '\0';
            buf[i] = (char)tolower(buf[i]);
        }
        printf("\n Searching = '%s'   ", buf);

        void* itemReturned = searchSkipList( list,  (void*) buf); // inserisco un nodo nella lista con item= cio che ho letto nel file

        if (itemReturned == NULL) printf("  WRONG WORD: '%s'", buf); // stampa la parola NON trovata con la search
    }
    fclose(file);
}


int main(int argc, char const *argv[]) {
    if (argc < 3) {
        printf("Usage: main <file_name>\n");
        exit(EXIT_FAILURE);
    }
    Skiplist *list = skipList_create(precedes_record_string_field);

    clock_t t;
    double time_taken;
    t = clock() ; // prima della funzione
    load_skipList(argv[1], list);
    t = clock() - t; // dopo la funzione
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Tempo per inserire i dati nella skip list = %f \n", time_taken);

    t = clock(); // prima della funzione
    find_errors(argv[2], list);
    t = clock() - t; // dopo la funzione
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\n Tempo per eseguire la ricerca nella skip list = %f \n", time_taken);

    skiplist_free(list);
}

