#ifndef CHISQUARE_DATASET_H
#define CHISQUARE_DATASET_H

#include <string>
#include <vector>
#include <unordered_map>

/* Assumptions about input datasets:
	1. There are no missing values
	2. There are no characters in a numeric column
	3. The dataset has at least 2 rows and 2 columns
	4. The dataset for chi-square correlation has at least 2 categorical columns
*/

// Represents the parsed CSV files that main will input to the library via function calls
struct Dataset {
    int nrow; //number of rows
    int ncol; //number of cols
    std::unordered_map<std::string, std::vector<std::string>> cat_cols; //categorical cols
    std::unordered_map<std::string, std::vector<float>> num_cols; //numerical cols
};

std::unordered_map<std::string, int> countFrequencyCat_Col(std::vector<std::string> v);
std::unordered_map<std::string, int> countFrequencyNum_Col(std::vector<float> v);
std::vector<std::vector<int>> buildContingencyTable(std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2);
std::vector<std::vector<float>> buildExpectedValuesTable(std::vector<std::vector<int>> v, std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2);
std::vector<std::vector<float>> buildEOSquaredETable(std::vector<std::vector<int>> v1, std::vector<std::vector<float>> v2, std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2);
float sumEOSquareEValues(std::vector<std::vector<float>> v, std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2);
int degreeOfFreedom(std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2);
void compareColumns(std::unordered_map<std::string, int> mp1, std::unordered_map<std::string, int> mp2);
void categoryColumnCombinations(Dataset a);

#endif //CHISQUARE_DATASET_H
