#include "Elimination.h"
#include "GJacobi.h"
#include "GSeidel.h"

#include <iostream>
#include <string>
#include <sstream> 
#include <iomanip>
#include <vector>

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QPushButton>

#define NUM 4
#define PRECISION 7

using namespace std;

void resetMatrix(double**a, const double a_temp[NUM][NUM], vector<double> &vars, double*b, const double b_temp[NUM], QLabel* nums_matrix[NUM][NUM + 1]){
    vars.assign(NUM, 0.0);
    for (int i = 0; i < NUM; i++) {
        b[i] = b_temp[i];

        nums_matrix[i][NUM]->setText( QString("%1").arg(b[i], 0, 'f', PRECISION));

        for (int j = 0; j < NUM; j++) {
            a[i][j] = a_temp[i][j];
            nums_matrix[i][j] -> setText(QString("%1").arg(a[i][j], 0, 'f', PRECISION));
        }
    }
}

void updateUIMatrix(double** a, double* b, QLabel* nums_matrix[NUM][NUM + 1]){
    for (int i = 0; i < NUM; i++){ 
        nums_matrix[i][NUM]->setText( QString("%1").arg(b[i], 0, 'f', PRECISION));
        for (int j = 0; j < NUM; j++){
            nums_matrix[i][j] -> setText(QString("%1").arg(a[i][j], 0, 'f', PRECISION));
        }
    }
    
}


void exibeMatriz(double **a ,double *b){
    for(int i = 0; i < NUM ; i++){
        for(int j = 0; j < NUM; j++){
            cout << a[i][j] << " ";
        }
        cout <<" | " << b[i] <<"\n";
    }
        cout << endl;
}

int main(int argc, char* argv[]){
    QApplication app(argc, argv);   
    QFile styleFile("style.qss");

    if (styleFile.open(QFile::ReadOnly)) {
        QTextStream stream(&styleFile);
        QString qss = stream.readAll();
        app.setStyleSheet(qss);
        styleFile.close();
    } else {
        cout << "Aviso: Nao foi possivel carregar o style.qss" << endl;
    }


    QWidget window;
    window.setWindowTitle("Gauss Methods Visualization");
    window.resize(1920,1080);

    QVBoxLayout *main_layout = new QVBoxLayout(&window);

    QHBoxLayout *visualize_layout = new QHBoxLayout();
    QGridLayout *matrix_layout = new QGridLayout();
    matrix_layout->setSpacing(5);
    QVBoxLayout *results_container = new QVBoxLayout();

    QHBoxLayout *buttons_layout = new QHBoxLayout();
    QVBoxLayout *methods_container = new QVBoxLayout();
    QVBoxLayout *control_container = new QVBoxLayout();

    main_layout->addLayout(visualize_layout);
    main_layout->addLayout(buttons_layout);

    visualize_layout->addLayout(matrix_layout);
    visualize_layout->addLayout(results_container);
    visualize_layout->setAlignment(matrix_layout, Qt::AlignCenter);

    buttons_layout->addLayout(methods_container);
    buttons_layout->addLayout(control_container);

    QLabel* nums_matrix[NUM][NUM + 1];


    cout << fixed << setprecision(9);

    double a_temp[NUM][NUM] = {
        {-18, 3, 4, -5},
        {1, -6, 0, 3},
        {1, 4, -8, -1},
        {-2, 3, -4, -10 }
    };

    double b_temp[NUM] {
        0, 10, 5, -3
    };

    double **a = new double*[NUM];
    for (int i = 0; i < NUM; i++) {
        a[i] = new double[NUM];
    }
    
    double b[NUM];
    vector <double> vars(NUM, 0.0);

    for (int i = 0; i < NUM; i++) {
        for (int j = 0; j < NUM; j++) {
            nums_matrix[i][j] = new QLabel();
            matrix_layout->addWidget(nums_matrix[i][j], i, j);
        }
        nums_matrix[i][NUM] = new QLabel();
        nums_matrix[i][NUM]->setStyleSheet("border-left: 3px solid #FF5C00;");
        matrix_layout->addWidget(nums_matrix[i][NUM], i, NUM);
    }

    resetMatrix(a, a_temp, vars, b, b_temp, nums_matrix);
    QLabel * var_labels[NUM];

    QLabel * num_iter_label = new QLabel;
    num_iter_label->setText("Iterations:   ");
    results_container->addWidget(num_iter_label);

    for(int i = 0; i < NUM; i++){
        var_labels[i] = new QLabel();

        QString result_text = QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', PRECISION);
        var_labels[i] -> setText(result_text);

        var_labels[i]->setFixedSize(150, 40);
        var_labels[i]->setAlignment(Qt::AlignCenter);
        var_labels[i]->setObjectName("Result");
        results_container->addWidget(var_labels[i]);
    }
    
    resetMatrix(a, a_temp, vars, b, b_temp, nums_matrix);

    for(int i =0; i < NUM ; i++){
        cout << vars[i] << " ";
        QString result_text = QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', PRECISION);
        var_labels[i]->setText(result_text);
    } cout << endl;

    QPushButton *button_elimin = new QPushButton("Gauss Elimination");
    methods_container->addWidget(button_elimin);
    QObject::connect(button_elimin, &QPushButton::clicked, [&a,a_temp, &vars,&b, b_temp, var_labels, num_iter_label, &nums_matrix](){
        updateUIMatrix(a,b,nums_matrix);
        resetMatrix(a, a_temp, vars, b, b_temp, nums_matrix);
        Elimination::solve(a,vars,b, NUM);
        for (int i = 0; i < NUM; i++) {
            QString result_text = QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', PRECISION);
            var_labels[i]->setText(result_text);
        }
        updateUIMatrix(a,b,nums_matrix);
        num_iter_label->setText(QString("Rounds: %1").arg(NUM-1));
    });

    QPushButton *button_jacobi = new QPushButton("Gauss Jacobi");
    methods_container->addWidget(button_jacobi);
    QObject::connect(button_jacobi, &QPushButton::clicked, [&a,a_temp, &vars,&b, b_temp, var_labels, num_iter_label, &nums_matrix](){
        resetMatrix(a, a_temp, vars, b, b_temp, nums_matrix);
        int iterations = GJacobi::solve(a,vars,b, NUM);
        for (int i = 0; i < NUM; i++) {
            QString result_text = QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', PRECISION);
            var_labels[i]->setText(result_text);
        }
        num_iter_label->setText(QString("Rounds: %1").arg(iterations));
    });

    QPushButton *button_seidel = new QPushButton("Gauss Seidel");
    methods_container->addWidget(button_seidel);
    QObject::connect(button_seidel, &QPushButton::clicked, [&a,a_temp, &vars,&b, b_temp, var_labels, num_iter_label, &nums_matrix](){
        resetMatrix(a, a_temp, vars, b, b_temp, nums_matrix);
        int iterations = GSeidel::solve(a,vars,b, NUM);
        for (int i = 0; i < NUM; i++) {
            QString result_text = QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', PRECISION);
            var_labels[i]->setText(result_text);
        }
        num_iter_label->setText(QString("Rounds: %1").arg(iterations));

    });

    window.show();
    int result = app.exec();

    for (int i = 0; i < NUM; i++) {
        delete[] a[i];
    }
    delete[] a;

    return result;
}
