//============================================================================
// Name        : ChisquarePValueFinder.h
// Author      : Joel Moore
// Version     : 1.00
// Description : This is a header file for a library that calculates the p-value
//               given the degrees of freedom and the Chi-square value.
//============================================================================
#ifndef CHISQUARE_CHISQUAREPVALUEFINDER_H
#define CHISQUARE_CHISQUAREPVALUEFINDER_H

/*
* This helper function helps to calculate the p-value.
*/
static double igf(double S, double Z);

/*
* This function takes as input the degrees of freedom and the Chi-square value.
* It returns the p-value as a double.
*/
double chisqr(int Dof, float Cv);

#endif //CHISQUARE_CHISQUAREPVALUEFINDER_H

