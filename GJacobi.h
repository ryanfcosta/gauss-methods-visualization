#pragma once

#include <cmath>
#include <iostream>
#include <vector>
using namespace std; 

class GJacobi{
public:
    static int solve(double**a, vector<double> & vars, double *b, const int  NUM);
protected:
    static bool critLinhas(double** a, const int NUM);
    static bool critParada(vector<double> last, vector<double> current, const int NUM, const double epsilon);

private:
    static int gaussJacobi(double** a, vector <double> &vars, double* b, const int NUM);
};