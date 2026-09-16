#include "GJacobi.h"

bool GJacobi::critLinhas(double** A, const int NUM){
    for(int i = 0; i < NUM; i++){
        double sum = 0, alpha = 0;
        for(int j = 0; j < NUM; j++){
            if(i != j){
                sum += fabs(A[i][j]);
            }
        }
        alpha = sum/fabs(A[i][i]);
        cout << "alpha "<< i  + 1<< " " << alpha << endl;
        if(alpha >= 1) return false;
    }
    cout << endl;
    return true;
}

bool GJacobi::critParada(vector<double> last, vector<double> current, const int NUM, const double epsilon){
    double d = 0.0 ,xMax = 0.0, dr;

    for(int i = 0; i < NUM; i++){
        if(fabs(current[i] - last[i]) > d){
            d = fabs(current[i] - last[i]);
            xMax = fabs(current[i]);
        }
    }
    if(xMax == 0.0){
        dr = 0.0;
    } else {
        dr = d / xMax;
    }

    if(d < epsilon && dr < epsilon) return true;
    return false;
}

int GJacobi::gaussJacobi(double** A, vector <double> &vars, double* b, const int NUM){
    vector<double> temp(NUM, 0.0);
    bool stop = false;

    int reps = 0;
    do{ 
        for(int i = 0; i < NUM; i++){
            double sum = 0.0;
            for(int j = 0 ; j < NUM; j++){
                if(  i!= j){
                    sum += A[i][j] * vars[j];
                }
            } 
            temp[i] = (b[i] - sum) / A[i][i];
        }

        stop = critParada(vars, temp, NUM, 1e-6);
        for (int i = 0; i < NUM; i++) vars[i] = temp[i];
        reps ++;
    } while(!stop && reps < 1000);
    cout << "Repetições: " << reps << endl;
    return reps;
}

int GJacobi::solve(double**A, vector<double> & vars, double *b, const int  NUM){
    if(critLinhas(A, NUM)){
        return gaussJacobi(A,vars,b,NUM);
    }
    else{
        cout << "Não irá convergir" << endl;
        return 0;
    }
}