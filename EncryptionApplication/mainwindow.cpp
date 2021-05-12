#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
using std::string;

int getRandomNumber(int);
bool isPrime(int number);
string cipherByVigenereCipher(string& data, const string& key);
string decipherByVigenereCipher(string& data, const string& key);
string cipherByCaesarCipher(string& data, int shft);
string decipherByCaesarCipher(string& data, int shft);
string compressRLE(string& data);
string decompressRLE(string& data);
double encryptionRSA(double& prime_number1, double& prime_number2, double& message);
double decryptionRSA(double prime_number1, double prime_number2, double encrypted_message);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditPrimeNumber1->setValidator(new QIntValidator);
    ui->lineEditPrimeNumber2->setValidator(new QIntValidator);
    ui->lineEditSource_6->setValidator(new QDoubleValidator);
    ui->lineEditEncrypted_6->setValidator(new QDoubleValidator);
    ui->lineEditDecrypted_6->setValidator(new QDoubleValidator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonGeneratePattern_clicked()
{
    ui->lineEditPattern1->setText("ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz0123456789");
    QString alpha_numeric = ui->lineEditPattern1->text();
    QString pattern(alpha_numeric);
    std::random_shuffle(pattern.begin(), pattern.end(),getRandomNumber);   //shuffle letters in a string
    ui->lineEditPattern2->setText(pattern); //set text in line edit
}

void MainWindow::on_pushButtonEncrypt_clicked()
{
    QString source = ui->lineEditSource->text();            //get source text
    QString alpha_numeric = ui->lineEditPattern1->text();   //get alphabet pattern
    QString pattern = ui->lineEditPattern2->text();         //get key pattern
    QString encoded_text;
    int index = 0;
    while (index < source.length()) {//passes over source text elements
        int key_index;
        for (key_index = 0; key_index < alpha_numeric.length() && (source[index] != alpha_numeric[key_index]); key_index++);
        if (key_index < alpha_numeric.length())
        {
            encoded_text.append(pattern[key_index]);
        } else {
            encoded_text.append(source[index]);
        }
        ++index;
    }
    ui->lineEditEncrypted->setText(encoded_text);   //shows encrypted text
}

void MainWindow::on_pushButtonDecrypt_clicked()
{
    QString encoded_text = ui->lineEditEncrypted->text();   //get encrypted text
    QString alpha_numeric = ui->lineEditPattern1->text();   //get alphabet pattern
    QString pattern = ui->lineEditPattern2->text();         //get key pattern
    QString decoded_text;
    for (int index = 0; index < encoded_text.length(); ++index)
    {
        int key_index;
        for (key_index = 0; key_index < pattern.size() && encoded_text[index] != pattern[key_index]; key_index++);
        if (key_index < pattern.size()) {
           decoded_text.append(alpha_numeric[key_index]);
        } else {
            decoded_text.append(encoded_text[index]);
        }
    }
    ui->lineEditDecrypted->setText(decoded_text);
}

void MainWindow::on_pushButtonEncrypt_2_clicked()
{
    int table_size = ui->spinBox->value();
    QString source = ui->lineEditSource_2->text();
    QString encoded_data;
    for (int column = 0; column < table_size; column++) {
        for (int index = column; index < source.size() && source[index] != '\0'; index += table_size)
        {
            encoded_data.append(source[index]);
        }
    }
    ui->lineEditEncrypted_2->setText(encoded_data);
}

void MainWindow::on_pushButtonDecrypt_2_clicked()
{
    int table_size = ui->spinBox->value();
    QString encoded_data = ui->lineEditEncrypted_2->text();
    QString decoded_data;
    int count, step_length = encoded_data.size() / table_size + 1;
    count = step_length;
    for (int start_index = 0; start_index < count; start_index++) {
        int index = start_index, num = 0;
        for (; num < encoded_data.size() % table_size && encoded_data[index] != '\0'; index += step_length, num++)
        {
            decoded_data.push_back(encoded_data[index]);
        }
        if (decoded_data.size() == encoded_data.size())
            break;
        for (; num < table_size && encoded_data[index] != '\0'; index += (step_length - 1), num++)
        {
            decoded_data.push_back(encoded_data[index]);
        }
        step_length = encoded_data.size() / table_size + 1;
    }
    ui->lineEditDecrypted_2->setText(decoded_data);
}

void MainWindow::on_pushButtonEncrypt_3_clicked()
{
    QString key = ui->lineEditVigenereEncryptionKey->text();
    QString source = ui->lineEditSource_3->text();

    string key_8bit = key.toLocal8Bit().constData();
    string source_8bit = source.toLocal8Bit().constData();
    string encoded_data_8bit = cipherByVigenereCipher(source_8bit, key_8bit);
    QString encoded_data = QString::fromLocal8Bit(encoded_data_8bit);
    ui->lineEditEncrypted_3->setText(encoded_data);
}

void MainWindow::on_pushButtonDecrypt_3_clicked()
{
    QString key = ui->lineEditVigenereEncryptionKey->text();
    QString encoded_data = ui->lineEditEncrypted_3->text();

    string key_8bit = key.toLocal8Bit().constData();
    string encoded_data_8bit = encoded_data.toLocal8Bit().constData();
    string decoded_data_8bit = decipherByVigenereCipher(encoded_data_8bit, key_8bit);
    QString decoded_data = QString::fromLocal8Bit(decoded_data_8bit);
    ui->lineEditDecrypted_3->setText(decoded_data);
}

void MainWindow::on_pushButtonEncrypt_4_clicked()
{
    int shift_size = ui->spinBox_2->value();
    QString source = ui->lineEditSource_4->text();

    string source_8bit = source.toLocal8Bit().constData();
    string encoded_data_8bit = cipherByCaesarCipher(source_8bit, shift_size);
    QString encoded_data = QString::fromLocal8Bit(encoded_data_8bit);
    ui->lineEditEncrypted_4->setText(encoded_data);
}

void MainWindow::on_pushButtonDecrypt_4_clicked()
{
    int shift_size = ui->spinBox_2->value();
    QString encoded_data = ui->lineEditEncrypted_4->text();

    string encoded_data_8bit = encoded_data.toLocal8Bit().constData();
    string decoded_data_8bit = decipherByCaesarCipher(encoded_data_8bit, shift_size);
    QString decoded_data = QString::fromLocal8Bit(decoded_data_8bit);
    ui->lineEditDecrypted_4->setText(decoded_data);
}

void MainWindow::on_pushButtonEncrypt_5_clicked()
{
    QString source = ui->lineEditSource_5->text();

    string source_8bit = source.toLocal8Bit().constData();
    string compressed_data_8bit = compressRLE(source_8bit);
    QString compressed_data = QString::fromLocal8Bit(compressed_data_8bit);
    ui->lineEditEncrypted_5->setText(compressed_data);
}


void MainWindow::on_pushButtonDecrypt_5_clicked()
{
    QString compressed_data = ui->lineEditEncrypted_5->text();

    string compressed_data_8bit = compressed_data.toLocal8Bit().constData();
    string decompressed_data_8bit = decompressRLE(compressed_data_8bit);
    QString decompressed_data = QString::fromLocal8Bit(decompressed_data_8bit);
    ui->lineEditDecrypted_5->setText(decompressed_data);
}

void MainWindow::on_pushButtonEncrypt_6_clicked()
{

    double prime_number1 = ui->lineEditPrimeNumber1->text().toInt();
    double prime_number2 = ui->lineEditPrimeNumber2->text().toInt();
    if (isPrime(prime_number1) && isPrime(prime_number2)) {
        double source = ui->lineEditSource_6->text().toDouble();
        double encrypted_message = encryptionRSA(prime_number1, prime_number2, source);
        encrypted_message = fmod(encrypted_message, prime_number1 * prime_number2);
        ui->lineEditEncrypted_6->setText(QString::number(encrypted_message));
    } else {
        QMessageBox::warning(this, "Warning", "Passed numbers isn't prime.");
    }
}


void MainWindow::on_pushButtonDecrypt_6_clicked()
{
    double prime_number1 = ui->lineEditPrimeNumber1->text().toInt();
    double prime_number2 = ui->lineEditPrimeNumber2->text().toInt();
    if (isPrime(prime_number1) && isPrime(prime_number2)) {
        double source = ui->lineEditSource_6->text().toDouble();
        double encrypted_message = encryptionRSA(prime_number1, prime_number2, source);
        double decrypted_message = decryptionRSA(prime_number1, prime_number2, encrypted_message);
        ui->lineEditDecrypted_6->setText(QString::number(decrypted_message));
    } else {
        QMessageBox::warning(this, "Warning", "Passed numbers isn't prime.");
    }
}
