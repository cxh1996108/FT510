#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
kvpair_t* split(char* str){
  
  char* s1=strchr(str,'=');
  *s1='\0';//
  s1++;  
  char* n=strchr(s1,'\n');
  if(n != NULL) *n='\0';
  kvpair_t* temp = malloc(sizeof(*temp));
  temp->key=str;
  temp->value=s1;
  return temp;  
}
kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  /*In readKVs, you will want to open the file, read the lines of text,
  split them into key/value pairs, add the resulting pairs to an array
  (hint: realloc it to make it larger each time), close the file, and
  return the kvarray_t * that has your array. 

  Remember that you will want to abstract out complex steps into
  functions (you should see at least 2 pieces to naturally pull out into
  their own functions). */
  FILE *f = fopen(fname,"r");
  if(f == NULL){
    perror("Could not open file");
    return NULL;//return EXIT_FAILURE is wrong
  }
  //initialize
  kvpair_t * t = NULL;
  kvarray_t *arr = malloc(sizeof(*arr));
  arr->a = NULL;
  arr->l = 0;
  
  
  char *line = NULL;//pointer to each line in one input file
  size_t sz=0;
  int l=0;//count the lenght of the array (arr)
  while(getline(&line,&sz,f) != -1){
    t = split(line);
    arr->a = realloc(arr->a,(l+1)*sizeof(*(arr->a)));//important
    //arr->a[l]->key = malloc(strlen(line)*sizeof(*(arr->a[l]->key)));wrong
    //arr->a[l]->value = malloc(strlen(line)*sizeof(*(arr->a[l]->value)));wrong
    //arr->a[l] = malloc(sizeof(*(arr->a[l])));wrong
    //split
    
    arr->a[l] = t;
    line = NULL;
    l++;
  }
  arr->l = l;
  free(line);
  //line=NULL;//remember
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return NULL;
  } 
  return arr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  /*Next, you will write freeKVs, which should free all the memory
    allocated by readKVs. That is, freeKVs(readKVs(filename)) should not
    leak any memory.*/
   for(int i=0;i < pairs->l;i++){
     free(pairs->a[i]->key);// can I just free(pairs[i]) or free(pairs)???
     //free(pairs->a[i]->value);//WRONG!!!!!
     free(pairs->a[i]);
   }
   free(pairs->a);
   free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  /*Third, write printKVs which should take a kvarray_t *, and print out
  "key = '%s' value = '%s'\n"
  for each key/value pair in the array, with the first %s being whatever
  the key is, and the second being whatever value (e.g., key = 'Jean Luc
  Picard' value = 'Captain'). */
  kvpair_t* t;
  for(int i=0;i < pairs->l;i++){
    t = pairs->a[i];
    printf("key = '%s' value = '%s'\n",t->key,t->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  /*Finally, write the lookupValue function, which takes a kvarray_t * and
  a char * (string). The char * that is passed in represents a key. This
  function searches the kvarray_t for a matching key, and if found,
  returns the corresponding value. If no match is found, this function
  returns NULL. */
  kvpair_t* t;
  for(int i=0;i < pairs->l;i++){
    t = pairs->a[i];
    if(strcmp(key,t->key)==0){
      return t->value;
    }
  }
  return NULL;    
}

