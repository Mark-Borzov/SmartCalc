#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Запрещаем ввод с клавиатуры для label_result и вставку текста:
    ui->label_result->setFocusPolicy(Qt::NoFocus);
    ui->label_result->setContextMenuPolicy(Qt::NoContextMenu);

    // Делаем step статичным:
    ui->lineEdit_step->setReadOnly(true);

    // Установка min и max значений для x, y:
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

    // Установка шага по умолчанию:
    ui->lineEdit_step->setText(QString::number(0));

    // Установка значений по умолчанию для графика:
    ui->widget_graph_of_function->xAxis->setRange(-10, 10);
    ui->widget_graph_of_function->yAxis->setRange(-10, 10);

    // Установка фиксированного размера окна, Ширина, высота:
    this->setFixedSize(1100, 460);

    // Установка значения x по умоляанию:
    ui->doubleSpinBox_value_x->setValue(1.0);
    ui->doubleSpinBox_value_x->setMinimum(-9999999.0); // Минимальное значение для значения X
    ui->doubleSpinBox_value_x->setMaximum(9999999.0); // Максимальное значение для значения X
    ui->doubleSpinBox_value_x->setDecimals(7); // Максимальное количество цифр после запятой для значения X

    // Добавляем клик по кнопке с выводом текста в label_result
    // Подключение сигналов (нажатие на кнопку) от каждой из кнопок сигналам слотам (обработчику событий) digits_numbers().
    // Это позволяет при нажатии на любую из цифровых кнопок вызывать метод digits_numbers() для обработки этого события.

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
    // Точка, плюс, минус, умножить, разделить, возведение в степень:
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
    // Открывающая и закрывающая скобки:
    connect(ui->pushButton_opening_parenthesis, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_closing_parenthesis, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    // Переменная X
    connect(ui->pushButton_x, SIGNAL(clicked()),this,SLOT(digits_numbers()));
    // Кнопка для обновления значений x и y графика функций:
    connect(ui->pushButton_Graphics, SIGNAL(clicked()), this, SLOT(update_graph_range()));
    // Кнопка для получения инфиксного выражения:
    connect(ui->pushButton_equals, SIGNAL(clicked()), this, SLOT(calculate_result()));
}

MainWindow::~MainWindow() {
    delete ui;
}

// Метод для замены функций тррригонометрии символом:
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

// Метод digits_numbers отвечает за обработку нажатий на кнопки и формировании строки в инфиксной нотации.
void MainWindow::digits_numbers() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString textToAdd = button->text();
        // Если текущий текст в label_result равен "Error", при вводе новой цифры очищаем label_result:
        if (ui->label_result->text() == "Error" || ui->label_result->text() == "inf" || ui->label_result->text() == "-inf"
           || ui->label_result->text() == "nan") {
            ui->label_result->setText("");
        }
        // Добавляем скобку в тригонометрии:
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

// Метод для отчистки поля и графика:
void MainWindow::on_pushButton_cleaning_clicked() {
    ui->label_result->setText("");
    ui->widget_graph_of_function->clearGraphs();
    ui->widget_graph_of_function->replot();
    ui->lineEdit_step->setText(QString::number(0));
}

// Реализация метода для связки значений max, min для x и y:
// Проверка на наличие x в инфиксном выражении:
void MainWindow::update_graph_range() {
    int minX = ui->spinBox_x_min->value();
    int maxX = ui->spinBox_x_max->value();
    int minY = ui->spinBox_y_min->value();
    int maxY = ui->spinBox_y_max->value();
    // Проверяем наличие символа 'x' в label_result
    if (ui->label_result->text().contains('x')) {
        display_graph_with_x(); // Вызываем метод для отображения графика с переменной x
    }
    // Обновляем переменные x и y:
    ui->widget_graph_of_function->xAxis->setRange(minX, maxX);
    ui->widget_graph_of_function->yAxis->setRange(minY, maxY);
    ui->widget_graph_of_function->replot();
}

// Метод для записи инфиксной строки в переменную и подсчет результата:
void MainWindow::calculate_result() {
    // Устанавливаем локаль для вещественных чисел:
    setlocale(LC_ALL, "C");
    // Данная строка хранит выражение инфиксной нотации для С бекенда:
    QString expression_infiks = ui->label_result->text();
    // Получаем значение x:
    double value_x = ui->doubleSpinBox_value_x->value();
    // Меняем тригонометрию для С бекенда:
    replace_trigonometry(expression_infiks);
    // Проверка строки на x:
    if (expression_infiks.contains('x')) {
        if (value_x >= 0) {
            expression_infiks.replace("x", QString::number(value_x, 'f', 7));
        } else {
            expression_infiks.replace("x", "(" + QString::number(value_x, 'f', 7) + ")");
        }
    }
    // Превращаем QString в char:
    char inficks[255] = {0};
    char polskya[512] = {0};
    for (int i = 0; i < expression_infiks.length(); i++) {
        inficks[i] = expression_infiks[i].toLatin1();
    }
    // Проверка строки и подсчет выражения:
    if (brackets(inficks) && is_valid_string(inficks)) {
        str_polish_notation(inficks, polskya);
        double res = polish_notation_expression(polskya);
        QString str_res = QString::number(res, 'f', 7);
        ui->label_result->setText(str_res);
    } else {
        ui->label_result->setText("Error");
    }
}

// Метод для отображения графика при наличии переменной x в выражении:
void MainWindow::display_graph_with_x() {
    QString expression_infiks = ui->label_result->text();
    // Меняем тригонометрию для С бекенда:
    replace_trigonometry(expression_infiks);
    // Присваиваем значения min_x и max_x в переменные:
    double minX = ui->spinBox_x_min->value();
    double maxX = ui->spinBox_x_max->value();
    int points_counter = 1000;
    // Формула для расчета шага:
    double step = (maxX - minX) / points_counter;
    // Вывод шага в lineEdit_step
    ui->lineEdit_step->setText(QString::number(step));
    //Объявляем массивы для хранения точек:
    QVector<double> x_points, y_points;
    // Генерация точек для построения графика с шагом 0.1 от minX до maxX:
    for (double x = minX; x <= maxX; x += step) {
        // Заменяем x в выражении на текущее значение:
        QString expression_with_x = expression_infiks;
        if (x >= 0) {
             expression_with_x.replace("x", QString::number(x, 'f', 7));
        } else {
             expression_with_x.replace("x", "(" + QString::number(x, 'f', 7) + ")");
        }
        // Подсчет выражения и получение значения y:
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
            // Очистка графика в случае ошибки:
            ui->widget_graph_of_function->clearGraphs();
            ui->widget_graph_of_function->replot();
            ui->lineEdit_step->setText(QString::number(0));
            return;
        }
    }
    // Отображение графика:
    ui->widget_graph_of_function->addGraph();
    ui->widget_graph_of_function->graph(0)->setData(x_points, y_points);
    ui->widget_graph_of_function->replot();
}
