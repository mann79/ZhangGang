#include <iostream>
#include <library.h>

int main(int argc, char *argv[]) {
    // Check that input is appropriate, i.e. there is arguments etc.

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