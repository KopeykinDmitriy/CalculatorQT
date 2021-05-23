#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void enter_numbers();
    void on_pushButton_result_clicked();
    void on_pushButton_reset_clicked();
    void on_pushButton_enter_clicked();
    void on_pushButton_plus_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_divide_clicked();
    void on_pushButton_mult_clicked();
    void on_pushButton_edit_clicked();
    void on_pushButton_dot_clicked();
    void on_pushButton_plus_minus_clicked();
    void on_pushButton_stepen_clicked();
    void on_pushButton_clicked();
    void on_pushButton_10_clicked();
};
#endif // MAINWINDOW_H
