#pragma once

#include <vector>
#include <QLabel>
#include <QString>

using namespace std;

#define NUM 4
#define PRECISION 7

class MethodVisualizer{
public:
    static void resetUI(double**a, const double a_temp[NUM][NUM], vector<double> &vars, double*b, const double b_temp[NUM], QLabel* nums_matrix[NUM][NUM + 1]);
    static void updateMatrixUI(double** a, double* b, QLabel* nums_matrix[NUM][NUM + 1]);

};