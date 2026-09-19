#pragma once

#include <vector>
#include <QLabel>
#include <QString>
#include <QTimer>
#include <QEventLoop>
#include "Elimination.h"
#include "GJacobi.h"
#include "GSeidel.h"

using namespace std;


#define NUM 4
#define PRECISION 9

class MethodVisualizer{
    private:
    QLabel* (*nums_matrix)[NUM + 1];
    QLabel** var_labels;
    QLabel* iter_label;

    const double (&a_temp)[NUM][NUM];
    const double (&b_temp)[NUM];

    double epsilon;
    int max_iterations;

    void delay(const int milliseconds);
    void updateMatrixUI(double** a, double* b);
    void updateVarsUI(const std::vector<double>& vars);
    void updateElementA(double** a, const int i, const int j);
    void updateElementB(double* b, const int i);
    void updateElementResult(const vector<double> &vars, const int i);

public:
    MethodVisualizer(QLabel* nums_matrix[NUM][NUM + 1],
                                    QLabel* var_labels[NUM],
                                    QLabel* iter_label,
                                    const double (&a_temp)[NUM][NUM],
                                    const double (&b_temp)[NUM],
                                    double epsilon,
                                    int max_iterations);
    void resetUI(double**a, vector<double> &vars, double*b);

    void updateVarsUI(const std::vector<double>& vars, const std::vector<double>& prev_vars, bool completed = false);

    void runElimination(double** a, double* b, std::vector<double>& vars);
    void runJacobi(double** a, double* b, std::vector<double>& vars);
    void runSeidel(double** a, double* b, std::vector<double>& vars);

    void setEpsilon(double ep);
    void setMaxIter(double mi);
};