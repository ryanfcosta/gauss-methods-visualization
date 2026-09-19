#include "GJacobi.h"

using namespace std;

bool GJacobi::critLinhas(double** a, const int n) {
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += fabs(a[i][j]);
            }
        }
        double alpha = sum / fabs(a[i][i]);
        cout << "alpha " << i + 1 << ": " << alpha << endl;
        if (alpha >= 1.0) return false;
    }
    cout << endl;
    return true;
}

bool GJacobi::critParada(vector<double> last, vector<double> current, const int n, const double epsilon) {
    double d = 0.0, xMax = 0.0;

    for (int i = 0; i < n; i++) {
        double diff = fabs(current[i] - last[i]);
        if (diff > d) {
            d = diff;
        }
        if (fabs(current[i]) > xMax) {
            xMax = fabs(current[i]);
        }
    }

    double dr = (xMax == 0.0) ? 0.0 : (d / xMax);
    return (d < epsilon && dr < epsilon);
}

int GJacobi::gaussJacobi(double** a, vector<double>& vars, double* b, const int n, std::function<void(int step)> onStep) {
    vector<double> temp(n, 0.0);
    bool stop = false;
    int reps = 0;

    do {
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum += a[i][j] * vars[j];
                }
            }
            temp[i] = (b[i] - sum) / a[i][i];
        }

        stop = critParada(vars, temp, n, 1e-6);
        for (int i = 0; i < n; i++) vars[i] = temp[i];

        reps++;
        if (onStep) {
            onStep(reps);
        }
    } while (!stop && reps < 1000);

    cout << "Repetições Jacobi: " << reps << endl;
    return reps;
}

int GJacobi::solve(double** a, vector<double>& vars, double* b, const int n, std::function<void(int step)> onStep) {
    if (critLinhas(a, n)) {
        return gaussJacobi(a, vars, b, n, onStep);
    } else {
        cout << "Não irá convergir" << endl;
        return 0;
    }
}