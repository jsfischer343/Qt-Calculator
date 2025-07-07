#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_num0_clicked()
{
    mainCalculator.inputDigit(0);
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num1_clicked()
{
    mainCalculator.inputDigit(1);
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num2_clicked()
{
    mainCalculator.inputDigit(2);
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num3_clicked()
{
    mainCalculator.inputDigit(3);
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num4_clicked()
{
    mainCalculator.inputDigit(4);
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num5_clicked()
{
    mainCalculator.inputDigit(5);
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num6_clicked()
{
    mainCalculator.inputDigit(6);
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num7_clicked()
{
    mainCalculator.inputDigit(7);
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num8_clicked()
{
    mainCalculator.inputDigit(8);
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num9_clicked()
{
    mainCalculator.inputDigit(9);
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}

void MainWindow::on_pushButton_operatorPlus_clicked()
{
    mainCalculator.inputOperator('+');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_operatorSub_clicked()
{
    mainCalculator.inputOperator('-');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_operatorMul_clicked()
{
    mainCalculator.inputOperator('*');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_operatorDiv_clicked()
{
    mainCalculator.inputOperator('/');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}

void MainWindow::on_pushButton_parenOpen_clicked()
{
    mainCalculator.inputParenthesis(1);
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_parenClosed_clicked()
{
    mainCalculator.inputParenthesis(0);
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}


void MainWindow::on_pushButton_enter_clicked()
{
    mainCalculator.pushAndFlushDigitBuffer();
    mainCalculator.executeCalculation();
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}

