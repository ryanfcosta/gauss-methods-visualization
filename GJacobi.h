#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <functional>

using namespace std; 


class GJacobi{
public:
    static int solve(double**a, vector<double> & vars, double *b, const int n, std::function<void(int step)> onStep = nullptr);
protected:
    static bool critLinhas(double** a);
    static bool critParada(vector<double> last, vector<double> current, const int n, const double epsilon);

private:
    static int gaussJacobi(double** a, vector <double> &vars, double* b, const int n);
};