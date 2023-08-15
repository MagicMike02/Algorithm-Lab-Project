#include "skiplist.h"

int randomLevel();

Node *createNode(void *I, int size);


Skiplist *skipList_create(int (*compare)(void *, void *)) {
    Skiplist *list = (Skiplist *) malloc(sizeof(Skiplist));
    if (list == NULL) {
        fprintf(stderr, "Error in memory allocation(list).\n");
        exit(EXIT_FAILURE);
    }

    Node *head = (Node *) malloc(sizeof(Node));
    if (head == NULL) {
        fprintf(stderr, "Error in memory allocation(head).\n");
        exit(EXIT_FAILURE);
    }

    head->next = (Node **) malloc(sizeof(Node *) * MAX_HEIGHT);

    if (head->next == NULL) {
        fprintf(stderr, "Error in memory allocation(next).\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_HEIGHT; i++) {
        head->next[i] = NULL;
    }
    head->size = MAX_HEIGHT;
    head->item = NULL;
    list->head = head;
    list->max_level = 0;
    list->compare = compare;
    return list;
}


void insertSkiplist(Skiplist *List, void *I) {
    Node *new = createNode(I, randomLevel());
    if (new->size > List->max_level) {
        List->max_level = new->size;
    }
    Node *x = List->head;
    int k = 0;
    for (k= List->max_level-1; k >= 0; k--) {
        if (x->next[k] == NULL || List->compare( I, x->next[k]->item) < 0) {
            if (k < new->size) {
                new->next[k] = x->next[k];
                x->next[k] = new;
            }
        } else {
            x = x->next[k];
            k++;
        }
    }
}

void *searchSkipList(Skiplist *list, void *item) {
    Node* x = list->head;
    int i = (int)list->max_level-1;
    for(; i>=1; i--){ //>=0
        //printf("Cerco %s nel %d = livello\n", item, i);

        while(x->next[i] != NULL && list->compare(x->next[i]->item, item) < 0){ // cmpFun(x->next[i]->item, I.item) < 0
            //printf("  item_lista %s < item_search %s\n", x->next[i]->item, item);
            x = x->next[i]; // x = list->head->next[i]
        }
    }
    x = x->next[1];

    if(x != NULL && list->compare(x->item, item) == 0){
        return x->item;
    }
    else{
        return NULL;
    }
}


Node *createNode(void *I, int size) {
    Node *node_p = (Node *) malloc(sizeof(Node));
    if (node_p == NULL) {
        fprintf(stderr, "Error in memory allocation.\n");
        exit(EXIT_FAILURE);
    } else {
        //creo il node_p
        node_p->next = (Node **) malloc(
                size * sizeof(Node *));   //alloco il nuovo vettore di puntatori di dimensione size
        node_p->size = size; //size è uguale al valore di ritorno della funzione randomLevel
        node_p->item = I;
    }
    return node_p;
}

void skiplist_free(Skiplist *list) {
    Node* current_node = list->head;

    while(current_node->next[0] != NULL){ // finche non finisco i nodi, ne disalloco uno ad uno fino alla fine
        Node* temp_node = current_node; // salvato il nodo da deallocare
        current_node = current_node->next[0]; // salvato puntatore al vettore di puntatori del nodo da deallocare
        free(temp_node);
    }
    free(list);
    printf("\nAll clean. \n");
}


int randomLevel() {
    int lvl = 1;
    //random() returns a random value in [0...1)
    while (rand() % lvl < 0.5 && lvl < MAX_HEIGHT) {
        lvl += 1;
    }
    return lvl;
}


