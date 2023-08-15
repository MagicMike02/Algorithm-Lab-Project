#include "structure.h"
#include <string.h>
#define MAX_BUF_LEN 1024
#define INITIAL_CAPACITY 1000

void readFile(Structure* myStruct, char* filename){

  FILE* file;
  if((file=fopen(filename, "r"))==NULL) {
    printf("Errore nell'apertura del file'");
    exit(1);
  }
  int  id;  /*ID*/
  char buf[MAX_BUF_LEN];  /*field1*/
  int field2;  /*field2*/
  float field3;  /*field3*/
  int lineno = 0;  /*line number*/
  int n;
  while(!feof(file) && lineno <1000) { // && lineno<2000
    Record* record = (Record*) malloc(sizeof(Record));
    int n = fscanf(file, "%d,%1024[^,],%d,%f\n", &id,buf,&field2,&field3);
    lineno++;
    if(n != 4) {
      if(feof(file)) {
        continue;
      }
      printf("Error while reading file at line: %d\n", lineno);
      exit(1);
    }
    record->id = id;
    record->field1 = strndup(buf, MAX_BUF_LEN);
    record->field2 = field2;
    record->field3 = field3;
    structureInsert(myStruct, record);
  }
  fclose(file);
}

Structure* structureNew(){
  Structure* myStructure = (Structure*) malloc(sizeof(Structure));
  myStructure->capacity = INITIAL_CAPACITY;
  myStructure->array = (void**) malloc(sizeof(void*)*myStructure->capacity);
  myStructure->size = 0;
  return myStructure;
}

Structure* structureFree(Structure* structure){
  //ordine importante
  free(structure->array);
  free(structure);
}

void structureInsert(Structure* structure, void* obj){
  if(structure->capacity == structure->size){
    structure->capacity = structure->capacity * 2;
    structure->array = (void**) realloc(structure->array, sizeof(void*) * structure->capacity);
    //sizeof(di un puntatore a void) moltiplicato per la capacit� memorizzata nella struttura
  }
  // adesso memorizzo nell'array in posizione [size] l'oggetto che devo inserire
  // perch� sono nella posizone size (che indica la dimenzione attuale)
  structure->array[structure->size] = obj;
  structure->size++;
}

void structureDelete(Structure* structure, int index){
  //se la dimenzione che effettivamente � occupata, � meno della met� della memoria allocata
  // allora realloco l'array per una dimenzione che � la met� dell'attuale
  if(structure->capacity > structure->size*2){
    structure->capacity = structure->capacity/2;
    structure->array = (void**) realloc(structure->array, structure->capacity);
  }

  //parto dall'indice indicato,
  // e finch� non sono arrivato all'ultima elemento effettivamente memorizzato
  // sposto tutti gli elementi successivi a quello che elimino, di 1 posizione indietro
  for(int j=index; j < structure->size-1; j++){
    structure->array[j] = structure->array[j+1];
  }
  structure->size--;
}

void* structureGet(Structure* structure, int index){
  return structure->array[index];
}

int structureSize(Structure* structure){
  return structure->size;
}
