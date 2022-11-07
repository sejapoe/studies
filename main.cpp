#include <iostream>
#include <map>
#include <functional>
#include "enter.h"
#include "5-1.h"
#include "5-2.h"
#include "5-3.h"
#include "5-4.h"
#include "5-5.h"
#include "5-6.h"
#include "5-7.h"
#include "6-1.h"
#include "6-2.h"
#include "6-3.h"
#include "6-4.h"
#include "6-5.h"
#include "6-6.h"

using namespace std;

int main() {
    map<string, pair<string, void (*)()>> functions{
            {"5-1", {"Алгоритм Евклида",                                               task5_1}},
            {"5-2", {"Решето Эратосфена",                                              task5_2}},
            {"5-3", {"Преобразование разделителей: превращение строк в столбцы фраз",  task5_3}},
            {"5-4", {"Проверка баланса скобок в текстовом файле",                      task5_4}},
            {"5-5", {"Ряд произведения",                                               task5_5}},
            {"5-6", {"Перевод массива вещественных чисел в целевую систему счисления", task5_6}},
            {"5-7", {"Организация хранения массивов в файле и операции с ними",        task5_7}},
            {"6-1", {"Шарики",                                                         task6_1}},
            {"6-2", {"21. Восточный календарь",                                        task6_2}},
            {"6-3", {"101. В мире животных",                                           task6_3}},
            {"6-4", {"131. Удалить лишние пробелы, разделяющие слова в строке",        task6_4}},
            {"6-5", {"76. Операции с комплексными числами",                            task6_5}},
            {"6-6", {"56а. Танцы с бубном (матрицами)",                                task6_6}}
    };
    cout << BLUE_FG_BOLD;
    while (true) {
        cout << "Enter task number (e.g. 5-1): ";

        std::function<bool (string)> isValidTask = [&functions] (const string& s) {
            return functions.find(s) != functions.end();
        };
        string s = enter(isValidTask);

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
    cout << RED_FG_BOLD << "Good bye!\n" << RESET;
}

// 0.012121212
// 0.030303030
// 0.103030302