#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  /*compute the counts of values that appear in a particular input
    file and then to put all the pieces together.*/
  //WRITE ME
  counts_t * testCounts = createCounts();
  FILE *f = fopen(filename,"r");
  if (f == NULL) {
      perror("Could not open");
      return NULL;
  }
  char *line = NULL;
  size_t sz = 0;
  char *name;
  while(getline(&line,&sz,f)!=-1){
    name = strchr(line,'\n');//important!!!!!!!!!!!!!!!!!!,review getline 
    if(name != NULL){ //important, if is necessary
      *name = '\0';
    }
    addCount(testCounts, lookupValue(kvPairs,line));//
  }
  free(line);
  line = NULL;
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return NULL;
  }
  return testCounts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc <= 1) {
    fprintf(stderr, "Error\n");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
  //count the values that appear in the file named by argv[i], using kv    as the key/value pair
  //(call this result c)
    counts_t * c ;
    c = countFile(argv[i],kv);
  //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
  //open the file named by outName (call that f)
    FILE *ff = fopen(outName,"w");
    if (ff == NULL) {
      perror("Could not open outName");
      return EXIT_FAILURE;
    }
  //print the counts from c into the FILE f
    printCounts(c, ff);
  //close f
    if (fclose(ff) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }
  //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
