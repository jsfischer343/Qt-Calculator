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

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Escape)
    {
        QApplication::quit();
    }
    else if(event->key()==Qt::Key_Backspace)
    {
        mainCalculator.eraseLastInput();
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_0)
    {
        mainCalculator.inputDigit(0);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_1)
    {
        mainCalculator.inputDigit(1);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_2)
    {
        mainCalculator.inputDigit(2);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_3)
    {
        mainCalculator.inputDigit(3);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_4)
    {
        mainCalculator.inputDigit(4);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_5)
    {
        mainCalculator.inputDigit(5);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_6)
    {
        mainCalculator.inputDigit(6);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_7)
    {
        mainCalculator.inputDigit(7);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_8)
    {
        mainCalculator.inputDigit(8);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_9)
    {
        mainCalculator.inputDigit(9);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_ParenLeft)
    {
        mainCalculator.inputParenthesis(1);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_ParenRight)
    {
        mainCalculator.inputParenthesis(0);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_Plus)
    {
        mainCalculator.inputOperator('+');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_Plus)
    {
        mainCalculator.inputOperator('+');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_Minus)
    {
        mainCalculator.inputOperator('-');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_Asterisk)
    {
        mainCalculator.inputOperator('*');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_Slash)
    {
        mainCalculator.inputOperator('/');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_Return)
    {
        mainCalculator.executeCalculation();
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else
    {
        //QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    //QMainWindow::keyReleaseEvent(event);
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
    mainCalculator.executeCalculation();
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}

void MainWindow::on_pushButton_backspace_clicked()
{
    mainCalculator.eraseLastInput();
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}

