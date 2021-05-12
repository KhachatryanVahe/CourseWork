#include <QString>
#include <cmath>
using std::string;

int getRandomNumber(int i)
{
    return std::rand() % i;
}

QString generatePattern(const QString& source)
{
    QString output(source);
    std::random_shuffle(output.begin(), output.end(),getRandomNumber);
    return output;
}

bool isPrime(int number)    //checks the pased number is prime or not
{
    int i = 2;
    while (i <= sqrt(number) && number % i != 0) {
        i++;
    }
    if (sqrt(number) < i) {
        return true;
    }
    else {
        return false;
    }
}

int findGreatestCommonDivisor(int a, int b) //finds greatest common divisor for two numbers
{
    while (a != b)
    {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

//===============Vigenere Cipher=============
string cipherByVigenereCipher(string& data, const string& key)
{
    string encoded_data;
    int length = key.length(), index_key = 0, index_encoded_data = 0, num, diff;
    for (size_t index_data = 0; index_data < data.size(); index_data++, index_encoded_data++)
    {
        diff = 65;
        if (index_key == length) { //key repetition
            index_key = 0;
        }
        num = static_cast<int>(data[index_data]);
        if (65 <= num && num <= 90) {// if the character is lowercase
            if (static_cast<int>(key[index_key]) >= 97) {
                diff = 97;
            }
            num += (int)key[index_key] - diff;//num - ascii code of encrypted character
            if (num > 90) {
                num -= 26;
            }
            index_key++;
        } else {
            if (97 <= num && num <= 122) { //if the character is capitalized
                if (static_cast<int>(key[index_key]) >= 97)
                    diff = 97;
                num += static_cast<int>(key[index_key]) - diff; //num - ascii code of encrypted character
                if (num > 122)
                    num -= 26;
                index_key++;
            }
        }
        encoded_data.push_back(static_cast<char>(num));
    }
    return encoded_data;
}


string decipherByVigenereCipher(string& data, const string& key)
{
    string decoded_data;
    int length = key.length(), index_key = 0, index_encoded_data = 0, num, diff;
    for (size_t index_data = 0; index_data < data.size(); index_data++, index_encoded_data++) {
        diff = 65;
        if (index_key == length) {
            index_key = 0;
        }
        num = static_cast<int>(data[index_data]);
        if (65 <= num && num <= 90) {
            if (static_cast<int>(key[index_key]) >= 97) {
                diff = 97;
            }
            if (num - 65 < static_cast<int>(key[index_key]) - diff) {
                num += 26;
            }
            num += diff - static_cast<int>(key[index_key]);
            index_key++;
        } else {
            if (97 <= num && num <= 122) {
                if (static_cast<int>(key[index_key]) >= 97) {
                    diff = 97;
                }
                if (num - 97 < static_cast<int>(key[index_key]) - diff) {
                    num += 26;
                }
                num += diff - static_cast<int>(key[index_key]);
                index_key++;
            }
        }
        decoded_data.push_back(static_cast<char>(num));
    }
    return decoded_data;
}

//==============Caesare Cipher===================
string cipherByCaesarCipher(string& data, int shft)
{
    string encoded_data;
    for (size_t index = 0; index < data.length(); index++) {
        if (isalpha(data[index])) {
            if (isupper(data[index])) {
                encoded_data.push_back((data[index] + shft - 65) % 26 + 65);
            } else {
                encoded_data.push_back((data[index] + shft - 97) % 26 + 97);
            }
        } else {
            encoded_data.push_back(data[index]);
        }

    }
    return encoded_data;
}

string decipherByCaesarCipher(string& data, int shft)
{
    string decoded_data;
    for (size_t index = 0; index < data.length(); index++) {
        if (isalpha(data[index])) {
            if (isupper(data[index])) {
                decoded_data.push_back((data[index] + (26 - shft) - 65) % 26 + 65);
            } else {
                decoded_data.push_back((data[index] + (26 - shft) - 97) % 26 + 97);
            }
        } else {
            decoded_data.push_back(data[index]);
        }
    }
    return decoded_data;
}

//================Run-length encoding compression================
string compressRLE(string& data)
{
    string encoded_data;
    for (size_t index_data = 0; index_data < data.length(); index_data++) {
        size_t index_repeater_item = index_data, count_repeater_item = 0, count_unrepeater = 0;
        if (data[index_repeater_item] == data[index_repeater_item + 1]) {
            //while the characters are repeated
            while (data[index_repeater_item] != '\0' && data[index_repeater_item] == data[index_repeater_item + 1]) {
                index_repeater_item++;
                count_repeater_item++;
            }
        } else {
            //while the characters are not repeated
            while (data[index_repeater_item] != '\0' && data[index_repeater_item] != data[index_repeater_item + 1]) {
                index_repeater_item++;
                count_unrepeater++;
            }
        }
        if (count_repeater_item > 0) {
            encoded_data += static_cast<char>(count_repeater_item - 1 + 128);//writes number of repeated characters
            encoded_data += data[index_data];//writes the repeated character
            index_data = index_repeater_item;
        } else {
            encoded_data += static_cast<char>(count_unrepeater - 1);//writes number of non-repeated characters
            size_t i = 0;
            for (; i < count_unrepeater; i++) {//writes non-repeated character
                encoded_data += data[index_data + i];
            }
            index_data += count_unrepeater - 1;
        }
    }
    return encoded_data;
}

string decompressRLE(string& data)
{
    string decoded_data;
    int count;
    for (size_t index = 0; index < data.length(); index++) {
        count = static_cast<int>(data[index]);//byte showing the number of characters
        if ( count < 0) {
            count += 130;   //quantity of repeated characters
            int index_decode = 0;
            for (; index_decode < count; index_decode++)    //writes the repeated characters
            {
                decoded_data += data[index + 1];
            }
            index++;
        } else {
            ++count;    //quantity of non-repeated character
            int index_decode = 0;
            for (; index_decode < count; index_decode++) {  //writes the not repeated characters
                decoded_data += data[++index];
            }
        }
    }
    return decoded_data;
}

//==============Rivest–Shamir–Adleman(RSA) algorithm==========
double encryptionRSA(double& prime_number1, double& prime_number2, double& message)
{
    //double product_prime_numbers = prime_number1 * prime_number2;
    double track = 0;
    double phi = (prime_number1 - 1) * (prime_number2 - 1); //calculate phi
    //public key stands for encrypt
    double public_key = 2;
    //for checking that 1 < public_key < phi(n) and gcd(public_key, phi(n)) = 1; i.e., e and phi(n) are coprime.
    while (public_key < phi && track != 1) {
        track = findGreatestCommonDivisor(public_key, phi);
        if (1 != track) {
            public_key++;
        }
    }
    //private key stands for decrypt
    double encrypted_message = pow(message, public_key); //encrypt the message
    //encrypted_message = fmod(encrypted_message, product_prime_numbers);
    return encrypted_message;
}

double decryptionRSA(double prime_number1, double prime_number2, double encrypted_message)
{
    double product_prime_number = prime_number1 * prime_number2;
    double track = 0;
    double phi = (prime_number1 - 1) * (prime_number2 - 1); //calculate phi
    double public_key = 2;
    //for checking that 1 < public_key < phi(n) and gcd(public_key, phi(n)) = 1; i.e., e and phi(n) are coprime.
    while (public_key < phi && track != 1) {
        track = findGreatestCommonDivisor(public_key, phi);
        if (1 != track) {
            public_key++;
        }
    }
    //private key stands for decrypt
    double private_key = fmod(1 / public_key, phi);
    double decrypted_message = pow(encrypted_message, private_key);
    decrypted_message = fmod(decrypted_message, product_prime_number);
    return decrypted_message;
}
