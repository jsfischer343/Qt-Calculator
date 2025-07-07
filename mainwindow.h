#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_num0_clicked();

    void on_pushButton_num1_clicked();

    void on_pushButton_num2_clicked();

    void on_pushButton_num3_clicked();

    void on_pushButton_num4_clicked();

    void on_pushButton_num5_clicked();

    void on_pushButton_num6_clicked();

    void on_pushButton_num7_clicked();

    void on_pushButton_num8_clicked();

    void on_pushButton_num9_clicked();

    void on_pushButton_operatorPlus_clicked();

    void on_pushButton_operatorSub_clicked();

    void on_pushButton_operatorMul_clicked();

    void on_pushButton_operatorDiv_clicked();

    void on_pushButton_parenOpen_clicked();

    void on_pushButton_parenClosed_clicked();

    void on_pushButton_enter_clicked();

    void on_pushButton_backspace_clicked();

private:
    Ui::MainWindow *ui;
    Calculator mainCalculator = Calculator();
};
#endif // MAINWINDOW_H
