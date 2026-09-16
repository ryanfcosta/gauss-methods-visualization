#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Elimination{

public: 
    static void solve(double **triSup, vector<double> &vars, double *b, const int NUM);

private:
    static void partialPivot(double **a,double *b, int k, const int NUM);
    static void upperTriangular(double **a, double *b, const int NUM);
    static void backSubs(double **triSup, vector<double> &vars, double *b, const int NUM);
    
};