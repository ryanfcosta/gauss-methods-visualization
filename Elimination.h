#pragma once

#include <vector>
#include <cmath>
#include <functional>

#define NUM 4

class Elimination {
private:
    static void backSubs(double **tri_sup, std::vector<double> &vars, double *b, std::function<void(int i)> onVarChanged);

    static void partialPivot(double **a, double *b, const int k, std::function<void()> onMatrixChanged);

    static void upperTriangular(double **a, double *b,
                                std::function<void(int i, int j)> onAChanged,
                                std::function<void(int i)> onBChanged,
                                std::function<void()> onMatrixChanged);

public:
    static void solve(double **a, std::vector<double> &vars, double *b,
                      std::function<void(int i, int j)> onAChanged = nullptr,
                      std::function<void(int i)> onBChanged = nullptr,
                      std::function<void(int i)> onVarChanged = nullptr,
                      std::function<void()> onMatrixChanged = nullptr);
};