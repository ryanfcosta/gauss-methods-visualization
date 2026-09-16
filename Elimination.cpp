#include "Elimination.h"

void Elimination::backSubs(double **tri_sup, vector<double> &vars, double *b, const int NUM){
    for(int i = NUM - 1 ;i >= 0; i--){
        double  sum = 0;
        for(int j = i + 1; j < NUM; j++){
            sum += tri_sup[i][j] * vars[j];
        }
        vars[i] = (b[i] - sum) / tri_sup[i][i];
    }
}


void Elimination::partialPivot(double **a,double *b, const int k, const int NUM){
    double maior  = fabs(a[k][k]);
    int maior_line = k;

    for(int i = k+1; i<NUM; i++){
        double temp = fabs(a[i][k]);

        if(temp > maior){
            maior = temp;
            maior_line = i;
        }
    }

    if(maior_line != k){
        for(int j = 0; j < NUM; j++){
            double tempA = a[maior_line][j];
            a[maior_line][j] = a[k][j];
            a[k][j] = tempA;
        }
        double tempB = b[maior_line];
        b[maior_line] = b[k];
        b[k] = tempB;
    }
}

void Elimination::upperTriangular(double **a, double *b, const int NUM){
    for(int k = 0; k < NUM - 1; k++){
        partialPivot(a, b, k, NUM);
        for(int i = k + 1; i < NUM; i++){
            if(fabs(a[i][k]) > 1e-12){
                double m = a[i][k] / a[k][k];

                for(int j = 0; j < NUM; j++)
                    a[i][j] = a[i][j] - m * a[k][j];
                
                b[i] = b[i] - m * b[k];
            }
        }
    }
}

void Elimination::solve(double **a, vector<double> &vars, double *b, const int NUM = 4){
    upperTriangular(a, b, NUM);
    backSubs(a, vars, b, NUM);
}  