#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  /*The first, createCounts should allocate memory for a counts_t
  structure, and initialize it to represent that nothing has been
  counted yet. */
  counts_t * count = malloc(sizeof(*count));
  //count->arr = malloc(sizeof(*arr));// no need to do so
  count->l = 0;
  count->u = 0;
  count->arr = NULL;
  return count;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  /*The next function, addCount, should increment the count for the
  corresponding name. Note that name will be NULL in the case of
  something that is unknown, so your code must account for this case.*/
  if(name == NULL){
    c->u++;
  }
  else{
    
    int flag = 0;//whether name is added
    
    one_count_t* temp = NULL;
  
    for(int i=0;i<c->l;i++){
      temp = c->arr[i];
      if(strcmp(temp->key,name) == 0){
        temp->c++;
        flag = 1;
      } 
    }
    temp = NULL;
    //name is not added, so add it
    if(flag == 0){
      temp = malloc(sizeof(*temp));
      temp->key = malloc(sizeof(*temp->key)+strlen(name));//hardest
      strcpy(temp->key , name);//should use strcpy
      temp->c = 1;
      c->arr = realloc(c->arr,(c->l+1)*sizeof(*c->arr));//important
      c->arr[c->l] = temp;
      c->l++;
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  /*The third function, printCounts, takes a counts_t and prints that
  information to the FILE outFile. Recall from the description of the
  entire problem, that this function should print in the format:
  
  Captain: 1
  Commander: 2
  Lt. Commander: 1
  <unknown> : 1
  
  These should appear in the order that the name is first added, with
  unknown always appearing last.
  
  ***If there are no unknown values, you should not print a line for
  unknown. That is, you should NEVER print
  
  <unknown> : 0*/
  for(int i=0;i<c->l;i++){
    fprintf(outFile,"%s: %d\n",c->arr[i]->key,c->arr[i]->c);
  }
  if(c->u != 0){
    fprintf(outFile,"<unknown> : %d\n",c->u);
  }
  //fclose(outFile);//should I add this?
}


void freeCounts(counts_t * c) {
  //WRITE ME
  /*Finally, you should write freeCounts, which should free all the memory
  associated with a counts_t.  */
  for(int i=0;i<c->l;i++){
    free(c->arr[i]->key);
    free(c->arr[i]);  
  }
  free(c->arr);
  free(c);
  //c->arr = NULL;
  //c = NULL;
}
