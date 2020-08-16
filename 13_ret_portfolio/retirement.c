#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "retirement.h"
//Have no idea how to use this function
/* function reads each line from a file between the specified dates,
   rorFromLine fcn ptr indicates how ror should be calculated 
   based on type of input data */
/*ror_arr_t * readFile(FILE * f,
                     double start,
                     double end,
                     double (*rorFromLine)(char *, double *)) {
  // WRITE ME

}*/
//Split index
double* split(char* s1){
  
  char* s2=strchr(s1,',');
  *s2 = '\0';//
  s2++;  
  char* s3=strchr(s2,',');
  *s3 = '\0';
  s3++;
  char* n=strchr(s3,'\n');
  if(n != NULL) {*n='\0';}
  double* temp = malloc(3*sizeof(*temp));
  temp[0] = atof(s1);
  temp[1] = atof(s2);
  temp[2] = atof(s3);
  return temp;  
}
double* splitB(char* s1){
  
  char* s2=strchr(s1,',');
  *s2 = '\0';//
  s2++;  
  char* n=strchr(s2,'\n');
  if(n != NULL) {*n='\0';}
  double* temp = malloc(3*sizeof(*temp));
  temp[0] = atof(s1);
  temp[1] = atof(s2);
  return temp;  
}
ror_arr_t * readEquity(FILE * f,double start,double end){
  //Calculate number of months
  size_t n =(size_t) ((floor(end)-floor(start)-1)*12+(end-floor(end))*100+(floor(start)+0.12-start)*100+0.5);//necessary to add 0.5
  //Initialize ror_arr_t
  ror_arr_t* arr = malloc(sizeof(*arr));
  arr->dates = malloc((n+1)*sizeof(*arr->dates));
  arr->index = malloc((n+1)*sizeof(*arr->index));
  arr->div = malloc((n+1)*sizeof(*arr->div));
  arr->n = n;
  arr->dates[0] = start;
  arr->dates[n] = end;
  //printf("%ld\n",n);
  //Find the start date
  char *line = NULL;
  size_t sz = 0;
  double* temp = NULL;
  while(getline(&line,&sz,f)!=-1){
    temp = split(line);
    if(start == temp[0]){
      //arr->dates[0] = temp[0];
      arr->index[0] = temp[1];
      arr->div[0] = temp[2];
      free(temp);//should add this
      temp = NULL;
      break;
    }
    free(temp);//should add this
    temp = NULL;
  }
  free(line);//should add this
  free(temp);//should add this
  temp = NULL;
  line = NULL;
  //Read from start to end 
  size_t i = 1;
  while(getline(&line,&sz,f)!=-1 && i<=n){
    temp = split(line);
    arr->dates[i] = temp[0];
    arr->index[i] = temp[1];
    arr->div[i] = temp[2];
    i++;
    free(temp);//should add this
    temp = NULL;
  }
  free(line);
  line = NULL;
  return arr;
}
ror_arr_t * readBond(FILE * f,double start,double end){
  //Calculate number of months
  size_t n =(size_t) ((floor(end)-floor(start)-1)*12+(end-floor(end))*100+(floor(start)+0.12-start)*100+0.5);//necessary to add 0.5
  //Initialize ror_arr_t
  ror_arr_t* arr = malloc(sizeof(*arr));
  arr->dates = malloc((n+1)*sizeof(*arr->dates));
  arr->index = malloc((n+1)*sizeof(*arr->index));//represent Bond Price
  arr->div = malloc((n+1)*sizeof(*arr->div));
  arr->n = n;
  arr->dates[0] = start;
  arr->dates[n] = end;
  //Find the start date
  char *line = NULL;
  size_t sz = 0;
  double* temp = NULL;
  while(getline(&line,&sz,f)!=-1){
    temp = splitB(line);
    if(start == temp[0]){
      arr->index[0] = temp[1];
      free(temp);//should add this
      temp = NULL;
      break;
    }
    free(temp);//should add this
    temp = NULL;
  }
  
  free(line);
  line = NULL;
  //Read from start to end 
  size_t i = 1;
  while(getline(&line,&sz,f)!=-1 && i<=n){
    temp = splitB(line);
    arr->dates[i] = temp[0];
    arr->index[i] = temp[1];
    i++;
    free(temp);//should add this
    temp = NULL;
  }
  free(line);
  line = NULL;
  return arr;
}

ret_portfolio_t* EquityCalculate(ret_portfolio_t* t,ror_arr_t* arr){
  t->dates[0] = arr->dates[0];
  t->cum_invest[0] = 0;
  double deposit = 100.00;
  for(size_t i=1;i<=arr->n;i++){
    t->dates[i] = arr->dates[i];//i th
    /*We will assume the monthly deposit begins at 100.00 
    and increases by 2.5% each new year (in January).*/
    double d = (t->dates[i]-floor(t->dates[i]))*100;
    if((fabs(d-1) < 0.000001)  && i!=1){
      deposit = deposit * 1.025;
      //printf("%s\n","test");
    }
    double indexror = arr->index[i]/arr->index[i-1]-1;
    double divror = (arr->div[i]/12)/arr->index[i];
    t->cum_invest[i] = t->cum_invest[i-1]*(indexror + divror +1) + deposit;  
  } 
   return t;
} 

ret_portfolio_t* BondCalculate(ret_portfolio_t* t,ror_arr_t* arr){
  t->dates[0] = arr->dates[0];
  t->cum_invest[0] = 0;
  double deposit = 100.00;
  for(size_t i=1;i<=arr->n;i++){
    t->dates[i] = arr->dates[i];//i th
    /*We will assume the monthly deposit begins at 100.00 
    and increases by 2.5% each new year (in January).*/
    double d = (t->dates[i]-floor(t->dates[i]))*100;
    if((fabs(d-1) < 0.000001)  && i!=1){
      deposit = deposit * 1.025;
    }
    double indexror = (arr->index[i]/12)/100;
    t->cum_invest[i] = t->cum_invest[i-1]*(indexror + 1) + deposit;  
  } 
   return t;
} 

ret_portfolio_t* MixCalculate(ret_portfolio_t* t,ror_arr_t* equity,ror_arr_t* bond){
  t->dates[0] = equity->dates[0];
  t->cum_invest[0] = 0;
  double deposit = 100.00;
  double lifecycle = 1.0;
  for(size_t i=1;i<=equity->n;i++){
    t->dates[i] = equity->dates[i];//i th
    /*We will assume the monthly deposit begins at 100.00 
    and increases by 2.5% each new year (in January).*/
    double d = (t->dates[i]-floor(t->dates[i]))*100;
    if((fabs(d-1) < 0.000001)  && i!=1){
      deposit = deposit * 1.025;
      lifecycle = lifecycle - 0.02;
    }
    double equityror = equity->index[i]/equity->index[i-1]-1 + (equity->div[i]/12)/equity->index[i];
    double bondror = (bond->index[i]/12)/100;
    t->cum_invest[i] = t->cum_invest[i-1]*(equityror + 1)*lifecycle + t->cum_invest[i-1]*(bondror + 1)*(1-lifecycle) + deposit;  
  } 
   return t;
} 
void Freeror(ror_arr_t* arr){
  free(arr->dates);
  free(arr->index);
  free(arr->div);
  free(arr);
}
void Freeret(ret_portfolio_t* arr){
    free(arr->dates);
    free(arr->cum_invest);
    free(arr);
}

/*Finally, write the results to a file "portfolio.csv", where each line
is the date followed by the three investment strategies' cumulative
investments at that date, separated by commas. */
void WriteFile(ret_portfolio_t* t,ret_portfolio_t* s2,ret_portfolio_t* s3,FILE * outFile)
{
  for(int i=1;i<=t->n;i++){
    fprintf(outFile,"%.2f,%.2f,%.2f,%.2f\n",t->dates[i],t->cum_invest[i],s2->cum_invest[i],s3->cum_invest[i]);
  }
}

int main(int argc, char ** argv) {
  if (argc < 4) {
    fprintf(stderr, "Error\n");
    return EXIT_FAILURE;
  }
  //Read 
  double start = atof(argv[3]);
  double end = atof(argv[4]);
  //Read sp_data
  FILE *f1 = fopen(argv[1],"r");
  if (f1 == NULL) {
    perror("Could not open outName");
    return EXIT_FAILURE;
  }
  ror_arr_t * arr1 = readEquity(f1,start,end);
  ret_portfolio_t * s1 = malloc(sizeof(*s1));
  //Initialize
  s1->n = arr1->n;
  s1->dates = malloc((s1->n+1)*sizeof(*s1->dates));
  s1->cum_invest = malloc((s1->n+1)*sizeof(*s1->cum_invest));
  //Calculate Strategy 1
  s1 = EquityCalculate(s1,arr1);  
  
  //Read bond_data
  FILE *f2 = fopen(argv[2],"r");
  if (f2 == NULL) {
    perror("Could not open outName");
    return EXIT_FAILURE;
  } 
  ror_arr_t * arr2 = readBond(f2,start,end);
  ret_portfolio_t * s2 = malloc(sizeof(*s2));
  //Initialize
  s2->n = arr2->n;
  s2->dates = malloc((s2->n+1)*sizeof(*s2->dates));
  s2->cum_invest = malloc((s2->n+1)*sizeof(*s2->cum_invest));
  //Calculate Strategy 2
  s2 = BondCalculate(s2,arr2); 
  
  //Calculate Strategy 3
  ret_portfolio_t * s3 = malloc(sizeof(*s3));
  //Initialize
  s3->n = arr2->n;
  s3->dates = malloc((s3->n+1)*sizeof(*s3->dates));
  s3->cum_invest = malloc((s3->n+1)*sizeof(*s3->cum_invest));
  
  MixCalculate(s3,arr1,arr2);
  
  
  
  //Write
  FILE *f3 = fopen("portfolio.csv","w");
  if (f3 == NULL) {
    perror("Could not open outName");
    return EXIT_FAILURE;
  }
  WriteFile(s1,s2,s3,f3);
  //Close
  if (fclose(f1) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  if (fclose(f2) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  if (fclose(f3) != 0) {
    perror("Failed to close the output file!");
    return EXIT_FAILURE;
  }
  //Free
  Freeror(arr1);
  Freeror(arr2);
  Freeret(s1);
  Freeret(s2);
  Freeret(s3);
  
  return EXIT_SUCCESS;
}