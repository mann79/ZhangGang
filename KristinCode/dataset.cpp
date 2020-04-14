// Do stuff to dataset structs in here
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "../model/dataset.h"

//function that counts frequency of each type of entry in a categorical column
//and returns it as an unordered_map<string, int> type variable
unordered_map<string, int> countFrequencyCat_Col(vector<string> v)
{
    std::unordered_map<string, int> map1;

    for(int i = 0; i < v.size(); i++)
    {
        unordered_map<string, int>::iterator hasKey = map1.find(v[i]);
        if(hasKey == map1.end())
        {
            map1[v[i]] = int();
            map1[v[i]] = 1;
        }
        else
        {
            map1[v[i]]++;
        }
    }
    //cout << map1 << endl;
    return map1;
}

//function that counts frequency of each type of entry in a numerical column
//and returns it as an unordered_map<string, int> type variable
unordered_map<string, int> countFrequencyNum_Col(vector<float> v)
{
    std::unordered_map<string, int> map1;

    for(int i = 0; i < v.size(); i++)
    {
        unordered_map<string, int>::iterator hasKey = map1.find(to_string(v[i]));
        if(hasKey == map1.end())
        {
            map1[to_string(v[i])] = int();
            map1[to_string(v[i])] = 1;
        }
        else
        {
            map1[to_string(v[i])]++;
        }
    }
    //cout << map1 << endl;
    return map1;
}

//this function builds a table (of vector<vector<int>> type) that determines
//the observed values of the two columns from the csv file being compared
vector<vector<int>> buildContingencyTable(unordered_map<string, int> map1, unordered_map<string, int> map2)
{
    int r = map1.size() + 1;
    int c = map2.size() + 1;
    vector<vector<int>> v(r, vector<int> (c));
    unordered_map<string, int>:: iterator iter1;
    unordered_map<string, int>:: iterator iter2;
    iter1 = map1.begin();

    for (int i = 0; i < r-1; i++)
    {
        iter2 = map2.begin();
        for (int j = 0; j < c-1; j++)
        {
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

//this function builds a table (of vector<vector<float>> type) that determines
//the expected values of the two columns from the csv file being compared
vector<vector<float>> buildExpectedValuesTable(vector<vector<int>> v, unordered_map<string, int> map1, unordered_map<string, int> map2)
{
    int r = map1.size() + 1;
    int c = map2.size() + 1;
    vector<vector<float>> v2(r, vector<float> (c));

    for (int i = 0; i < r-1; i++)
    {
        v2[i][c-1] = static_cast<float>(v[i][c-1]);
        for (int j = 0; j < c-1; j++)
        {
            v2[r-1][j] = static_cast<float>(v[r-1][j]);
            v2[i][j] = (static_cast<float>(v[r-1][j]) * v[i][c-1])/v[r-1][c-1];
        }
    }
    v2[r-1][c-1] = static_cast<float>(v[r-1][c-1]);
    //cout << "Expected Values Table:" << endl;
    //cout << v2;
    return v2;
}

//this function builds a table (of vector<vector<float>> type) that determines
//the calculated values (using the formula [(Observed-Expected)^2/Expected]) of
//the two columns from the csv file being compared
vector<vector<float>> buildEOSquaredETable(vector<vector<int>> v1, vector<vector<float>> v2, unordered_map<string, int> map1, unordered_map<string, int> map2)
{
    int r = map1.size();
    int c = map2.size();
    vector<vector<float>> v3(r, vector<float> (c));

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            v3[i][j] = pow(v1[i][j] - v2[i][j], 2.0) / v2[i][j];
        }
    }
    //cout << "(O-E)^2 / E Values Table:" << endl;
    //cout << v3;
    return v3;
}

//this function adds up the calculated values (from buildEOSquaredETable())
//and returns the Chi-Square value of the two columns from the csv file being
//compared
float sumEOSquareEValues(vector<vector<float>> v, unordered_map<string, int> map1, unordered_map<string, int> map2)
{
    int r = map1.size();
    int c = map2.size();

    float sum = 0;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            sum = sum + v[i][j];
        }
    }
    //cout << "Chi-Square Value: "<< sum << endl;
    return sum;
}

// this function calculates and returns the degrees of freedom of the two
//columns from the csv file being compared
int degreeOfFreedom(unordered_map<string, int> map1, unordered_map<string, int> map2)
{
    int dFree = (map1.size()- 1) * (map2.size() - 1);
    //cout << "Degree of Freedom: " << dFree << endl;
    return dFree;
}

//this function is called in chisqr() to help determine p-value
static double igf(double S, double Z)
{
    if(Z < 0.0) {
        return 0.0;
    }
    double Sc = (1.0 / S);
    Sc *= std::pow(Z, S);
    Sc *= std::exp(-Z);

    double Sum = 1.0;
    double Nom = 1.0;
    double Denom = 1.0;

    for(int I = 0; I < 200; I++) {
        Nom *= Z;
        S++;
        Denom *= S;
        Sum += (Nom / Denom);
    }

    return Sum * Sc;
}

//this function determines p-value
double chisqr(int Dof, float Cv)
{
    if (Cv < 0 || Dof < 1) {
        //cout << "P-value: 0" << endl;
        return 0.0;
    }
    double K = ((double) Dof) * 0.5;
    double X = ((double) Cv) * 0.5;
    if (Dof == 2) {
        //cout << "P-value: " << exp(-1.0 * X) << endl;
        return exp(-1.0 * X);
    }

    double PValue = igf(K, X);
    if (std::isnan(PValue) || std::isinf(PValue) || PValue <= 1e-8) {
        //cout << "P-value: " << 1e-14 << endl;
        return 1e-14;
    }

    PValue /= tgamma(K);
    //cout << "P-value: " << 1.0 - PValue << endl;
    return (1.0 - PValue);
}

//this function builds a table (of vector<vector<float>> type) that determines the
//frequencies of the observed values table of the two columns from the csv file
//being compared and calculates their correlation coefficient
float correlationCoefficient(vector<vector<int>> v, unordered_map<string, int> map1, unordered_map<string, int> map2)
{
    int r = map1.size() + 1;
    int c = map2.size() + 1;
    vector<vector<float>> v2(r, vector<float> (c));

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            v2[i][j] = static_cast<float>(1.00 * v[i][j]/v[r-1][c-1]);
        }
    }
    //cout << "Frequency Values Table:" << endl;
    //cout << v2;

    //Calculate E[XY]
    float eXY = 0;
    for (int i = 0; i < r-1; i++)
    {
        for (int j = 0; j < c-1; j++)
        {
            eXY = eXY + (v2[i][j] * (i + 1) * (j + 1));
        }
    }

    //Calculate E[X]
    float eX = 0;
    for (int i = 0; i < r-1; i++)
    {
        eX = eX + (v2[i][c-1] * (i + 1));
    }

    //Calculate E[Y]
    float eY = 0;
    for (int j = 0; j < c-1; j++)
    {
        eY = eY + (v2[r-1][j] * (j + 1));
    }

    //Calculate Covariance(X,Y)
    float covXY = eXY - (eX * eY);

    //Calculate E[X]^2
    float eX2 = 0;
    for (int i = 0; i < r-1; i++)
    {
        eX2 = eX2 + (v2[i][c-1] * pow(i + 1, 2));
    }

    //Calculate E[Y]^2
    float eY2 = 0;
    for (int j = 0; j < c-1; j++)
    {
        eY2 = eY2 + (v2[r-1][j] * pow(j + 1, 2));
    }

    //Calculate V[X]
    float vX = eX2 - pow(eX, 2);

    //Calculate V[Y]
    float vY = eY2 - pow(eY, 2);

    //Calculate Correlation Coefficient
    float corCoef = covXY / sqrt(vX * vY);

    //cout << "Correlation Coefficient: " << corCoef << endl;

    return corCoef;
}

//this function encases other functions and returns the correlation coefficient
// if the p-value is greater than the threshold value.
// It returns -2 if p-value <= threshold value.
float compareColumns(unordered_map<string, int> mp1, unordered_map<string, int> mp2, double threshold)
{
    vector<vector<int>> obsValues = buildContingencyTable(mp1,mp2);
    vector<vector<float>> expValues = buildExpectedValuesTable(obsValues, mp1, mp2);
    vector<vector<float>> eOSquareValues = buildEOSquaredETable(obsValues, expValues, mp1, mp2);
    float chiSquareValue = sumEOSquareEValues(eOSquareValues, mp1, mp2);
    int degreeFreedom = degreeOfFreedom(mp1, mp2);
    float pValue = chisqr(degreeFreedom, chiSquareValue);
    if(pValue > threshold)
    {
        return correlationCoefficient(obsValues, mp1, mp2);
    }
    return 2;
}

//this function chooses two columns to compare and continues iterating until all
//columns have been compared to all other columns from the csv file
vector<Correlation>* chisquare(double threshold, Dataset a)
{
    unordered_map<string, vector<string>>:: iterator iter1c;
    unordered_map<string, vector<string>>:: iterator iter2c;
    unordered_map<string, vector<float>>:: iterator iter1n;
    unordered_map<string, vector<float>>:: iterator iter2n;

    if(a.cat_cols.size() > 1)
    {
        for (iter1c = a.cat_cols.begin(); iter1c != a.cat_cols.end(); iter1c++) //comparing category columns
        {
            for (iter2c = iter1c++; iter2c != a.cat_cols.end(); iter2c++)
            {
                if(iter1c->first != iter2c->first)
                {
                    unordered_map<string, int> mp1 = countFrequencyCat_Col(a.cat_cols[iter1c->first]);
                    unordered_map<string, int> mp2 = countFrequencyCat_Col(a.cat_cols[iter2c->first]);
                    //cout << "Category 1: '" << iter1c->first << "' compared to Category 2: '" << iter2c->first << "'" << endl;
                    float correlationCoef = compareColumns(mp1, mp2, threshold);
                    if(correlationCoef != 2)
                    {
                        Correlation a;

                        a.column_1_name = iter1c->first;
                        a.column_2_name = iter2c->first;
                        a.coefficient = correlationCoef;
                        result->push_back(a);
                        //cout << "Column_1_name: " << a.column_1_name << endl;
                        //cout << "Column_2_name: " << a.column_2_name << endl;
                        //cout << "Correlation Coefficient: " << a.coefficient << endl;
                        //cout << result->back();
                    }
                }
            }
        }
    }

    if(a.num_cols.size() > 1)
    {
        for (iter1n = a.num_cols.begin(); iter1n != a.num_cols.end(); iter1n++) //comparing numerical columns
        {
            for (iter2n = iter1n++; iter2n != a.num_cols.end(); iter2n++)
            {
                if(iter1n->first != iter2n->first)
                {
                    unordered_map<string, int> mp1 = countFrequencyNum_Col(a.num_cols[iter1n->first]);
                    unordered_map<string, int> mp2 = countFrequencyNum_Col(a.num_cols[iter2n->first]);
                    //cout << "Category 1: '" << iter1n->first << "' compared to Category 2: '" << iter2n->first << "'" << endl;
                    float correlationCoef = compareColumns(mp1, mp2);
                    if(correlationCoef != 2)
                    {
                        Correlation a;

                        a.column_1_name = iter1n->first;
                        a.column_2_name = iter2n->first;
                        a.coefficient = correlationCoef;
                        result->push_back(a);
                        //cout << "Column_1_name: " << a.column_1_name << endl;
                        //cout << "Column_2_name: " << a.column_2_name << endl;
                        //cout << "Correlation Coefficient: " << a.coefficient << endl;
                        //cout << result->back();
                    }
                }
            }
        }
    }

    if(a.cat_cols.size() > 0 && a.num_cols.size() > 0)
    {
        for (iter1c = a.cat_cols.begin(); iter1c != a.cat_cols.end(); iter1c++) //comparing category columns and numerical columns
        {
            for (iter1n = a.num_cols.begin(); iter1n != a.num_cols.end(); iter1n++)
            {
                unordered_map<string, int> mp1 = countFrequencyCat_Col(a.cat_cols[iter1c->first]);
                unordered_map<string, int> mp2 = countFrequencyNum_Col(a.num_cols[iter1n->first]);
                //cout << "Category 1: '" << iter1c->first << "' compared to Category 2: '" << iter1n->first << "'" << endl;
                float correlationCoef = compareColumns(mp1, mp2);
                if(correlationCoef != 2)
                {
                    Correlation a;

                    a.column_1_name = iter1c->first;
                    a.column_2_name = iter1n->first;
                    a.coefficient = correlationCoef;
                    result->push_back(a);
                    //cout << "Column_1_name: " << a.column_1_name << endl;
                    //cout << "Column_2_name: " << a.column_2_name << endl;
                    //cout << "Correlation Coefficient: " << a.coefficient << endl;
                    //cout << result->back();
                }
            }
        }
    }
    return result;
}