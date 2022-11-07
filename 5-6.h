//
// Created by sejapoe on 10/30/22.
//
// Задан массив F[1:n] из вещественных чисел в десятичной системе счисления.
// В другом массиве организовать перевод исходного массива в любую систему счисления
// по желанию пользователя в пределах от двоичной до девятеричной

#ifndef FIRST_5_6_H
#define FIRST_5_6_H

#include <vector>
#include "colors.h"

void reverse(string &s) {
    string s1;
    for (int i = 1; i <= s.size(); i++) {
        s1.push_back(tolower(s[s.size() - i]));
    }
    s = s1;
}

string convertFromDecimal(int output_notation, double a) {
    string s;
    int intPart = int(a);
    double floatPart = a - intPart;
    while (int(a) != 0) {
        int x = int(a) % output_notation;
        char c = (char) (x >= 10 ? 'a' + x - 10 : '0' + x);
        s += c;
        a /= output_notation;
    }
    reverse(s);

    if (floatPart != 0.0) {
        s += '.';
        vector<double> history;
        while (floatPart > 1e-8) {
            auto iterator = find_if(history.begin(), history.end(), [&floatPart](double a) {
                return abs(a - floatPart) < 1e-8;
            });
            if (iterator != history.end()) {
                s.insert(s.end() - (history.end() - iterator), '(');
                s += ')';
                break;
            }
            if (history.size() > 10) {
                s.insert(s.begin(), '~');
                break;
            }

            double t = floatPart * output_notation;
            int x = int(t);
            history.push_back(floatPart);
            floatPart = t - x;
            s += (char) (x >= 10 ? 'a' + x - 10 : '0' + x);
        }
    }
    return s;
}


void task5_6() {
    cout << BLUE_FG << "Enter array size... ";
    int n = enter(isPositive);

    auto inputArray = new double[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter " << i << "th double: ";
        inputArray[i] = enter(anyDouble);
    }

    cout << BLUE_FG << "Enter target notation (2-9)... ";

    int notation = enter(static_cast<function<bool(int)>>([](int t) {
        return t >= 2 && t <= 9;
    }));

    auto resultArray = new string[n];
    for (int i = 0; i < n; i++) {
        resultArray[i] = convertFromDecimal(notation, inputArray[i]);
    }

    cout.precision(4);
    cout << GREEN_FG;
    for (int i = 0; i < n; i++) {
        cout << inputArray[i] << " -> " << resultArray[i] << "\n";
    }
    cout << RESET;
}

#endif //FIRST_5_6_H
