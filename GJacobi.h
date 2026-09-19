#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <functional>

#define NUM 4

class GJacobi {
public:
    static int solve(double** a, std::vector<double>& vars, double* b, const int n, std::function<void(int step)> onStep = nullptr);
    static bool critLinhas(double** a, const int n);
    static bool critParada(std::vector<double> last, std::vector<double> current, const int n, const double epsilon);

private:
    static int gaussJacobi(double** a, std::vector<double>& vars, double* b, const int n, std::function<void(int step)> onStep = nullptr);
};