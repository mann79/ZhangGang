#ifndef CHISQUARE_DATASET_H
#define CHISQUARE_DATASET_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

/* Assumptions about input datasets:
	1. There are no missing values
	2. There are no characters in a numeric column
	3. The dataset has at least 2 rows and 2 columns
	4. The dataset for chi-square correlation has at least 2 categorical columns
*/

// Represents the parsed CSV files that main will input to the library via function calls
struct Dataset{
    int nrow; //number of rows
    int ncol; //number of cols
    std::unordered_map<std::string, std::vector<std::string>> cat_cols; //categorical cols
    std::unordered_map<std::string, std::vector<float>> num_cols; //numerical cols
};

//function that counts frequency of each type of entry in a categorical column
//and returns it as an unordered_map<string, int> type variable
unordered_map<string, int> countFrequencyCat_Col(vector<string> v);

//function that counts frequency of each type of entry in a numerical column
//and returns it as an unordered_map<string, int> type variable
unordered_map<string, int> countFrequencyNum_Col(vector<float> v);

//this function builds a table (of vector<vector<int>> type) that determines
//the observed values of the two columns from the csv file being compared
vector<vector<int>> buildContingencyTable(unordered_map<string, int> map1, unordered_map<string, int> map2);

//this function builds a table (of vector<vector<float>> type) that determines
//the expected values of the two columns from the csv file being compared
vector<vector<float>> buildExpectedValuesTable(vector<vector<int>> v, unordered_map<string, int> map1, unordered_map<string, int> map2);

//this function builds a table (of vector<vector<float>> type) that determines
//the calculated values (using the formula [(Observed-Expected)^2/Expected]) of
//the two columns from the csv file being compared
vector<vector<float>> buildEOSquaredETable(vector<vector<int>> v1, vector<vector<float>> v2, unordered_map<string, int> map1, unordered_map<string, int> map2);

//this function adds up the calculated values (from buildEOSquaredETable())
//and returns the Chi-Square value of the two columns from the csv file being
//compared
float sumEOSquareEValues(vector<vector<float>> v, unordered_map<string, int> map1, unordered_map<string, int> map2);

// this function calculates and returns the degrees of freedom of the two
//columns from the csv file being compared
int degreeOfFreedom(unordered_map<string, int> map1, unordered_map<string, int> map2);

//this function is called in chisqr() to help determine p-value
static double igf(double S, double Z);

//this function determines p-value
double chisqr(int Dof, float Cv);

//this function builds a table (of vector<vector<float>> type) that determines the
//frequencies of the observed values table of the two columns from the csv file
//being compared and calculates their correlation coefficient
float correlationCoefficient(vector<vector<int>> v, unordered_map<string, int> map1, unordered_map<string, int> map2);

//this function encases other functions and returns the correlation coefficient
// if the p-value is greater than the threshold value.
// It returns -2 if p-value <= threshold value.
float compareColumns(unordered_map<string, int> mp1, unordered_map<string, int> mp2, double threshold);

//this function chooses two columns to compare and continues iterating until all
//columns have been compared to all other columns from the csv file
vector<Correlation>* chisquare(double threshold, Dataset a);

#endif //CHISQUARE_DATASET_H
