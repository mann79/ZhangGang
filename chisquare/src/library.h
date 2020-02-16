#ifndef CHISQUARE_LIBRARY_H
#define CHISQUARE_LIBRARY_H

#include "model/correlation.h"
#include "model/dataset.h"

// Chisquare takes in a pvalue to use as its threshold and also a dataset struct
// it returns a vector containing a Correlation struct for each pair of correlated columns
std::vector<Correlation> chisquare(double threshold, Dataset dataset);


#endif