#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include <stack>
#include "QMessageBox"
#include <cmath>

using namespace std;

stack <double> steck;
int count_stack = 0;

int count_lab_next = 0;

double num;

bool res = 0;
bool check_dot = 1;
bool size_window = 1;

QString lab_next, lab_prev;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(enter_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(enter_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(enter_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(enter_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(enter_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(enter_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(enter_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(enter_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(enter_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(enter_numbers()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enter_numbers()
{
    QPushButton *button = (QPushButton*)sender();

    QString lab;

    num = (lab_next+button->text()).toDouble();
    lab = QString::number(num,'g',14);
    lab_next = lab_next+button->text();
    count_lab_next++;
    if (button->text() == '0' && lab_next.indexOf('.') != -1)
        ui->label->setText(lab_prev+lab_next);
    else
        ui->label->setText(lab_prev+lab);
    res = 1;
}



void MainWindow::on_pushButton_result_clicked()
{
    if (count_stack != 1)
    {
        QMessageBox msgBox;

        msgBox.setText("Ошибка!!!");

        msgBox.exec();
    }
    else
    {
        lab_next = "";
        count_lab_next = 0;
        lab_prev = "";
        ui->label->setText(QString::number(steck.top(), 'g', 14));
        steck.pop();
        count_stack = 0;
        check_dot = 1;
    }
}


void MainWindow::on_pushButton_reset_clicked()
{
    ui->label->setText("");
    for (int i=1; i<=count_stack; i++)
        steck.pop();
    count_stack = 0;
    lab_prev = "";
    lab_next = "";
    count_lab_next = 0;
    res = 0;
    check_dot = 1;
}


void MainWindow::on_pushButton_enter_clicked()
{
    steck.push(num);
    count_stack++;
    lab_prev = lab_prev + lab_next + " ";
    lab_next = "";
    count_lab_next = 0;
    ui->label->setText(lab_prev);
    check_dot = 1;
    num = 0;
}


void MainWindow::on_pushButton_plus_clicked()
{
    if (res)
    {
        steck.push(num);
        count_stack++;
        res = 0;
    }
    if (count_stack < 2)
    {
        QMessageBox msgBox;

        msgBox.setText("Ошибка! Недостаточно чисел для сложения!");

        msgBox.exec();
    } else
    {
        lab_prev = lab_prev + lab_next + " + ";
        lab_next = "";
        count_lab_next = 0;
        ui->label->setText(lab_prev);
        double top_1 = steck.top();
        steck.pop(); count_stack--;
        double top_2 = steck.top();
        steck.pop();
        steck.push(top_1 + top_2);
    }
}


void MainWindow::on_pushButton_minus_clicked()
{
    if (res)
    {
        steck.push(num);
        count_stack++;
        res = 0;
    }
    if (count_stack < 2)
    {
        QMessageBox msgBox;

        msgBox.setText("Ошибка! Недостаточно чисел для вычитания!");

        msgBox.exec();
    } else
    {
        lab_prev = lab_prev + lab_next + " - ";
        lab_next = "";
        count_lab_next = 0;
        ui->label->setText(lab_prev);
        double top_1 = steck.top();
        steck.pop(); count_stack--;
        double top_2 = steck.top();
        steck.pop();
        steck.push(top_2 - top_1);
    }
}


void MainWindow::on_pushButton_divide_clicked()
{
    if (res)
    {
        steck.push(num);
        count_stack++;
        res = 0;
    }
    if (count_stack < 2)
    {
        QMessageBox msgBox;

        msgBox.setText("Ошибка! Недостаточно чисел для деления!");

        msgBox.exec();
    } else
    {
        if (steck.top()==0)
        {
            QMessageBox msgBox;

            msgBox.setText("Ошибка! Попытка деления на ноль!");

            msgBox.exec();
        }
        else
        {
            lab_prev = lab_prev + lab_next + " / ";
            lab_next = "";
            count_lab_next = 0;
            ui->label->setText(lab_prev);
            double top_1 = steck.top();
            steck.pop(); count_stack--;
            double top_2 = steck.top();
            steck.pop();
            steck.push(top_2 / top_1);
        }
    }
}


void MainWindow::on_pushButton_mult_clicked()
{
    if (res)
    {
        steck.push(num);
        count_stack++;
        res = 0;
    }
    if (count_stack < 2)
    {
        QMessageBox msgBox;

        msgBox.setText("Ошибка! Недостаточно чисел для умножения!");

        msgBox.exec();
    } else
    {
        lab_prev = lab_prev + lab_next + " x ";
        lab_next = "";
        count_lab_next = 0;
        ui->label->setText(lab_prev);
        double top_1 = steck.top();
        steck.pop(); count_stack--;
        double top_2 = steck.top();
        steck.pop();
        steck.push(top_2 * top_1);
    }
}


void MainWindow::on_pushButton_edit_clicked()
{
    if (count_lab_next != 0)
    {
        count_lab_next--;
        lab_next = lab_next.left(count_lab_next);
        ui->label->setText(lab_prev+lab_next);
        if (lab_next.endsWith('.')) check_dot = 1;
    }
}


void MainWindow::on_pushButton_dot_clicked()
{
    if (check_dot)
    {
        QString lab;
        num = (lab_next+'.').toDouble();
        lab = QString::number(num,'g',14);
        lab_next = lab_next+'.';
        count_lab_next++;
        ui->label->setText(lab_prev+lab+'.');
        res = 1;
        check_dot = 0;
    }
}


void MainWindow::on_pushButton_plus_minus_clicked()
{
    num = num * -1;
    lab_next = '-' + lab_next;
    ui->label->setText(lab_prev+lab_next);
}


void MainWindow::on_pushButton_stepen_clicked()
{
    if (res)
    {
        steck.push(num);
        count_stack++;
        res = 0;
    }
    if (count_stack < 2)
    {
        QMessageBox msgBox;

        msgBox.setText("Ошибка! Недостаточно чисел для возведения в степень!");

        msgBox.exec();
    } else
    {
        if (lab_next.indexOf('.') != -1 || lab_next.indexOf('-') != -1)
        {
            QMessageBox msgBox;

            msgBox.setText("Ошибка! Степень должна быть натуральной!");

            msgBox.exec();
        }
        else
        {
            lab_prev = lab_prev + lab_next + " ^ ";
            lab_next = "";
            count_lab_next = 0;
            ui->label->setText(lab_prev);
            double top_1 = steck.top();
            steck.pop(); count_stack--;
            double top_2 = steck.top();
            steck.pop();
            steck.push(pow(top_2, top_1));
        }
    }
}


void MainWindow::on_pushButton_clicked()
{
    if (size_window){
        setGeometry(geometry().x(),geometry().y(),950,411);
        ui->label_2->setGeometry(ui->label_2->geometry().x(), ui->label_2->geometry().y(), 891, 371);
        ui->pushButton_10->setGeometry(857, 11, ui->pushButton_10->geometry().width(), ui->pushButton_10->geometry().height());
        ui->label_4->setGeometry(ui->label_4->geometry().x(), ui->label_4->geometry().y(), 891, 33);
        ui->label_5->setGeometry(ui->label_5->geometry().x(), ui->label_5->geometry().y(), 891, 21);
        size_window = 0;
    }
    else {
        setGeometry(geometry().x(),geometry().y(),519,411);
        ui->label_2->setGeometry(ui->label_2->geometry().x(), ui->label_2->geometry().y(), 501, 371);
        ui->pushButton_10->setGeometry(469, 11, ui->pushButton_10->geometry().width(), ui->pushButton_10->geometry().height());
        ui->label_4->setGeometry(ui->label_4->geometry().x(), ui->label_4->geometry().y(), 501, 33);
        ui->label_5->setGeometry(ui->label_5->geometry().x(), ui->label_5->geometry().y(), 501, 21);
        size_window = 1;
    }
}


void MainWindow::on_pushButton_10_clicked()
{
    qApp->quit();
}

