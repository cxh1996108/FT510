#ifndef __KV_H__
#define __KV_H__

struct _kvpair_t {
  //DEFINE ME!
  /*To start with this problem, you are going to want to define two
  structs, in the file kv.h. The first one (struct _kvpair_t) should
  define the structure for one key/value pair. The second should define
  the structure for an array of key/value pairs (hint: you will want to
  include the lenght of the array in this structure). */
  char *key;
  char *value;
};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t {
  //DEFINE ME!
  kvpair_t **a;
  int l;
};
typedef struct _kvarray_t kvarray_t;

kvarray_t * readKVs(const char * fname);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
