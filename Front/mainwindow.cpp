#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Запрет Ввода с Клавиатуры и Вставку из Буфера для label_result:
    ui->label_result->setFocusPolicy(Qt::NoFocus);
    ui->label_result->setContextMenuPolicy(Qt::NoContextMenu);

    ui->lineEdit_step->setReadOnly(true);

    // Установка min и max Значений для X, Y:
    // X min:
    ui->spinBox_x_min->setMinimum(-1000000);
    ui->spinBox_x_min->setMaximum(1000000);
    ui->spinBox_x_min->setValue(-10);
    // X max:
    ui->spinBox_x_max->setMinimum(-1000000);
    ui->spinBox_x_max->setMaximum(1000000);
    ui->spinBox_x_max->setValue(10);
    // Y min:
    ui->spinBox_y_min->setMinimum(-1000000);
    ui->spinBox_y_min->setMaximum(1000000);
    ui->spinBox_y_min->setValue(-10);
    // Y max:
    ui->spinBox_y_max->setMinimum(-1000000);
    ui->spinBox_y_max->setMaximum(1000000);
    ui->spinBox_y_max->setValue(10);

    // Установка Шага по Умолчанию:
    ui->lineEdit_step->setText(QString::number(0));

    // Установка Значений по Умолчанию для Графика:
    ui->widget_graph_of_function->xAxis->setRange(-10, 10);
    ui->widget_graph_of_function->yAxis->setRange(-10, 10);

    // Установка Фиксированного Размера Окна (Ширина, Высота):
    this->setFixedSize(1100, 460);

    // Установка Значения для X по Умоляанию:
    ui->doubleSpinBox_value_x->setValue(1.0);
    // Минимальное Значение для X:
    ui->doubleSpinBox_value_x->setMinimum(-9999999.0);
    // Максимальное Значение для X:
    ui->doubleSpinBox_value_x->setMaximum(9999999.0);
    // Максимальное Количество Цифр После Запятой для Значения X:
    ui->doubleSpinBox_value_x->setDecimals(7);

    /* Реализация Клика по Кнопке с Выводом Текста в label_result.
     * Подключение Сигналов (нажатие на кнопку) от Каждой из Кнопок Сигналам Слотам (обработчику событий) digits_numbers().
    */

    // Цифры от 0 до 9:
    connect(ui->pushButton_zero, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_one, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_two, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_three, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_four, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_five, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_six, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_seven, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_eight, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_nine, SIGNAL(clicked()),this,SLOT(digits_numbers()));

    // Точка, Плюс, Минус, Умножить, Разделить, Возведение в Степень:
    connect(ui->pushButton_dot, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_plus, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_minus, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_divide, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_pow, SIGNAL(clicked()),this,SLOT(digits_numbers()));

    // Тригонометрия:
    connect(ui->pushButton_ln, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_log, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_mod, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_atan, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_acos, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_asin, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_sin, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_cos, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_tan, SIGNAL(clicked()),this,SLOT(digits_numbers()));

    // Открывающая и Закрывающая Скобки:
    connect(ui->pushButton_opening_parenthesis, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_closing_parenthesis, SIGNAL(clicked()),this,SLOT(digits_numbers()));

    // Переменная X:
    connect(ui->pushButton_x, SIGNAL(clicked()),this,SLOT(digits_numbers()));

    // Кнопка для Обновления Значений X и Y Графика Функций:
    connect(ui->pushButton_Graphics, SIGNAL(clicked()), this, SLOT(update_graph_range()));

    // Кнопка для Получения Инфиксного Выражения:
    connect(ui->pushButton_equals, SIGNAL(clicked()), this, SLOT(calculate_result()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::replace_trigonometry(QString &expression) {
    expression.replace("acos", "C");
    expression.replace("asin", "S");
    expression.replace("atan", "T");
    expression.replace("sin", "s");
    expression.replace("cos", "c");
    expression.replace("tan", "t");
    expression.replace("sqrt", "q");
    expression.replace("ln", "l");
    expression.replace("log", "L");
    expression.replace("mod", "m");
}

void MainWindow::digits_numbers() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString textToAdd = button->text();
        if (ui->label_result->text() == "Error" || ui->label_result->text() == "inf" || ui->label_result->text() == "-inf"
           || ui->label_result->text() == "nan") {
            ui->label_result->setText("");
        }

        if (button == ui->pushButton_ln) {
            textToAdd += "(";
        } else if (button == ui->pushButton_log) {
            textToAdd += "(";
        } else if (button == ui->pushButton_sqrt) {
            textToAdd += "(";
        } else if (button == ui->pushButton_atan) {
            textToAdd += "(";
        } else if (button == ui->pushButton_acos) {
            textToAdd += "(";
        } else if (button == ui->pushButton_asin) {
            textToAdd += "(";
        } else if (button == ui->pushButton_sin) {
            textToAdd += "(";
        } else if (button == ui->pushButton_cos) {
            textToAdd += "(";
        } else if (button == ui->pushButton_tan) {
            textToAdd += "(";
        }
        QString all_numbers = ui->label_result->text() + textToAdd;
        ui->label_result->setText(all_numbers);
    }
}

void MainWindow::on_pushButton_cleaning_clicked() {
    ui->label_result->setText("");
    ui->widget_graph_of_function->clearGraphs();
    ui->widget_graph_of_function->replot();
    ui->lineEdit_step->setText(QString::number(0));
}

void MainWindow::update_graph_range() {
    int minX = ui->spinBox_x_min->value();
    int maxX = ui->spinBox_x_max->value();
    int minY = ui->spinBox_y_min->value();
    int maxY = ui->spinBox_y_max->value();
    if (ui->label_result->text().contains('x')) {
        display_graph_with_x();
    }
    ui->widget_graph_of_function->xAxis->setRange(minX, maxX);
    ui->widget_graph_of_function->yAxis->setRange(minY, maxY);
    ui->widget_graph_of_function->replot();
}

void MainWindow::calculate_result() {
    setlocale(LC_ALL, "C");
    QString expression_infiks = ui->label_result->text();
    double value_x = ui->doubleSpinBox_value_x->value();
    replace_trigonometry(expression_infiks);
    if (expression_infiks.contains('x')) {
        if (value_x >= 0) {
            expression_infiks.replace("x", QString::number(value_x, 'f', 7));
        } else {
            expression_infiks.replace("x", "(" + QString::number(value_x, 'f', 7) + ")");
        }
    }
    char inficks[255] = {0};
    char polskya[512] = {0};
    for (int i = 0; i < expression_infiks.length(); i++) {
        inficks[i] = expression_infiks[i].toLatin1();
    }
    if (brackets(inficks) && is_valid_string(inficks)) {
        str_polish_notation(inficks, polskya);
        double res = polish_notation_expression(polskya);
        QString str_res = QString::number(res, 'f', 7);
        ui->label_result->setText(str_res);
    } else {
        ui->label_result->setText("Error");
    }
}

void MainWindow::display_graph_with_x() {
    QString expression_infiks = ui->label_result->text();
    replace_trigonometry(expression_infiks);
    double minX = ui->spinBox_x_min->value();
    double maxX = ui->spinBox_x_max->value();
    int points_counter = 1000;
    double step = (maxX - minX) / points_counter;
    ui->lineEdit_step->setText(QString::number(step));
    QVector<double> x_points, y_points;
    for (double x = minX; x <= maxX; x += step) {
        QString expression_with_x = expression_infiks;
        if (x >= 0) {
             expression_with_x.replace("x", QString::number(x, 'f', 7));
        } else {
             expression_with_x.replace("x", "(" + QString::number(x, 'f', 7) + ")");
        }
        char inficks[255] = {0};
        char polskya[512] = {0};
        for (int i = 0; i < expression_with_x.length(); i++) {
            inficks[i] = expression_with_x[i].toLatin1();
        }
        if (brackets(inficks) && is_valid_string(inficks)) {
            str_polish_notation(inficks, polskya);
            double res = polish_notation_expression(polskya);
            x_points.push_back(x);
            y_points.push_back(res);
        } else {
            ui->label_result->setText("Error");
            ui->widget_graph_of_function->clearGraphs();
            ui->widget_graph_of_function->replot();
            ui->lineEdit_step->setText(QString::number(0));
            return;
        }
    }
    ui->widget_graph_of_function->addGraph();
    ui->widget_graph_of_function->graph(0)->setData(x_points, y_points);
    ui->widget_graph_of_function->replot();
}
