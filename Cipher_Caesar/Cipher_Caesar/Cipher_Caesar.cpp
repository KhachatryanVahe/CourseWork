#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;


void Encript_Caesar(string& txt, int shft)
{
    for (int index = 0; index < txt.length(); index++)
    {
        if (isalpha(txt[index]))
        {
            if (isupper(txt[index]))
            {
                txt[index] = (txt[index] + shft - 65) % 26 + 65;
            }
            else
            {
                txt[index] = (txt[index] + shft - 97) % 26 + 97;
            }
        }
    }
}

void Decrypt_Caesar(string& txt, int shft)
{
    for (int index = 0; index < txt.length(); index++)
    {
        if (isalpha(txt[index])) 
        {
            if (isupper(txt[index]))
            {
                txt[index] = (txt[index] + (26 - shft) - 65) % 26 + 65;
            }
            else
            {
                txt[index] = (txt[index] + (26 - shft) - 97) % 26 + 97;
            }
        }
    }
}

int main()
{
    string Text;
    int shift;
    cout << "Enter your text: ";
    std::getline(cin, Text);
    cout << "Shift: ";
    cin >> shift;

    Encript_Caesar(Text, shift);
    cout << "Encrypted text: " << Text << endl;
    Decrypt_Caesar(Text, shift);
    cout << "Decrypted text: " << Text << endl;

}
