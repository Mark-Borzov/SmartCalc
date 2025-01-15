#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QIntValidator>
#include <iostream>

extern "C" {
#include "../Back/stack.h"
#include "../Back/notation.h"
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

// Метод для Отслеживания нажатой Кнопки:
private slots:
    void digits_numbers();

// Метод для Очистки Поля:
private slots:
    void on_pushButton_cleaning_clicked();

// Метод для Связки Значений max, min для x и y:
private slots:
    void update_graph_range();

// Метод для записи Инфиксной Строки в Переменную и Подсчет Результата:
private slots:
    void calculate_result();

// Метод для Отображения Графика:
private slots:
    void display_graph_with_x();

// Метод для Замены Функций Тригонометрии Символом:
private slots:
    void replace_trigonometry(QString &expression);
};

#endif // MAINWINDOW_H
