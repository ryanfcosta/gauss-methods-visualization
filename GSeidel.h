#pragma once

#include "GJacobi.h"

class GSeidel : public GJacobi{

public:
    static int solve(double* *a, vector<double> &vars, double* b, const int NUM);

private:
    static bool critSassenfeld(double **a, const int NUM);
    static int gaussSeidel(double** a, vector<double> &vars, double* b, const int NUM);
};
