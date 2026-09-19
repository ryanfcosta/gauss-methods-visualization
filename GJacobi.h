#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <functional>

#define NUM 4

class GJacobi {
public:
    static int solve(double** a, std::vector<double>& vars, double* b, const int matrix_size, double epsilon, int max_iter, std::function<void(int step)> onStep = nullptr);
    static bool critLinhas(double** a, const int matrix_size);
    static bool critParada(std::vector<double> last, std::vector<double> current, const int matrix_size, const double epsilon);

private:
    static int gaussJacobi(double** a, std::vector<double>& vars, double* b, const int matrix_size,double epsilon, int max_iter, std::function<void(int step)> onStep = nullptr);
};