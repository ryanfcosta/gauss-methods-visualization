#pragma once

#include "GJacobi.h"
#include <functional>

class GSeidel : public GJacobi {
public:
    static int solve(double** a, std::vector<double>& vars, double* b, const int n, double epsilon, std::function<void(int step)> onStep = nullptr);
    static bool critSassenfeld(double** a, const int n);

private:
    static int gaussSeidel(double** a, std::vector<double>& vars, double* b, const int n,  double epsilon, std::function<void(int step)> onStep = nullptr);
};