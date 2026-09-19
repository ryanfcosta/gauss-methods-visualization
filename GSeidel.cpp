#include "GSeidel.h"

using namespace std;

bool GSeidel::critSassenfeld(double** a, const int n) {
    vector<double> beta(n, 0.0);
    double max_beta = 0.0;

    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (j < i) {
                    sum += fabs(a[i][j]) * beta[j];
                } else {
                    sum += fabs(a[i][j]);
                }
            }
        }
        beta[i] = sum / fabs(a[i][i]);
        if (beta[i] > max_beta) {
            max_beta = beta[i];
        }
        cout << "beta " << i + 1 << ": " << beta[i] << endl;
    }
    return max_beta < 1.0;
}

int GSeidel::gaussSeidel(double** a, vector<double>& vars, double* b, const int n, std::function<void(int step)> onStep) {
    bool stop = false;
    int reps = 0;

    do {
        vector<double> last = vars;

        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += a[i][j] * vars[j];
                }
            }
            vars[i] = (b[i] - sum) / a[i][i];
        }

        reps++;
        if (onStep) {
            onStep(reps);
        }

        stop = GJacobi::critParada(last, vars, n, 1e-6);
    } while (!stop && reps < 1000);

    cout << "Repetições Seidel: " << reps << endl;
    return reps;
}

int GSeidel::solve(double** a, vector<double>& vars, double* b, const int n, std::function<void(int step)> onStep) {
    if (GJacobi::critLinhas(a, n) || GSeidel::critSassenfeld(a, n)) {
        return gaussSeidel(a, vars, b, n, onStep);
    } else {
        cout << "Não irá convergir" << endl;
        return 0;
    }
}