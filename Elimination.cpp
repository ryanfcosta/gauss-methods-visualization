#include "Elimination.h"

void Elimination::backSubs(double **tri_sup, std::vector<double> &vars, double *b, std::function<void(int i)> onVarChanged){
    for(int i = NUM - 1 ;i >= 0; i--){
        double  sum = 0;
        for(int j = i + 1; j < NUM; j++){
            sum += tri_sup[i][j] * vars[j];
        }
        vars[i] = (b[i] - sum) / tri_sup[i][i];
        if (onVarChanged) onVarChanged(i);
    }
}


void Elimination::partialPivot(double **a,double *b, const int k, std::function<void()> onMatrixChanged){
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
        if (onMatrixChanged) onMatrixChanged();
    }
}

void Elimination::upperTriangular(double **a, double *b,
                                    std::function<void(int i, int j)> onAChanged,
                                    std::function<void(int i)> onBChanged,
                                    std::function<void()> onMatrixChanged){
    for(int k = 0; k < NUM - 1; k++){
        partialPivot(a, b, k, onMatrixChanged);
        for(int i = k + 1; i < NUM; i++){
            if(fabs(a[i][k]) > 1e-12){
                double m = a[i][k] / a[k][k];

                for(int j = 0; j < NUM; j++){
                    a[i][j] = a[i][j] - m * a[k][j];
                    if (onAChanged) onAChanged(i, j);
                }

                b[i] = b[i] - m * b[k];
                if (onBChanged) onBChanged(i);
            }
        }
    }
}

void Elimination::solve(double **a, std::vector<double> &vars, double *b,
                        std::function<void(int i, int j)> onAChanged,
                        std::function<void(int i)> onBChanged,
                        std::function<void(int i)> onVarChanged,
                        std::function<void()> onMatrixChanged){
    upperTriangular(a, b, onAChanged, onBChanged, onMatrixChanged);
    backSubs(a, vars, b, onVarChanged);
}  