#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <model/dataset.h>

void getData(Dataset& csvFile);
std::ostream& operator<<(std::ostream& os, const std::unordered_map<std::string, std::vector<std::string>>& v);
std::ostream& operator<<(std::ostream& os, const std::unordered_map<std::string,std::vector<float>>& v);
std::ostream& operator<<(std::ostream& os, const std::unordered_map<std::string, int>& v);
std::ostream& operator<<(std::ostream& os, const std::unordered_map<float, int>& v);
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int>>& v);
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<float>>& v);
std::unordered_map<std::string, int> countFrequencyCat_Col(std::vector<std::string> v);
std::unordered_map<std::string, int> countFrequencyNum_Col(std::vector<float> v);
std::vector<std::vector<int>> buildContingencyTable(std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2);
std::vector<std::vector<float>> buildExpectedValuesTable(std::vector<std::vector<int>> v, std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2);
std::vector<std::vector<float>> buildEOSquaredETable(std::vector<std::vector<int>> v1, std::vector<std::vector<float>> v2, std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2);
float sumEOSquareEValues(std::vector<std::vector<float>> v, std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2);
int degreeOfFreedom(std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2);
void compareColumns(std::unordered_map<std::string, int> mp1, std::unordered_map<std::string, int> mp2);
void categoryColumnCombinations(Dataset a);

int main(int argc, char *argv[]) {
    std::ifstream inFile;
    inFile.open("GenderPetTest.csv"); // could replace parameter with cin,
    // but currently using PetTest for testing purposes.
    if (!inFile) {
        std::cout << "Unable to open file\n";
        exit(1); // terminate with error
    }

    // create a Dataset struct for this csv file:
    Dataset genderPetData = {};

    // grab first line's column names:
    // referencing: https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
    std::string firstLine;
    std::string colName;

    int colCount = 0;

    if(inFile.good()) { // referencing: https://www.geeksforgeeks.org/ios-good-function-in-c-with-examples/
        getline(inFile, firstLine);
        std::stringstream firstLineStream(firstLine); // A stringstream associates a string object with a stream
        // allowing you to read from the string as if it were a
        // stream (like cin).
        // extract each column name from the first line's stream
        while(getline(firstLineStream, colName, ',')) {
            // to see if the column name was read correctly:
            std::cout << " " << colName << std::endl;

            colCount++; // keep track of how many columns there were

            // ------ would need to put data in vectors and struct here: ------

        }
        // update Dataset struct ncol here:
        genderPetData.ncol = colCount;
    }

    // read the rest of the data line by line:
    std::string line;
    std::string element;
    int rowCount = 0;
    while( getline(inFile, line) ) {
        rowCount++; // keep track of how many rows there were

        std::stringstream lineStream(line);
        // extract each element in the row:
        // since we can assume clean data
        for( int i = 0; i < genderPetData.ncol; i++ ) {
            getline(lineStream, element, ',');

            // to see if the column name was read correctly:
            std::cout << " " << element;

            // ------ would have to check if element is categorical or numerical here: ------
            // ------ based off that, would have to put data in vectors and struct here: ------
        }
        std::cout << std::endl;
    }
    // update Dataset struct nrow here:
    genderPetData.nrow = rowCount;

    //Dataset csvFile1;
    //getData(csvFile1);
    //cout << "csvFile1.ncol:" << csvFile1.ncol << endl;
    //cout << "csvFile1.nrow:" << csvFile1.nrow << endl;
    //cout << csvFile1.cat_cols << csvFile1.num_cols << endl;
    //categoryColumnCombinations(csvFile1);

    return 0;
}

void getData(Dataset& csvFile){
    csvFile.ncol = 3;
    csvFile.nrow = 10;
    csvFile.cat_cols["gender"] = std::vector<std::string>();
    csvFile.cat_cols["gender"].push_back("male");
    csvFile.cat_cols["gender"].push_back("male");
    csvFile.cat_cols["gender"].push_back("male");
    csvFile.cat_cols["gender"].push_back("male");
    csvFile.cat_cols["gender"].push_back("male");
    csvFile.cat_cols["gender"].push_back("male");
    csvFile.cat_cols["gender"].push_back("female");
    csvFile.cat_cols["gender"].push_back("female");
    csvFile.cat_cols["gender"].push_back("female");
    csvFile.cat_cols["gender"].push_back("female");
    csvFile.cat_cols["pet"] = std::vector<std::string>();
    csvFile.cat_cols["pet"].push_back("dog");
    csvFile.cat_cols["pet"].push_back("dog");
    csvFile.cat_cols["pet"].push_back("dog");
    csvFile.cat_cols["pet"].push_back("cat");
    csvFile.cat_cols["pet"].push_back("cat");
    csvFile.cat_cols["pet"].push_back("cat");
    csvFile.cat_cols["pet"].push_back("dog");
    csvFile.cat_cols["pet"].push_back("dog");
    csvFile.cat_cols["pet"].push_back("dog");
    csvFile.cat_cols["pet"].push_back("cat");
    csvFile.num_cols["numOfPet"] = std::vector<float>();
    csvFile.num_cols["numOfPet"].push_back(1);
    csvFile.num_cols["numOfPet"].push_back(2);
    csvFile.num_cols["numOfPet"].push_back(3);
    csvFile.num_cols["numOfPet"].push_back(1);
    csvFile.num_cols["numOfPet"].push_back(2);
    csvFile.num_cols["numOfPet"].push_back(3);
    csvFile.num_cols["numOfPet"].push_back(1);
    csvFile.num_cols["numOfPet"].push_back(2);
    csvFile.num_cols["numOfPet"].push_back(3);
    csvFile.num_cols["numOfPet"].push_back(1);
}

std::ostream& operator<<(std::ostream& os, const std::unordered_map<std::string, std::vector<std::string>>& v) {
    for (auto it : v) {
        os << it.first << " : ";
        os << "[";

        for (int i = 0; i < it.second.size(); ++i) {
            os << it.second[i];
            if (i != it.second.size() - 1) {
                os << ", ";
            }
        }

        os << "]\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::unordered_map<std::string, std::vector<float>>& v) {
    for (auto it : v) {
        os << it.first << " : ";
        os << "[";

        for (int i = 0; i < it.second.size(); ++i) {
            os << it.second[i];
            if (i != it.second.size() - 1)
                os << ", ";
        }

        os << "]\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::unordered_map<std::string, int>& v) {
    for (const auto& it : v) {
        os << it.first << " : ";
        os << it.second << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::unordered_map<float, int>& v) {
    for (auto it : v) {
        os << it.first << " : ";
        os << it.second << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int>>& v) {
    for (const auto & i : v) {
        std::cout << "[ ";
        for (int j : i) {
            os << j << " ";
        }
        os << "]" << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<float>>& v) {
    for (const auto & i : v) {
        std::cout << "[ ";

        for (float j : i) {
            os << j << " ";
        }

        os << "]" << std::endl;
    }
    return os;
}

std::unordered_map<std::string, int> countFrequencyCat_Col(std::vector<std::string> v) {
    std::unordered_map<std::string, int> map1;

    for(int i = 0; i < v.size(); i++) {
        std::unordered_map<std::string, int>::iterator hasKey = map1.find(v[i]);
        if(hasKey == map1.end()) {
            map1[v[i]] = int();
            map1[v[i]] = 1;
        } else {
            map1[v[i]]++;
        }
    }
    //cout << map1 << endl;
    return map1;
}

std::unordered_map<std::string, int> countFrequencyNum_Col(std::vector<float> v) {
    std::unordered_map<std::string, int> map1;

    for(float i : v) {
        std::unordered_map<std::string, int>::iterator hasKey = map1.find(std::to_string(i));
        if(hasKey == map1.end()) {
            map1[std::to_string(i)] = int();
            map1[std::to_string(i)] = 1;
        } else {
            map1[std::to_string(i)]++;
        }
    }
    //cout << map1 << endl;
    return map1;
}

std::vector<std::vector<int>> buildContingencyTable(std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2) {
    int r = map1.size() + 1;
    int c = map2.size() + 1;
    std::vector<std::vector<int>> v(r, std::vector<int> (c));
    std::unordered_map<std::string, int>:: iterator iter1;
    std::unordered_map<std::string, int>:: iterator iter2;
    iter1 = map1.begin();

    for (int i = 0; i < r-1; i++) {
        iter2 = map2.begin();
        for (int j = 0; j < c-1; j++) {
            v[i][j] = iter1->second + iter2->second;
            v[i][c-1] = v[i][c-1] + v[i][j];
            v[r-1][j] = v[r-1][j] + v[i][j];
            v[r-1][c-1] = v[r-1][c-1] + v[i][j];
            iter2++;
        }
        iter1++;
    }
    //cout << "Observed Values Table:" << endl;
    //cout << v;
    return v;
}

std::vector<std::vector<float>> buildExpectedValuesTable(std::vector<std::vector<int>> v, std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2) {
    int r = map1.size() + 1;
    int c = map2.size() + 1;
    std::vector<std::vector<float>> v2(r, std::vector<float> (c));

    for (int i = 0; i < r-1; i++) {
        v2[i][c-1] = static_cast<float>(v[i][c-1]);
        for (int j = 0; j < c-1; j++) {
            v2[r-1][j] = static_cast<float>(v[r-1][j]);
            v2[i][j] = (static_cast<float>(v[r-1][j]) * v[i][c-1])/v[r-1][c-1];
        }
    }
    v2[r-1][c-1] = static_cast<float>(v[r-1][c-1]);
    //cout << "Expected Values Table:" << endl;
    //cout << v2;
    return v2;
}

std::vector<std::vector<float>> buildEOSquaredETable(std::vector<std::vector<int>> v1, std::vector<std::vector<float>> v2, std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2) {
    int r = map1.size();
    int c = map2.size();
    std::vector<std::vector<float>> v3(r, std::vector<float> (c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            v3[i][j] = pow(v1[i][j] - v2[i][j], 2.0) / v2[i][j];
        }
    }
    //cout << "(O-E)^2 / E Values Table:" << endl;
    //cout << v3;
    return v3;
}

float sumEOSquareEValues(std::vector<std::vector<float>> v, std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2) {
    int r = map1.size();
    int c = map2.size();

    float sum = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            sum = sum + v[i][j];
        }
    }

    std::cout << "Chi-Square Value: "<< sum << std::endl;
    return sum;
}

int degreeOfFreedom(std::unordered_map<std::string, int> map1, std::unordered_map<std::string, int> map2) {
    int dFree = (map1.size()- 1) * (map2.size() - 1);
    std::cout << "Degree of Freedom: " << dFree << std::endl;
    return dFree;
}

void compareColumns(std::unordered_map<std::string, int> mp1, std::unordered_map<std::string, int> mp2) {
    std::vector<std::vector<int>> obsValues = buildContingencyTable(mp1,mp2);
    std::vector<std::vector<float>> expValues = buildExpectedValuesTable(obsValues, mp1, mp2);
    std::vector<std::vector<float>> eOSquareValues = buildEOSquaredETable(obsValues, expValues, mp1, mp2);
    float chiSquareValue = sumEOSquareEValues(eOSquareValues, mp1, mp2);
    int degreeFreedom = degreeOfFreedom(mp1, mp2);
}

void categoryColumnCombinations(Dataset a) {
    std::unordered_map<std::string, std::vector<std::string>>:: iterator iter1c;
    std::unordered_map<std::string, std::vector<std::string>>:: iterator iter2c;
    std::unordered_map<std::string, std::vector<float>>:: iterator iter1n;
    std::unordered_map<std::string, std::vector<float>>:: iterator iter2n;

    if(a.cat_cols.size() > 1) {
        //comparing category columns
        for (iter1c = a.cat_cols.begin(); iter1c != a.cat_cols.end(); iter1c++) {
            for (iter2c = iter1c++; iter2c != a.cat_cols.end(); iter2c++) {
                if(iter1c->first != iter2c->first) {
                    std::unordered_map<std::string, int> mp1 = countFrequencyCat_Col(a.cat_cols[iter1c->first]);
                    std::unordered_map<std::string, int> mp2 = countFrequencyCat_Col(a.cat_cols[iter2c->first]);
                    std::cout << "Category 1: '" << iter1c->first << "' compared to Category 2: '" << iter2c->first << "'" << std::endl;
                    compareColumns(mp1, mp2);
                }
            }
        }
    }

    if(a.num_cols.size() > 1) {
        //comparing numerical columns
        for (iter1n = a.num_cols.begin(); iter1n != a.num_cols.end(); iter1n++) {
            for (iter2n = iter1n++; iter2n != a.num_cols.end(); iter2n++) {
                if(iter1n->first != iter2n->first) {
                    std::unordered_map<std::string, int> mp1 = countFrequencyNum_Col(a.num_cols[iter1n->first]);
                    std::unordered_map<std::string, int> mp2 = countFrequencyNum_Col(a.num_cols[iter2n->first]);
                    std::cout << "Category 1: '" << iter1n->first << "' compared to Category 2: '" << iter2n->first << "'" << std::endl;
                    compareColumns(mp1, mp2);
                }
            }
        }
    }

    if(!a.cat_cols.empty() && !a.num_cols.empty()) {
        //comparing category columns and numerical columns
        for (iter1c = a.cat_cols.begin(); iter1c != a.cat_cols.end(); iter1c++) {
            for (iter1n = a.num_cols.begin(); iter1n != a.num_cols.end(); iter1n++) {
                std::unordered_map<std::string, int> mp1 = countFrequencyCat_Col(a.cat_cols[iter1c->first]);
                std::unordered_map<std::string, int> mp2 = countFrequencyNum_Col(a.num_cols[iter1n->first]);
                std::cout << "Category 1: '" << iter1c->first << "' compared to Category 2: '" << iter1n->first << "'" << std::endl;
                compareColumns(mp1, mp2);
            }
        }
    }
}








/*
 * #include <iostream>
#include <library.h>

int main(int argc, char *argv[]) {
    const double P_VALUE = 0.5; // Default P-Value to be used in chi-square test when user does not pass in value

    std::ifstream input;

    if (argc == 2) { // Try to parse CSV file and run chi-square test with default p-value

    } else if (argc == 3) { // Try to parse CSV file and run chi-square test with passed in p-value

    } else {
        // Default behavior is to return non-zero value to indicate abnormal program termination
        return 1;
    }

    // Check that argument is a file that exists and if so open the file for read only
    // Start to parse the CSV file and store values in two vectors:
    // std::unordered_map<std::string, std::vector<std::string>> categorical_columns;
    // std::unordered_map<std::string, std::vector<float>> numerical_columns;
    // Create a Dataset struct with the two previously calculated maps

    // call entry func e.g. chisquare()
    // entry func should take AT LEAST two values:
    // p-value which should be default 0.5 but configurable
    // the previously built dataset struct
    // e.g. chisquare(p-value, dataset)


    // The main loop should be flexible enough to read in multiple files, or read up to N-1 files where N = argc

    exit(EXIT_SUCCESS);
}
 */