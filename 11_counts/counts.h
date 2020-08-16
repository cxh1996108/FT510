#ifndef __COUNTS_H__
#define __COUNTS_H__

struct _one_count_t {
  //DEFINE ME
  char* key;
  int c;//it is always a good way to use size_t !!!!!
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  //DEFINE ME
  one_count_t **arr;
  int l;//size of arr
  int u;//count unknown
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);

void addCount(counts_t * c, const char * name);

void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif

/*First, go to counts.h. Here, you will find two empty struct
declarations. You will need to fill these in. The first should reflect
the information about one count. That is, for some particular string,
how many times have we seen it so far. The second should have an array
of the first, as well as the size of that array. You should also
include a field in this struct to count unknown names. */