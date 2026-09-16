#include "GSeidel.h"

bool GSeidel::critSassenfeld(double **a, const int NUM){
    vector <double> beta(NUM, 0.0); 
    double max_beta = 0.0;

    for(int i = 0; i< NUM; i++){
        double sum = 0.0;
        for(int j = 0; j < NUM; j++){
            if(i != j){
                if(j < i){
                    sum += fabs(a[i][j]) * beta[j]; 
                }
                else{
                    sum += fabs(a[i][j]);                    
                }
            }
        }
        beta[i] = sum / fabs(a[i][i]);
        if(beta[i] > max_beta){
            max_beta = beta[i];
        }
        cout << "beta "<< i  + 1<< " " << beta[i] << endl;

    }
    if(max_beta >= 1) return false;
    return true;
}

int GSeidel::gaussSeidel(double** a, vector <double> &vars, double* b, const int NUM){
    bool stop = false;
    int reps = 0;

    do{
        vector<double> last(NUM, 0.0);
        for(int k = 0; k < NUM; k++){
            last[k] = vars[k];
        }

        for(int i = 0; i < NUM; i++){
            double sum = 0.0;
            for(int j = 0; j < NUM; j++){
                if(i!=j){
                    sum += a[i][j] * vars[j];
                }
            }
            vars[i] = (b[i] - sum) / a[i][i];
        }
        stop = GJacobi::critParada(last,vars,NUM, 1e-9);
        reps++;
    }while(!stop && reps < 1000);
    cout << "Repetições " << reps << endl;
    return reps;
}

int GSeidel::solve(double* *a, vector<double> &vars, double* b, const int NUM){
    if(GJacobi::critLinhas(a, NUM) || GSeidel::critSassenfeld(a, NUM)){
        return gaussSeidel(a,vars,b, NUM); 
    }else{
        cout << "Não irá convergir" << endl;
        return 0;
    }
}