#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cmath>


using namespace std;
using std::vector;

struct Dataset{
    int nrow; //number of rows
    int ncol; //number of cols
    std::unordered_map<string, vector<string>> cat_cols; //categorical cols
    std::unordered_map<string, vector<float>> num_cols; //numerical cols
};

void getData(Dataset& csvFile);
ostream& operator<<(ostream& os, const unordered_map<string, vector<string>>& v);
ostream& operator<<(ostream& os, const unordered_map<string, vector<float>>& v);
ostream& operator<<(ostream& os, const unordered_map<string, int>& v);
ostream& operator<<(ostream& os, const unordered_map<float, int>& v);
ostream& operator<<(ostream& os, const vector<vector<int>>& v);
ostream& operator<<(ostream& os, const vector<vector<float>>& v);
unordered_map<string, int> countFrequencyCat_Col(vector<string> v);
unordered_map<string, int> countFrequencyNum_Col(vector<float> v);
vector<vector<int>> buildContingencyTable(unordered_map<string, int> map1, unordered_map<string, int> map2);
vector<vector<float>> buildExpectedValuesTable(vector<vector<int>> v, unordered_map<string, int> map1, unordered_map<string, int> map2);
vector<vector<float>> buildEOSquaredETable(vector<vector<int>> v1, vector<vector<float>> v2, unordered_map<string, int> map1, unordered_map<string, int> map2);
float sumEOSquareEValues(vector<vector<float>> v, unordered_map<string, int> map1, unordered_map<string, int> map2);
int degreeOfFreedom(unordered_map<string, int> map1, unordered_map<string, int> map2);
void compareColumns(unordered_map<string, int> mp1, unordered_map<string, int> mp2);
void categoryColumnCombinations(Dataset a);

int main() {
    Dataset csvFile1;
    getData(csvFile1);
    //cout << "csvFile1.ncol:" << csvFile1.ncol << endl;
    //cout << "csvFile1.nrow:" << csvFile1.nrow << endl;
    //cout << csvFile1.cat_cols << csvFile1.num_cols << endl;
    categoryColumnCombinations(csvFile1);

    return 0;
}

void getData(Dataset& csvFile){
    csvFile.ncol = 3;
    csvFile.nrow = 10;
    csvFile.cat_cols["gender"] = vector<string>();
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
    csvFile.cat_cols["pet"] = vector<string>();
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
    csvFile.num_cols["numOfPet"] = vector<float>();
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
ostream& operator<<(ostream& os, const unordered_map<string, vector<string>>& v)
{
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
ostream& operator<<(ostream& os, const unordered_map<string, vector<float>>& v)
{
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
ostream& operator<<(ostream& os, const unordered_map<string, int>& v)
{
    for (auto it : v) {
        os << it.first << " : ";
        os << it.second << endl;
    }
    return os;
}
ostream& operator<<(ostream& os, const unordered_map<float, int>& v)
{
    for (auto it : v) {
        os << it.first << " : ";
        os << it.second << endl;
    }
    return os;
}
ostream& operator<<(ostream& os, const vector<vector<int>>& v)
{
        for (int i = 0; i < v.size(); ++i)
        {
            cout << "[ ";
            for (int j = 0; j < v[i].size(); j++)
            {
                os << v[i][j] << " ";
            }
            os << "]" << endl;
        }
    return os;
}
ostream& operator<<(ostream& os, const vector<vector<float>>& v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        cout << "[ ";
        for (int j = 0; j < v[i].size(); j++)
        {
            os << v[i][j] << " ";
        }
        os << "]" << endl;
    }
    return os;
}
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
    cout << "Chi-Square Value: "<< sum << endl;
    return sum;
}
int degreeOfFreedom(unordered_map<string, int> map1, unordered_map<string, int> map2)
{
    int dFree = (map1.size()- 1) * (map2.size() - 1);
    cout << "Degree of Freedom: " << dFree << endl;
    return dFree;
}
void compareColumns(unordered_map<string, int> mp1, unordered_map<string, int> mp2)
{
    vector<vector<int>> obsValues = buildContingencyTable(mp1,mp2);
    vector<vector<float>> expValues = buildExpectedValuesTable(obsValues, mp1, mp2);
    vector<vector<float>> eOSquareValues = buildEOSquaredETable(obsValues, expValues, mp1, mp2);
    float chiSquareValue = sumEOSquareEValues(eOSquareValues, mp1, mp2);
    int degreeFreedom = degreeOfFreedom(mp1, mp2);
}
void categoryColumnCombinations(Dataset a)
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
                    cout << "Category 1: '" << iter1c->first << "' compared to Category 2: '" << iter2c->first << "'" << endl;
                    compareColumns(mp1, mp2);
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
                    cout << "Category 1: '" << iter1n->first << "' compared to Category 2: '" << iter2n->first << "'" << endl;
                    compareColumns(mp1, mp2);
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
                cout << "Category 1: '" << iter1c->first << "' compared to Category 2: '" << iter1n->first << "'" << endl;
                compareColumns(mp1, mp2);
            }
        }
    }
}




