#pragma once

#include "GJacobi.h"
#include <functional>

class GSeidel : public GJacobi{

public:
    static int solve(double* *a, vector<double> &vars, double* b,const int n, std::function<void(int step)> onStep = nullptr);

private:
    static bool critSassenfeld(double **a, const int n);
    static int gaussSeidel(double** a, vector<double> &vars, double* b);
};
