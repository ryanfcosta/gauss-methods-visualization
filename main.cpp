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

using namespace std;

void resetMatrix(double**a, const double a_temp[NUM][NUM], vector <double> vars, double*b, const double b_temp[NUM], QGridLayout *matrix_layout, QLabel* nums_matrix[NUM][NUM + 1]){
    vars.assign(NUM, 0.0);
    for (int i = 0; i < NUM; i++) {
        b[i] = b_temp[i];

        nums_matrix[i][NUM] = new QLabel();

        QString result_b = QString("%1").arg(b[i], 0, 'f', 4);
        nums_matrix[i][NUM] -> setText(result_b);
        nums_matrix[i][NUM]->setStyleSheet("border-left: 3px solid #FF5C00;");
        matrix_layout->addWidget(nums_matrix[i][NUM], i, NUM);
        a[i] = new double[NUM];
        for (int j = 0; j < NUM; j++) {
            a[i][j] = a_temp[i][j];

            nums_matrix[i][j] = new QLabel();

            QString result_text = QString("%1").arg(a[i][j], 0, 'f', 4);
            nums_matrix[i][j] -> setText(result_text);
                
            matrix_layout->addWidget(nums_matrix[i][j], i, j);
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


    QWidget janela;
    janela.setWindowTitle("Gauss Methods Visualization");
    janela.resize(1920,1080);

    QVBoxLayout *main_layout = new QVBoxLayout(&janela);

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
    double b[NUM];
    vector <double> vars(NUM, 0.0);

    resetMatrix(a, a_temp, vars, b, b_temp, matrix_layout, nums_matrix);
    QLabel * var_labels[NUM];

    for(int i = 0; i < NUM; i++){
        var_labels[i] = new QLabel();

        QString result_text = QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', 4);
        var_labels[i] -> setText(result_text);

        var_labels[i]->setFixedSize(150, 40);
        var_labels[i]->setAlignment(Qt::AlignCenter);

        var_labels[i]->setObjectName("resultado");
        results_container->addWidget(var_labels[i]);
    }



    Elimination::solve(a,vars,b,NUM);
    exibeMatriz(a,b);

    for(int i =0; i < NUM; i++){
        QString result_text = QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', 4);
        var_labels[i]->setText(result_text);
    }

    resetMatrix(a, a_temp, vars, b, b_temp, matrix_layout, nums_matrix);
    
    for(auto const x : vars){
        cout << x << " ";
    } cout << endl;
    for (int i = 0; i < NUM; i++) delete[] a[i];
    delete[] a;


    double ** a_new = new double*[NUM];
    for (int i = 0; i < NUM; i++) {
        b[i] = b_temp[i];
        a_new[i] = new double[NUM];
        for (int j = 0; j < NUM; j++) {
            a_new[i][j] = a_temp[i][j];
        }
    }
    
    vars.assign(NUM, 0.0);
    GJacobi::solve(a_new,vars,b,NUM);

    for(auto const x : vars){
        cout << x << " "; vars.assign(NUM, 0.0);
    }cout << endl;

    vars.assign(NUM, 0.0);
    GSeidel::solve(a_new,vars,b,NUM);

    for(auto const x : vars){
        cout << x << " ";
    }cout << endl;

    for (int i = 0; i < NUM; i++) delete[] a_new[i];
    delete[] a_new;
        
    QPushButton *button_elimin = new QPushButton("Eliminação Gaussiana");
    methods_container->addWidget(button_elimin);

    QObject::connect(button_elimin, &QPushButton::clicked, [&a,a_temp, &vars,&b, b_temp, var_labels, matrix_layout, &nums_matrix](){
        resetMatrix(a, a_temp, vars, b, b_temp, matrix_layout, nums_matrix);
        Elimination::solve(a,vars,b, NUM);
        for (int i = 0; i < NUM; i++) {
            QString result_text = QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', 4);
            var_labels[i]->setText(result_text);
        }
    });

    QPushButton *button_jacobi = new QPushButton("Gauss Jacobi");
    methods_container->addWidget(button_jacobi);
    QObject::connect(button_jacobi, &QPushButton::clicked, [&a,a_temp, &vars,&b, b_temp, var_labels, matrix_layout, &nums_matrix](){
        resetMatrix(a, a_temp, vars, b, b_temp, matrix_layout, nums_matrix);
        GJacobi::solve(a,vars,b, NUM);
        for (int i = 0; i < NUM; i++) {
            QString result_text = QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', 4);
            var_labels[i]->setText(result_text);
        }
    });


    QPushButton *button_seidel = new QPushButton("Gauss Seidel");
    methods_container->addWidget(button_seidel);
    QObject::connect(button_seidel, &QPushButton::clicked, [&a,a_temp, &vars,&b, b_temp, var_labels, matrix_layout, &nums_matrix](){
        resetMatrix(a, a_temp, vars, b, b_temp, matrix_layout, nums_matrix);
        GSeidel::solve(a,vars,b, NUM);
        for (int i = 0; i < NUM; i++) {
            QString result_text = QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', 4);
            var_labels[i]->setText(result_text);
        }
    });

    buttons_layout->addItem(methods_container);
    janela.show();
    return app.exec();
}
