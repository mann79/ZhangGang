//============================================================================
// Author      : Joel Moore
// Version     : 1.00
// Description : This library calculates the p-value
//               given the degrees of freedom and the Chi-square value.
//============================================================================

Here are a few examples with expected output:

cout << "\nTesting p-value: with Chisquare value 15 and df 2: p-value = " << chisqr(2,15) << "\n";
cout << "\nTesting p-value: with Chisquare value 20 and df 5: p-value = " << chisqr(5,20) << "\n";
cout << "\nTesting p-value: with Chisquare value 1000 and df 5: p-value = " << chisqr(5,1000) << "\n";
cout << "\nTesting p-value: with Chisquare value -1000 and df 5: p-value = " << chisqr(5,-1000) << "\n";

Output:
Testing p-value: with Chisquare value 15 and df 2: p-value = 0.000553084

Testing p-value: with Chisquare value 20 and df 5: p-value = 0.00124973

Testing p-value: with Chisquare value 1000 and df 5: p-value = 1e-014

Testing p-value: with Chisquare value -1000 and df 5: p-value = 0





Alternative: If there are any difficulties with using the library, the following functions can be copied
             and pasted into the code to achieve the same result:

static double igf(double S, double Z)
{
    if(Z < 0.0)
    {
	return 0.0;
    }
    double Sc = (1.0 / S);
    Sc *= pow(Z, S);
    Sc *= exp(-Z);
 
    double Sum = 1.0;
    double Nom = 1.0;
    double Denom = 1.0;
 
    for(int I = 0; I < 200; I++)
    {
	Nom *= Z;
	S++;
	Denom *= S;
	Sum += (Nom / Denom);
    }
 
    return Sum * Sc;
}

///finding p value functions
double chisqr(int Dof, float Cv)
{
    if(Cv < 0 || Dof < 1)
    {
        return 0.0;
    }
    double K = ((double)Dof) * 0.5;
    double X = ((double)Cv) * 0.5;
    if(Dof == 2)
    {
	return exp(-1.0 * X);
    }
 
    double PValue = igf(K, X);
    if(isnan(PValue) || isinf(PValue) || PValue <= 1e-8)
    {
        return 1e-14;
    } 

    PValue /= tgamma(K); 
	
    return (1.0 - PValue);
}