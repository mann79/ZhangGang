#ifndef CHISQUARE_CORRELATION_H
#define CHISQUARE_CORRELATION_H

#include <vector>
#include <iostream>
#include <string>

// Represents the calculated correlation to be returned from the library
// Each pair of correlated columns with p-value > threshold; i.e. a vector of Correlation structs will be returned from the library.
// e.g. std::vector<Correlation> result = new vector<Correlation>();
// 		result->push_back(correlation1);
//		result->push_back(correlation2);
//		return result;
struct Correlation {
    std::string column_one;
    std::string column_two;
    float coefficient;
};

//the vector of Correlation structs that return results
vector<Correlation>* result = new vector<Correlation>();

//this function displays the results that would appear on the GUI
void displayTopTenResults(vector<Correlation>* v);

#endif //CHISQUARE_CORRELATION_H
