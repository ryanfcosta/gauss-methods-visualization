#include "MethodVisualizer.h"


void MethodVisualizer::resetUI(double**a, const double a_temp[NUM][NUM], vector<double> &vars, double*b, const double b_temp[NUM], QLabel* nums_matrix[NUM][NUM + 1]){
    vars.assign(NUM, 0.0);
    for (int i = 0; i < NUM; i++) {
        b[i] = b_temp[i];

        nums_matrix[i][NUM]->setText(QString("%1").arg(b[i], 0, 'f', PRECISION));

        for (int j = 0; j < NUM; j++) {
            a[i][j] = a_temp[i][j];
            nums_matrix[i][j] -> setText(QString("%1").arg(a[i][j], 0, 'f', PRECISION));
        }
    }
}

void MethodVisualizer::updateMatrixUI(double** a, double* b, QLabel* nums_matrix[NUM][NUM + 1]){
    for (int i = 0; i < NUM; i++){ 
        nums_matrix[i][NUM]->setText(QString("%1").arg(b[i], 0, 'f', PRECISION));
        for (int j = 0; j < NUM; j++){
            nums_matrix[i][j] -> setText(QString("%1").arg(a[i][j], 0, 'f', PRECISION));
        }
    }
    
}
