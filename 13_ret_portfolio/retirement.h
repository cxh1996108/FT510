#ifndef __RETIREMENT_H__
#define __RETIREMENT_H__

#include <stdlib.h>

struct ror_arr_tag {
  // WRITE ME
  double * dates;
  double * index;
  double * div;
  size_t n;//number of months
};
typedef struct ror_arr_tag ror_arr_t;

// struct to hold array of dates and cumulative investments
// (hint: can be used for any investment strategy)
struct ret_portfolio_tag {
  double * dates;//an array of dates
  double * cum_invest;//an array of the cumulative investments
  size_t n;//number of months
};
typedef struct ret_portfolio_tag ret_portfolio_t;

#endif

