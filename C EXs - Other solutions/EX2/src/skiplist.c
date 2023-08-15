#include <string.h>
#include <ctype.h> //needed for "tolower()" function
#include "skiplist.h"
#define MAX_BUF_LEN 1024
//case multiple definiton, u should not compile this file if u link in gcc command this file
// you have to link this file "skiplist.c" when you want to execute one of the main files, as written in makefile
/*
MAX_HEIGHT: Define the max number of pointers "next" which can be in a single node of the Skiplist
*/

// Return a random number which is the number of levels (express lines) that a node is going to have
//  calculated with a formula makes less probable to create a level
int randomLevel(){
  int level = 1;
  while ( rand() % level < 0.5 && level < MAX_HEIGHT){
	level = level + 1;
  }
  return level;
}

//Returns a new Node with all his pointers to "next" equals NULL
Node* createNode(void* item, int level){

  Node* n = (Node*)malloc(sizeof(Node));
  n->item = item;
  n->size = level;

  n->next = (Node **) malloc(sizeof(Node*) * level);

  for (int i=0; i < level; i++){
	n->next[i] = NULL;
  }
  return n;
}
// Return an EMPTY SKIPLIST (One 'sentinel' node with item=NULL and MAX_HEIGHT express lines)
SkipList* newSkipList(compareFunction cmpFun){

	SkipList* list = (SkipList*) malloc(sizeof (SkipList));

	Node* h = createNode(NULL, MAX_HEIGHT);

	for(int i=0; i< MAX_HEIGHT; i++){
	  h->next[i] = NULL; //Sett all "next" pointers to NULL
   }

  list->head = h;
	list->max_level = 0; //max_level: ACTUAL MAX Reached in the skiplist ( =0 since is an EMPTY list)
	list->compare = cmpFun;

	return list;
}

// Frees all the memory allocated for each nodes in the skiplist, including the sentinel node
void deleteSkipList(SkipList* l){

	/*
    As in LInked List, each Nodes has a "next" pointer
	   Check if next pointer is NULL,
      If NOT, save current node to deallocate, go on to the next node to check, deallocate current node
       If NULL, deallocate head of sentinel, then deallocate the list
   */

  /*SEMBRA FUNZIONARE*/
  Node* next = NULL;
  Node* node = l->head;

  while(node) {
    next = node->next[1];
    if(l->compare == compareField1 && node->item != NULL && strlen(node->item) >1) free(node->item); //chech if has to deallocate the item which can be an array of char [checks if is the sentinel item (null) ora if is 1 digit which is casted to sorts of int]
    free(node->next);
    free(node);
    node = next;
  }
  free(l);

}

// Create a new Node and insert it in the skiplist following the order of the list
void insertSkipList(SkipList* list, void* item){

  Node* corrente = createNode(item, randomLevel());

  /*
	Update max_level of the Skiplist for each insert call,
	with the ACTUAL VALUE (dim of pointers' array) that max_level has reached
  */

  if(corrente->size > list->max_level){
	list->max_level = corrente->size;
  }

  Node* prec = list->head;
  int k = (int)list->max_level; // ->max_level is unsigned int
  for(; k>0; k--){ // starting from the actual max_level
  	if(prec->next[k] == NULL || list->compare(item, prec->next[k]->item) == -1){ // (check if item is BEFORE or after the element found in the skiplist in that level)
  	  if(k < corrente->size){//check if the item pointers' array-size, if enougth high,  if true insert the node adjusting the pointers of the nodes
  		corrente->next[k] = prec->next[k]; //Current node points to the next node of the precedent one. (Points to the node which is Greater)
  		prec->next[k] = corrente; // attach the first node less than him to the inserted current node
  	  }
  	}
  	else{ // If false stay in the SAME LEVEL (k++ + k-- = k) and check next node in the line
  	  prec = prec->next[k];
  	  k++;
  	}
  }
}

// Check if the param "item" is in the skiplits. Return the "item" if found, NULL otherwise

void* searchSkipList(SkipList* list, void* item){ //Node I
  Node* x = list->head;
  int i;
  for(i = (int)list->max_level-1; i>=1; i--){ //>=0
	//printf("Cerco %s nel %d = livello\n", item, i);

  	while(x->next[i] != NULL && list->compare(x->next[i]->item, item) == -1){ // cmpFun(x->next[i]->item, I.item) < 0
  		//printf("  item_lista %s < item_search %s\n", x->next[i]->item, item);
  		x = x->next[i]; // x = list->head->next[i]
  	}
  }
  x = x->next[1];

  if(list->compare(x->item, item) == 0){ //x = list->head->next[i]->item
	   //printf("Items sono UGUALI, %s = %s\n",x->item, item);
	   return x->item;
  }
  else{
	   //printf("  Item sono DIVERSI, stampo %s \n", item); //faccio questa print nella funzione checkPhrase
	   return NULL;
  }
}


// Read the file "filename" calling the insertSkipList function for each string found
void readFile1(SkipList* skl, char* filename){
  FILE* file;
  //long lineno = 0;
  if( (file=fopen(filename, "r")) == NULL) {
  	printf("Error Opening file 1'\n");
  	exit(1);
  }
  char* new_str_p ;
  while(!feof(file)) { //read untill EOF
    //lineno++;
    char buf[MAX_BUF_LEN];  //stringa
  	fscanf(file, "%s", buf); //all the strings untill white-space

  	//printf("Inserisco: %s\n", buf);
     new_str_p= strdup(buf);
  	insertSkipList(skl, new_str_p ); // insering the string read in a Node and then in the skiplist

  }
  free(new_str_p);
  //printf("End of reading %s lineno = %ld\n",filename,lineno);
  fclose(file);
}

//read file "filename" calling the searchSkipList function for each string found
// Prints the items which ARE NOT found in the skiplist
void checkPhrase(SkipList* skl, char* filename){
  FILE* file;

  if( (file=fopen(filename, "r")) == NULL) {
  	printf("Error in Opening file 2'\n");
  	exit(1);
  }

  while(!feof(file)) { // Se a volte l'ultima parola viene stampata 2 volte, è perche il file correct me ha la 2a riga vuota
    char buf[1000];
	  fscanf(file, "%s", buf); //legge le stringhe  format:("%[^.,:]") ?

    for (int i=0; buf[i]!='\0'; i++){
      if(buf[i] == '.' /*|| buf[i] == ':'*/|| buf[i] == ',') buf[i] = '\0';
      buf[i] = (char)tolower(buf[i]);
    }
  	printf("\n Searching = '%s'   ", buf);

  	void* itemReturned = searchSkipList(skl, buf); // inserisco un nodo nella lista con item= cio che ho letto nel file
  	if (itemReturned == NULL) printf("  WRONG WORD: '%s'", buf); // stampa la parola NON trovata con la search
  }
  fclose(file);
}

// Prints the skiplist by levels
void SkipList_print(SkipList *list){
	/*
	Node *x = list->head;
	while (x && x->next[1] != list->head) {
		printf("%s[%d]->", x->next[1]->item, x->next[1]->size);
		x = x->next[1];
	}
	printf("NIL\n");
	*/
	int i;
	for (i = MAX_HEIGHT - 1; i >= 1; i--){
	  if(list->head->next[i] != NULL){
		printf("Level %d: ", i);
		for(Node *itr = list->head->next[i]; itr != NULL; itr = itr->next[i]) {
	  printf("%s", (char*)itr->item);
		}
		printf("\n");
	  }
	  else {
		printf("Level %d: (empty)\n", i);
	  }
	}
}

//checks strings
int compareField1(void* item1, void* item2) {

  // strcmp(s1, s2) restituisce un valore:
  // -) <0 se s1 è minore di s2
  // -) =0 se s1 è uguale a s2
  // -) >0 se s1 è maggiore di s2

  //return strcmp(item1, item2);
	char* s1 = (char*)item1;
	char* s2 = (char*)item2;

	if(strcmp(s1, s2)<0) return(-1);
	else if(strcmp(s1,s2)>0) return 1;
	else return(0);
}
//checks int
int compareField2(void* item1, void* item2) {

  return item1 - item2;
}
//checks decimals
int compareField3(void* item1, void* item2){

  if(item1 == item2) { return  0; }
  else if(item1 >  item2) { return  1; }
  return -1;   /* else if(item1 <  item2) { return -1; }*/

}

