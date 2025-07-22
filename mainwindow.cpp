#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mainCalculator = new Calculator();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mainCalculator;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Escape)
    {
        QApplication::quit();
    }
    else if(event->key()==Qt::Key_Backspace)
    {
        mainCalculator->eraseFromBuffer();
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_0)
    {
        mainCalculator->appendToBuffer('0');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_1)
    {
        mainCalculator->appendToBuffer('1');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_2)
    {
        mainCalculator->appendToBuffer('2');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_3)
    {
        mainCalculator->appendToBuffer('3');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_4)
    {
        mainCalculator->appendToBuffer('4');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_5)
    {
        mainCalculator->appendToBuffer('5');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_6)
    {
        mainCalculator->appendToBuffer('6');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_7)
    {
        mainCalculator->appendToBuffer('7');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_8)
    {
        mainCalculator->appendToBuffer('8');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_9)
    {
        mainCalculator->appendToBuffer('9');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_ParenLeft)
    {
        mainCalculator->appendToBuffer(1);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_ParenRight)
    {
        mainCalculator->appendToBuffer(0);
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_Plus)
    {
        mainCalculator->appendToBuffer('+');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_Minus)
    {
        mainCalculator->appendToBuffer('-');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_Asterisk)
    {
        mainCalculator->appendToBuffer('*');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else if(event->key()==Qt::Key_Slash)
    {
        mainCalculator->appendToBuffer('/');
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else
    {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    QMainWindow::keyReleaseEvent(event);
}


void MainWindow::on_pushButton_num0_clicked()
{
    mainCalculator->appendToBuffer('0');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_num1_clicked()
{
    mainCalculator->appendToBuffer('1');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_num2_clicked()
{
    mainCalculator->appendToBuffer('2');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_num3_clicked()
{
    mainCalculator->appendToBuffer('3');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_num4_clicked()
{
    mainCalculator->appendToBuffer('4');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_num5_clicked()
{
    mainCalculator->appendToBuffer('5');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_num6_clicked()
{
    mainCalculator->appendToBuffer('6');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_num7_clicked()
{
    mainCalculator->appendToBuffer('7');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_num8_clicked()
{
    mainCalculator->appendToBuffer('8');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_num9_clicked()
{
    mainCalculator->appendToBuffer('9');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}

void MainWindow::on_pushButton_operatorPlus_clicked()
{
    mainCalculator->appendToBuffer('+');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_operatorSub_clicked()
{
    mainCalculator->appendToBuffer('-');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_operatorMul_clicked()
{
    mainCalculator->appendToBuffer('*');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_operatorDiv_clicked()
{
    mainCalculator->appendToBuffer('/');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_operatorExp_clicked()
{
    mainCalculator->appendToBuffer('^');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}

void MainWindow::on_pushButton_decimalPoint_clicked()
{
    mainCalculator->appendToBuffer('.');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}


void MainWindow::on_pushButton_parenOpen_clicked()
{
    mainCalculator->appendToBuffer('(');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}
void MainWindow::on_pushButton_parenClosed_clicked()
{
    mainCalculator->appendToBuffer(')');
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}

void MainWindow::on_pushButton_Mod_clicked()
{

}


void MainWindow::on_pushButton_Sin_clicked()
{

}


void MainWindow::on_pushButton_Cos_clicked()
{

}


void MainWindow::on_pushButton_Tan_clicked()
{

}


void MainWindow::on_pushButton_comma_clicked()
{

}

void MainWindow::on_pushButton_enter_clicked()
{
    try
    {
        mainCalculator->execCalc();
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    } catch (int errorNum) {
        this->errorHandler(errorNum);
    }
}

void MainWindow::on_pushButton_backspace_clicked()
{
    mainCalculator->eraseFromBuffer();
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}

void MainWindow::on_pushButton_clr_clicked()
{
    mainCalculator->clearBuffer();
    ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
}

void MainWindow::errorHandler(int errorNum)
{
    if(errorNum==1051)
    {
        QMessageBox notifyBox;
        notifyBox.setWindowTitle("Error");
        notifyBox.setText("Invalid syntax");
        notifyBox.exec();
    }
    else if(errorNum==1071)
    {
        QMessageBox notifyBox;
        notifyBox.setWindowTitle("Error");
        notifyBox.setText("Unclosed parenthesis(es)");
        notifyBox.exec();
        mainCalculator->clearBuffer();
        mainCalculator->~Calculator();
        mainCalculator = new Calculator();
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
    else
    {
        QMessageBox notifyBox;
        notifyBox.setWindowTitle("Error");
        notifyBox.setText(QString::number(errorNum));
        notifyBox.exec();
        mainCalculator->clearBuffer();
        mainCalculator->~Calculator();
        mainCalculator = new Calculator();
        ui->outputPanel->setText(QString::fromUtf8(mainCalculator->getBuffer()));
    }
}
