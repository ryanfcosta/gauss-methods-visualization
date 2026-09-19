#include "MethodVisualizer.h"

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
#include <QLineEdit>
#include <QDoubleValidator>

#define PRECISION 7

using namespace std;

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

    QLabel *epsilonLabel = new QLabel("Epsilon (Tolerância):");
    QLineEdit *epsilonInput = new QLineEdit(&window);
    epsilonInput->setText("1e-6");

    QDoubleValidator *validator = new QDoubleValidator(0.0, 1.0, 10, epsilonInput);
    validator->setNotation(QDoubleValidator::ScientificNotation);
    epsilonInput->setValidator(validator);

    control_container->addWidget(epsilonLabel);
    control_container->addWidget(epsilonInput);

    double epsilon = epsilonInput->text().toDouble();

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
            nums_matrix[i][j]->setObjectName("matrixCell");
            matrix_layout->addWidget(nums_matrix[i][j], i, j);
        }
        nums_matrix[i][NUM] = new QLabel();
        nums_matrix[i][NUM]->setObjectName("matrixCell");
        nums_matrix[i][NUM]->setStyleSheet("border-left: 3px solid #FF5C00;");
        matrix_layout->addWidget(nums_matrix[i][NUM], i, NUM);
    }

    QLabel *num_iter_label = new QLabel("Rounds: 0");
    results_container->addWidget(num_iter_label);

    QLabel *var_labels[NUM];
    for(int i = 0; i < NUM; i++){
        var_labels[i] = new QLabel();
        var_labels[i]->setFixedSize(150, 40);
        var_labels[i]->setAlignment(Qt::AlignCenter);
        var_labels[i]->setObjectName("Result");
        results_container->addWidget(var_labels[i]);
    }


    for(int i =0; i < NUM ; i++){
        cout << vars[i] << " ";
        QString result_text = QString("x%1 = %2").arg(i + 1).arg(vars[i], 0, 'f', PRECISION);
        var_labels[i]->setText(result_text);
    } cout << endl;

    MethodVisualizer visualizer(nums_matrix, var_labels, num_iter_label, a_temp, b_temp, epsilon);
    visualizer.resetUI(a, vars, b);

    QPushButton *button_elimin = new QPushButton("Gauss Elimination");
    methods_container->addWidget(button_elimin);
    QObject::connect(button_elimin, &QPushButton::clicked, [&]() {
        visualizer.runElimination(a, b, vars);
    });

    QPushButton *button_jacobi = new QPushButton("Gauss Jacobi");
    methods_container->addWidget(button_jacobi);
    QObject::connect(button_jacobi, &QPushButton::clicked, [&]() {
        visualizer.setEpsilon(epsilonInput->text().toDouble());
        visualizer.runJacobi(a, b, vars);
    });

    QPushButton *button_seidel = new QPushButton("Gauss Seidel");
    methods_container->addWidget(button_seidel);
    QObject::connect(button_seidel, &QPushButton::clicked, [&]() {
        visualizer.setEpsilon(epsilonInput->text().toDouble());
        visualizer.runSeidel(a, b, vars);
    });
    window.show();
    int result = app.exec();

    for (int i = 0; i < NUM; i++) {
        delete[] a[i];
    }
    delete[] a;

    return result;
}
