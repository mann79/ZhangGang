/* the command line usage for the driver program is the following, where {p-value} is an optional value:
 *          driver inputFileName {p-value}
 *
 *  the driver exe currently needs to be in the same directory as the input file.
 *
 *  main will attempt to parse a user-specified CSV file and build a DataSet struct
 *  then a chi-square test will be ran on that struct to determine correlation between categorical/numerical data.
 */
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <model/dataset.h>

std::ostream& operator<<(std::ostream& os, const std::unordered_map<std::string, std::vector<std::string>>& v);
std::ostream& operator<<(std::ostream& os, const std::unordered_map<std::string,std::vector<float>>& v);
std::ostream& operator<<(std::ostream& os, const std::unordered_map<std::string, int>& v);
std::ostream& operator<<(std::ostream& os, const std::unordered_map<float, int>& v);
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int>>& v);
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<float>>& v);;

bool isFloat(const std::string &input);
Dataset parseCSV(std::ifstream &inputFile);

// TODO The main program should be flexible enough to read in multiple files
int main(int argc, char *argv[]) {
    const double P_VALUE = 0.5; // Default P-Value to be used in chi-square test when user does not pass in value at command line

    std::ifstream inputFile;
    Dataset testDataSet = {};

    /*
     * case 2 - Handle case that user passes in only name of CSV file
     * case 3 - Handle case that user passes in name of CSV file & P-Value
     * default - The user has passed in either too few or too many arguments at the command line
     */
    switch(argc) {
        case 2:
            // Check that argument is a file that exists and if so open the file for read only
            inputFile.open(argv[argc-1]);
            if (!inputFile) {
                // TODO possibly throw an error instead of printing and exiting
                std::cout << "Unable to open file\n";
                exit(EXIT_FAILURE); // terminate with error
            }

            testDataSet = parseCSV(inputFile); // parse the CSV file & return a DataSet struct

            //TODO REMOVE this before production ----- Simple test that the data was input correctly
            std::cout << "testDataSet.ncol:" << testDataSet.ncol << std::endl;
            std::cout << "testDataSet.nrow:" << testDataSet.nrow << std::endl;
            std::cout << testDataSet.cat_cols << testDataSet.num_cols << std::endl;

            /*
             * call entry func e.g. chisquare()
             * entry func should take AT LEAST two values:
             *      p-value which should be default 0.5 but configurable
             *      the previously built dataset struct
             * e.g. chisquare(p-value, dataset)
             * */

            break;
        case 3:
            // Check that argument is a file that exists and if so open the file for read only
            inputFile.open(argv[argc-2]);
            if (!inputFile) {
                // TODO possibly throw an error instead of printing and exiting
                std::cout << "Unable to open file\n";
                exit(EXIT_FAILURE); // terminate with error
            }

            testDataSet = parseCSV(inputFile); // parse the CSV file & return a DataSet struct

            //TODO REMOVE this before production ----- Simple test that the data was input correctly
            std::cout << "testDataSet.ncol:" << testDataSet.ncol << std::endl;
            std::cout << "testDataSet.nrow:" << testDataSet.nrow << std::endl;
            std::cout << testDataSet.cat_cols << testDataSet.num_cols << std::endl;

            /*
             * call entry func e.g. chisquare()
             * entry func should take AT LEAST two values:
             *      p-value which should be default 0.5 but configurable
             *      the previously built dataset struct
             * e.g. chisquare(p-value, dataset)
             * */

            break;
        default:
            std::cout << "You have entered an invalid number of arguments." << std::endl;
            std::cout << "Please try again from the command line with usage 'driver fileName {p-value}' " << std::endl;
            break;
    }

    exit(EXIT_SUCCESS);
}

bool isFloat(const std::string &input) {
    std::istringstream stringStream(input);
    float f;
    stringStream >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    return stringStream.eof() && !stringStream.fail(); // check the entire string was consumed and if either failbit or badabit is set
}

Dataset parseCSV(std::ifstream &inputFile) {
    Dataset testDataSet = {};

    // grab first line's column names: referencing: https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
    std::string firstLine;
    std::string colName;

    int colCount = 0;
    std::vector<std::string> colNames;

    if(inputFile.good()) { // referencing: https://www.geeksforgeeks.org/ios-good-function-in-c-with-examples/
        getline(inputFile, firstLine);
        /* A stringstream associates a string object with a stream allowing you to read from the string as if it were a
         * stream (like cin).
         */
        std::stringstream firstLineStream(firstLine);

        // extract each column name from the first line's stream
        while(getline(firstLineStream, colName, ',')) {
            // to see if the column name was read correctly:
            std::cout << " " << colName << std::endl;
            colCount++; // keep track of how many columns there were

            // ------ would need to put data in vectors and struct here: ------
            colNames.push_back(colName);
        }
    }
    testDataSet.ncol = colCount;

    // Read the row data
    std::string line;
    std::string element;
    int rowCount = 0;

    // Handle the first row and create the maps properly to be filled with the remaining data
    getline(inputFile, line);
    rowCount++;
    std::stringstream ls(line);
    for (int i = 0; i < testDataSet.ncol; i++) {
        getline(ls, element, ',');
        if (isFloat(element)) {
            testDataSet.num_cols[colNames[i]].push_back(std::stof(element));
        } else {
            testDataSet.cat_cols[colNames[i]].push_back(element);
        }
    }

    // Handle the rest of the data line by line
    while(getline(inputFile, line)) {
        rowCount++; // keep track of how many rows there were

        std::stringstream lineStream(line);

        /* extract each element in the row: since we can assume clean data */
        for(int i = 0; i < testDataSet.ncol; i++) {
            getline(lineStream, element, ',');

            std::cout << " " << element; // to see if the column name was read correctly:

            // ------ would have to check if element is categorical or numerical here:
            // ------ based off that, would have to put data in vectors and struct here: ------
            if (isFloat(element)) {
                testDataSet.num_cols[colNames[i]].push_back(std::stof(element));
            } else {
                testDataSet.cat_cols[colNames[i]].push_back(element);
            }

        }
        std::cout << std::endl;
    }

    testDataSet.nrow = rowCount;

    return testDataSet;
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