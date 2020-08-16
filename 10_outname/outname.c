#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  /*For this problem, you will be writing the function which computes the
  output file name. That is, given an input file name (such as
  "input.txt"), it should allocate memory for and fill in a string with
  the output file name ("input.txt.counts").

  You should write the function

  char * computeOutputFileName(const char * inputName)

  in the outname.c file. You can make and test with the main function
  found in outname_test.c. As always, be sure your program valgrinds
  cleanly. */
  
  char * outFileName = malloc((strlen(inputName) + 8) * sizeof(*outFileName));
  strcpy(outFileName, inputName);
  strcat(outFileName, ".counts");
  return outFileName;
}



