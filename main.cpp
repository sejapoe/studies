#include <iostream>
#include <map>
#include "5-1.h"
#include "5-2.h"
#include "5-3.h"
#include "5-4.h"
#include "5-5.h"
#include "5-6.h"
#include "5-7.h"

using namespace std;

int main() {
    map<string, pair<string, void (*)()>> functions{
            {"5-1", {"Алгоритм Евклида",                                               task5_1}},
            {"5-2", {"Решето Эратосфена",                                              task5_2}},
            {"5-3", {"Преобразование разделителей: превращение строк в столбцы фраз",                      task5_3}},
            {"5-4", {"Проверка баланса скобок в текстовом файле",  task5_4}},
            {"5-5", {"Ряд произведения",                                               task5_5}},
            {"5-6", {"Перевод массива вещественных чисел в целевую систему счисления", task5_6}},
            {"5-7", {"Организация хранения массивов в файле и операции с ними",        task5_7}}
    };
    cout << BLUE_FG_BOLD;
    while (true) {
        cout << "Enter task number (e.g. 5-1): ";

        string s;
        cin >> s;
        while (cin.fail() || functions.find(s) == functions.end()) {
            cout << RED_FG_BOLD << "Invalid task. Try again: ";
            cin.clear();
            cin.ignore(32767, '\n');
            cin >> s;
        }

        auto it = functions.find(s);

        char c = 'r';
        while (c == 'r') {
            cout << BOLD << GREEN_FG << it->second.first << "\n";
            cout << RESET;
            it->second.second();
            cout << BLUE_FG_BOLD;
            cout << "[e]xit, [r]estart or [c]ontinue (default)? ";
            cin >> c;
            cin.ignore(32767, '\n');
        }

        if (c == 'e') break;
    }
    cout << "Good bye!";
}

// 0.012121212
// 0.030303030
// 0.103030302