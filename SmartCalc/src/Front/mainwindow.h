#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QIntValidator>
#include <iostream>

extern "C" {
#include "../stack.h"
#include "../notation.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

// Объявляем метод для отслеживания нажатой кнопки:
private slots:
    void digits_numbers();

// Метод для отчистки поля
private slots:
    void on_pushButton_cleaning_clicked();

// Метод для связки значений max, min для x и y:
private slots:
    void update_graph_range();

// Метод для записи инфиксной строки в переменную и подсчет результата:
private slots:
    void calculate_result();

// Метод для отображения графика:
private slots:
    void display_graph_with_x();

// Метод для замены функций тррригонометрии символом:
private slots:
    void replace_trigonometry(QString &expression);
};

#endif // MAINWINDOW_H
