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

private slots:
    void on_pushButtonGeneratePattern_clicked();
    //Pattern based encryption encrypt and decrypt buttons
    void on_pushButtonEncrypt_clicked();
    void on_pushButtonDecrypt_clicked();
    //Row and column based encryption encrypt and decrypt buttons
    void on_pushButtonEncrypt_2_clicked();
    void on_pushButtonDecrypt_2_clicked();
    //Vignenere encryption encrypt and decrypt buttons
    void on_pushButtonEncrypt_3_clicked();
    void on_pushButtonDecrypt_3_clicked();

    void on_pushButtonEncrypt_4_clicked();

    void on_pushButtonDecrypt_4_clicked();

    void on_pushButtonEncrypt_5_clicked();

    void on_pushButtonDecrypt_5_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
