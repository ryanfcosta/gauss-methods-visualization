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

#define NUM 3

using namespace std;

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
        {-0.0000,1.0000,0.8415},
        {3,-1.0000,0.0000},
        {14.7781, 0.0000,-1.0000}
    };

    double b_temp[NUM] {
        0.5403, 3, 15.3890
    };

    double **a = new double*[NUM];
    double b[NUM];
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
    vector <double> vars(NUM, 0.0);
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
        cout << x << " ";
    }cout << endl;

    vars.assign(NUM, 0.0);
    GSeidel::solve(a_new,vars,b,NUM);

    for(auto const x : vars){
        cout << x << " ";
    }cout << endl;

    for (int i = 0; i < NUM; i++) delete[] a_new[i];
    delete[] a_new;

    janela.show();
    return app.exec();
}
