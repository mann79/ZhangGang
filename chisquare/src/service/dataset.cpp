// Do stuff to dataset structs in here
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "../model/dataset.h"

void categoryColumnCombinations(Dataset dataSet) {
    std::unordered_map<std::string, std::vector<std::string>>:: iterator iter1c;
    std::unordered_map<std::string, std::vector<std::string>>:: iterator iter2c;
    std::unordered_map<std::string, std::vector<float>>:: iterator iter1n;
    std::unordered_map<std::string, std::vector<float>>:: iterator iter2n;

    if(dataSet.cat_cols.size() > 1) {
        //comparing category columns
        for (iter1c = dataSet.cat_cols.begin(); iter1c != dataSet.cat_cols.end(); iter1c++) {
            for (iter2c = iter1c++; iter2c != dataSet.cat_cols.end(); iter2c++) {
                if(iter1c->first != iter2c->first) {
                    std::unordered_map<std::string, int> mp1 = countFrequencyCat_Col(dataSet.cat_cols[iter1c->first]);
                    std::unordered_map<std::string, int> mp2 = countFrequencyCat_Col(dataSet.cat_cols[iter2c->first]);
                    std::cout << "Category 1: '" << iter1c->first << "' compared to Category 2: '" << iter2c->first << "'" << std::endl;
                    compareColumns(mp1, mp2);
                }
            }
        }
    }

    if(dataSet.num_cols.size() > 1) {
        //comparing numerical columns
        for (iter1n = dataSet.num_cols.begin(); iter1n != dataSet.num_cols.end(); iter1n++) {
            for (iter2n = iter1n++; iter2n != dataSet.num_cols.end(); iter2n++) {
                if(iter1n->first != iter2n->first) {
                    std::unordered_map<std::string, int> mp1 = countFrequencyNum_Col(dataSet.num_cols[iter1n->first]);
                    std::unordered_map<std::string, int> mp2 = countFrequencyNum_Col(dataSet.num_cols[iter2n->first]);
                    std::cout << "Category 1: '" << iter1n->first << "' compared to Category 2: '" << iter2n->first << "'" << std::endl;
                    compareColumns(mp1, mp2);
                }
            }
        }
    }

    if(!dataSet.cat_cols.empty() && !dataSet.num_cols.empty()) {
        //comparing category columns and numerical columns
        for (iter1c = dataSet.cat_cols.begin(); iter1c != dataSet.cat_cols.end(); iter1c++) {
            for (iter1n = dataSet.num_cols.begin(); iter1n != dataSet.num_cols.end(); iter1n++) {
                std::unordered_map<std::string, int> mp1 = countFrequencyCat_Col(dataSet.cat_cols[iter1c->first]);
                std::unordered_map<std::string, int> mp2 = countFrequencyNum_Col(dataSet.num_cols[iter1n->first]);
                std::cout << "Category 1: '" << iter1c->first << "' compared to Category 2: '" << iter1n->first << "'" << std::endl;
                compareColumns(mp1, mp2);
            }
        }
    }
}

void compareColumns(std::unordered_map<std::string, int> mp1, std::unordered_map<std::string, int> mp2) {
    std::vector<std::vector<int>> obsValues = buildContingencyTable(mp1,mp2);
    std::vector<std::vector<float>> expValues = buildExpectedValuesTable(obsValues, mp1, mp2);
    std::vector<std::vector<float>> eOSquareValues = buildEOSquaredETable(obsValues, expValues, mp1, mp2);
    float chiSquareValue = sumEOSquareEValues(eOSquareValues, mp1, mp2);
    int degreeFreedom = degreeOfFreedom(mp1, mp2);
}

std::unordered_map<std::string, int> countFrequencyCat_Col(std::vector<std::string> v) {
    std::unordered_map<std::string, int> map1;

    for (const auto &i : v) {
        auto hasKey = map1.find(i);

        if(hasKey == map1.end()) {
            map1[i] = int();
            map1[i] = 1;
        } else {
            map1[i]++;
        }
    }
    //cout << map1 << endl;
    return map1;
}

std::unordered_map<std::string, int> countFrequencyNum_Col(std::vector<float> v) {
    std::unordered_map<std::string, int> map1;

    for(float i : v) {
        auto hasKey = map1.find(std::to_string(i));
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