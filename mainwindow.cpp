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
        mainCalculator.inputDigitOrDecimal(0);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_1)
    {
        mainCalculator.inputDigitOrDecimal(1);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_2)
    {
        mainCalculator.inputDigitOrDecimal(2);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_3)
    {
        mainCalculator.inputDigitOrDecimal(3);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_4)
    {
        mainCalculator.inputDigitOrDecimal(4);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_5)
    {
        mainCalculator.inputDigitOrDecimal(5);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_6)
    {
        mainCalculator.inputDigitOrDecimal(6);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_7)
    {
        mainCalculator.inputDigitOrDecimal(7);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_8)
    {
        mainCalculator.inputDigitOrDecimal(8);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else if(event->key()==Qt::Key_9)
    {
        mainCalculator.inputDigitOrDecimal(9);
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
    mainCalculator.inputDigitOrDecimal('0');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num1_clicked()
{
    mainCalculator.inputDigitOrDecimal('1');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num2_clicked()
{
    mainCalculator.inputDigitOrDecimal('2');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num3_clicked()
{
    mainCalculator.inputDigitOrDecimal('3');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num4_clicked()
{
    mainCalculator.inputDigitOrDecimal('4');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num5_clicked()
{
    mainCalculator.inputDigitOrDecimal('5');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num6_clicked()
{
    mainCalculator.inputDigitOrDecimal('6');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num7_clicked()
{
    mainCalculator.inputDigitOrDecimal('7');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num8_clicked()
{
    mainCalculator.inputDigitOrDecimal('8');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}
void MainWindow::on_pushButton_num9_clicked()
{
    mainCalculator.inputDigitOrDecimal('9');
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
void MainWindow::on_pushButton_decimalPoint_clicked()
{
    mainCalculator.inputDigitOrDecimal('.');
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
    if(mainCalculator.executeCalculation())
    {
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
    }
    else
    {
        popUp_InvalidSyntax();
    }
}

void MainWindow::on_pushButton_backspace_clicked()
{
    mainCalculator.eraseLastInput();
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator.getScreenOutput()));
}

void MainWindow::popUp_InvalidSyntax()
{
    QMessageBox notifyBox;
    notifyBox.setWindowTitle("Error");
    notifyBox.setText("Invalid equation syntax.");
    notifyBox.exec();
}
