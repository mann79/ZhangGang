#include "library.h"
#include "model/dataset.h"
#include "model/correlation.h"

#include <iostream>
#include <vector>
// Time Complexity:
// 		Count frequency & build contingency table: O(r) - r is number of rows
//		Calculate the difference between expected and actual: O(mn)
//		Overall: O(r + mn) = O(r)

// Chisquare takes in a pvalue to use as its threshold and also a dataset struct
// it returns a vector containing a Correlation struct for each pair of correlated columns
std::vector<Correlation> chisquare(double threshold, Dataset dataset) {
    std::vector<Correlation> result;

    /*
    	int chisquareValue = 0

    	for (all entries in Dataset) {
			expectedValue = ((rowTotal * columnTotal) / overallTotal)
			workingValue = (((expectedValue - actualValue) ** 2) / expectedValue)
			chisquareValue += workingValue
    	}

    	degreeFreedom = ((rows-1) * (columns - 1))

    	pValue = givenLibFunction(chisquareValue, degreeFreedom)

    	if (pValue > threshold) {
			add column pair to result
    	}
    */

    return result;
}