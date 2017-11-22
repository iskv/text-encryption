/*
 * В данной лабораторной работе используем для шифрования текста - Шифр простой замены - Шифр Цезаря
 * Для расшифровки текста - Метод частотного криптоанализа
 */

#include <iostream>
#include <fstream>

using namespace std;

bool encryption();
bool decryption();

int main()
{
    try {

    if (encryption()) cout << "Enc complete" << endl;
    if (decryption()) cout << "Dec complete" << endl;

    } catch (const char* err) {
        cout << err << endl;
    }    

    cin.get();
    return 0;
}

bool encryption()
{
    const int k = 3;   

    ifstream inp {"text_inp.txt"};    
    ofstream out {"text_out.txt"};
    if (!inp || !out) throw "Error opening file";

    char c_x, c_y;
    while (inp) {
        c_x = inp.get();
        c_y = c_x + k;        
        out << c_y;
    }
    return true;
}

bool decryption()
{
    int inp_mas[256] = {0};
    int out_mas[256] = {0};

// Анализ исходного файла:
    ifstream inp{"text_inp.txt"};
    if (!inp) throw "Error opening file!";

    char c = 0;
    int counter = 0; // кол-во символов в тексте
    while (inp) {
        c = inp.get();
        inp_mas[c]++;
        //counter++;
    }

// Анализ зашифрованного файла:
    counter = 0;
    inp.close();
    inp.open("text_out.txt");
    if (!inp) throw "Error opening file!";

    while (inp) {
        c = inp.get();
        out_mas[c]++;
    }

// Дешифрация:
    ofstream out{"out_freq.txt"};
    if (!out) throw "Error save file";
    inp.close();
    inp.open("text_out.txt");
    if (!inp) throw "Error opening file!";
// Сравнение по частотам:
    while (inp) {
        c = inp.get();
        for (int i = 0; i < 256; i++) {
            if (out_mas[c] == inp_mas[i] && inp_mas[i] != 0) out << char(i);
        }
    }
    return true;
}
