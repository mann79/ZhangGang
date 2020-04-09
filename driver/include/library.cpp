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

    // note: must perform chi-square on all possible pairs
    
    /*
    	int chisquareValue = 0
     
        // add the rows and columns of the dataset_file
     
        // calaculate the "expected value" for each entry of the dataset_file by
        //    multipling each row total by each column total and dividing by the overall total
    	for (all entries in Dataset) {
			expectedValue = ((rowTotal * columnTotal) / overallTotal)
            // subtract expected by actual (the original number in the dataset_file), square it,
            //    then divide by expected
			workingValue = (((expectedValue - actualValue) ** 2) / expectedValue)
            // add up the new values to get the chi-square value
			chisquareValue += workingValue
    	}

        // calculate the degrees of freedom
        //    multiply (rows − 1) by (columns − 1)
    	degreeFreedom = ((rows-1) * (columns - 1))

        // call a library function to calculate the p-value
        //    (must give the chi-square value and degrees of freedom)
        pValue = givenLibFunction(chisquareValue, degreeFreedom)

        // see if p_value is less than p_threshold
        //    if so, then ignore the pair
    	if (pValue > threshold) {
			add column pair to result
    	}
    */

    // return a struct containing the names of the 2 columns and the correlation coefficient
    return result;
}
