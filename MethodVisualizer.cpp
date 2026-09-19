#include "MethodVisualizer.h"

MethodVisualizer::MethodVisualizer(QLabel* nums_matrix[NUM][NUM + 1],
                                    QLabel* var_labels[NUM],
                                    QLabel* iter_label,
                                    const double (&a_temp)[NUM][NUM],
                                   const double (&b_temp)[NUM])
    : nums_matrix(nums_matrix), var_labels(var_labels), iter_label(iter_label),
      a_temp(a_temp), b_temp(b_temp) {};



void MethodVisualizer::delay(const int milliseconds) {
    QEventLoop loop;
    QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);
    loop.exec();
}

void MethodVisualizer::resetUI(double**a, vector<double> &vars, double*b){
    vars.assign(NUM, 0.0);
    for (int i = 0; i < NUM; i++) {
        b[i] = MethodVisualizer::b_temp[i];

        nums_matrix[i][NUM]->setText(QString("%1").arg(b[i], 0, 'f', PRECISION));

        for (int j = 0; j < NUM; j++) {
            a[i][j] = a_temp[i][j];
            nums_matrix[i][j] -> setText(QString("%1").arg(a[i][j], 0, 'f', PRECISION));
            var_labels[j]->setStyleSheet("");
            var_labels[j]->setText(QString("x%1 = 0.0000").arg(i + 1));

        }
    }
}
void MethodVisualizer::updateElementA(double** a, const int i, const int j) {
    nums_matrix[i][j]->setText(QString("%1").arg(a[i][j], 0, 'f', PRECISION));
    
    if (i > j) {
        if (a[i][j] == 0.0) {
            nums_matrix[i][j]->setStyleSheet("color: #FF3333; font-weight: bold;"); 
        } else {
            nums_matrix[i][j]->setStyleSheet("");
        }
    } else {
        nums_matrix[i][j]->setStyleSheet("color: #2ECC71; font-weight: bold;");
    }
}

void MethodVisualizer::updateElementB(double* b, const int i) {
    nums_matrix[i][NUM]->setText(QString("%1").arg(b[i], 0, 'f', PRECISION));
}

void MethodVisualizer::updateElementResult(const std::vector<double>& vars, const int i) {
    var_labels[i]->setText(QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', PRECISION));
}

void MethodVisualizer::updateMatrixUI(double** a, double* b) {
    for (int i = 0; i < NUM; i++) {
        updateElementB(b, i);
        for (int j = 0; j < NUM; j++) {
            updateElementA(a, i, j);
        }
    }
}
void MethodVisualizer::updateVarsUI(const std::vector<double>& vars, const std::vector<double>& prev_vars, bool completed) {
    for (int i = 0; i < NUM; i++) {
        if (completed) {
            var_labels[i]->setStyleSheet("background-color: #2ECC71; color: #FFFFFF; font-weight: bold; border-radius: 4px;");
            var_labels[i]->setText(QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', PRECISION));
        } else {
            var_labels[i]->setStyleSheet("");

            QString curStr = QString::number(vars[i], 'f', PRECISION);
            QString prevStr = QString::number(prev_vars[i], 'f', PRECISION);

            QString formattedVal = "";
            bool matching = true;

            for (int k = 0; k < curStr.length(); k++) {
                if (matching && k < prevStr.length() && curStr[k] == prevStr[k]) {
                    formattedVal += QString("<span style='color: #2ECC71; font-weight: bold;'>%1</span>").arg(curStr[k]);
                } else {
                    matching = false;
                    formattedVal += curStr[k];
                }
            }

            var_labels[i]->setText(QString("x%1 = %2").arg(i + 1).arg(formattedVal));
        }
    }
}

void MethodVisualizer::runElimination(double** a, double* b, std::vector<double>& vars) {
    MethodVisualizer::resetUI(a, vars, b);

    Elimination::solve(a, vars, b,
        [this, a](int i, int j) {
            MethodVisualizer::updateElementA(a, i, j);
            MethodVisualizer::delay(100);
        },
        [this, b](int i) {
            MethodVisualizer::updateElementB(b, i);
            MethodVisualizer::delay(100);
        },
        [this, &vars](int i) {
            MethodVisualizer::updateElementResult(vars, i);
            MethodVisualizer::delay(150);
        },
        [this, a, b]() {
            MethodVisualizer::updateMatrixUI(a, b);
            MethodVisualizer::delay(200);
        }
    );
}
void MethodVisualizer::runJacobi(double** a, double* b, std::vector<double>& vars) {
    resetUI(a, vars, b);
    std::vector<double> prev_vars = vars;

    int iterations = GJacobi::solve(a, vars, b, NUM, [&](int step) {
        updateVarsUI(vars, prev_vars, false); 
        prev_vars = vars;                    
        
        if (iter_label) iter_label->setText(QString("Rounds: %1").arg(step));
        delay(250);
    });

    updateVarsUI(vars, prev_vars, true);
}
void MethodVisualizer::runSeidel(double** a, double* b, std::vector<double>& vars) {
    resetUI(a, vars, b);
    std::vector<double> prev_vars = vars;

    int iterations = GSeidel::solve(a, vars, b, NUM, [&](int step) {
        updateVarsUI(vars, prev_vars, false); 
        prev_vars = vars; 
        
        if (iter_label) iter_label->setText(QString("Rounds: %1").arg(step));
        delay(250);
    });

    updateVarsUI(vars, prev_vars, true);
}