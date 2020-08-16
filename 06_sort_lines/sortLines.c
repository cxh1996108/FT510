#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    char * str[100];
    char * line = NULL;
    size_t sz;
    int i=0;
  	while (getline(&line, &sz, stdin) != -1) {
        str[i] = (char *)malloc(sizeof(char) * 100);//very important!!!!!!
  			strcpy(str[i],line);//
        //printf("%s\n",line);
  			i++;
 		}
  	free(line);
  	sortData(str,i);//i-1 is wrong
    for(int j=0;j<i;j++){
        printf("%s\n",str[j]);
        free(str[j]);
    }
  	return EXIT_SUCCESS;
	} 
  if (argc > 1) {
  	for(int i=1;i<argc;i++)
    {
    	FILE * f = fopen(argv[i], "r");
	    if (f == NULL) {
	    	perror("Could not open file");
	    	return EXIT_FAILURE;
		  }
	  	char * str[100];
  		char * line = NULL;
  		size_t sz;
  		int i=0;
  		while (getline(&line, &sz, f) != -1) {
        str[i] = (char *)malloc(sizeof(char) * 100);//very important!!!!!!
  			strcpy(str[i],line);//
        //printf("%s\n",line);
  			i++;
  		}
      //for(int j=0;j<=i-1;j++){
        //printf("%s\n",str[j]);}
    	sortData(str,i);//i-1 is wrong
      for(int j=0;j<i;j++){
        printf("%s\n",str[j]);
        free(str[j]);
      }
    	free(line);
    	if (fclose(f) != 0) {
		    perror("Failed to close the input file!");
		    return EXIT_FAILURE;
		  }
	  }	
  }
  return EXIT_SUCCESS;
}