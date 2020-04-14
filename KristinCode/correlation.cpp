// Do stuff to Correlation structs in here.

#include <vector>
#include <iostream>
#include <string>

#include "../model/correlation.h"

//this function displays the results that would appear on the GUI
void displayTopTenResults(vector<Correlation>* v)
{
    for(int t = 0; t < 10; t++)
    {
        while(!v->empty())
        {
            float largest = -2;
            int index = -1;
            if(v->size() >= 1)
            {
                for(int i = 0; i < v->size(); i++)
                {
                    if(v->at(i).coefficient > largest)
                    {
                        largest = v->at(i).coefficient;
                        index = i;
                    }
                }
            }
            cout << v->at(index) << endl;
            v->erase(v->begin() + index);
        }
    }
}