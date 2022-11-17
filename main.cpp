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

template<typename F>
long measureTime(F &&lambda) {
    auto start = std::chrono::high_resolution_clock::now();
    lambda();
    auto stop = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}

int main() {
    map<string, pair<string, void (*)()>> functions{
            {"5-1",  {"Алгоритм Евклида",                                               task5_1}},
            {"5-2",  {"Решето Эратосфена",                                              task5_2}},
            {"5-3",  {"Преобразование разделителей: превращение строк в столбцы фраз",  task5_3}},
            {"5-4",  {"Проверка баланса скобок в текстовом файле",                      task5_4}},
            {"5-5",  {"Ряд произведения",                                               task5_5}},
            {"5-6",  {"Перевод массива вещественных чисел в целевую систему счисления", task5_6}},
            {"5-7",  {"Организация хранения массивов в файле и операции с ними",        task5_7}},
            {"6-1",  {"Шарики",                                                         task6_1}},
            {"6-2",  {"21. Восточный календарь",                                        task6_2}},
            {"6-3",  {"101. В мире животных",                                           task6_3}},
            {"6-4",  {"131. Удалить лишние пробелы, разделяющие слова в строке",        task6_4}},
            {"6-5",  {"76. Операции с комплексными числами",                            task6_5}},
            {"6-6",  {"56а. Танцы с бубном (матрицами)",                                task6_6}},
            {"test", {"Life is suffering",                                              findOptimal}},
    };
    while (true) {
        cout << BLUE_FG_BOLD << "Enter task number (e.g. 5-1): ";

        std::function<bool(string)> isValidTask = [&functions](const string &s) {
            return s == "list" || functions.find(s) != functions.end();
        };
        string s = enter(isValidTask);

        if (s == "list") {
            for (const auto &func : functions) {
                cout << RESET << GREEN_FG << func.first << "\t" << func.second.first << "\n";
            }
            continue;
        }

        auto it = functions.find(s);

        char c = 'r';
        while (c == 'r' || c == 'n') {
            cout << BOLD << GREEN_FG << it->first << ": " << it->second.first << "\n"
                 << RESET << "\n";
            long runtime = measureTime([&it]() {
                it->second.second();
            });
            cout << "\n" << RED_FG_BOLD << "Runtime: " << runtime << "ms" << "\n"
                 << BLUE_FG_BOLD << "[e]xit, [r]estart, [n]ext or [c]hoose (default)? ";
            cin >> c;
            cin.ignore(32767, '\n');

            if (c == 'n' && ++it == functions.end()) {
                it = functions.begin();
            }
        }

        if (c == 'e') break;
    }
    cout << RED_FG_BOLD << "Good bye!\n" << RESET;
}

// 0.012121212
// 0.030303030
// 0.103030302