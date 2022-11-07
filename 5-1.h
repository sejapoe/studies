//
// Created by sejapoe on 10/30/22.
//
// Алгоритм Евклида

#ifndef FIRST_5_1_H
#define FIRST_5_1_H

#include "colors.h"

using namespace std;

int euclidByMinus(int a, int b) {
    while (a != b) {
        int c = abs(a - b);
        a = min(a, b);
        b = c;
    }
    return a;
}

int euclidByMod(int a, int b) {
    while (a != b && b != 0) {
        int c = max(a, b) % min(a, b);
        a = min(a, b);
        b = c;
    }
    return a;
}


void task5_1() {
    cout << BLUE_FG << "Enter first number: ";

    int a = enter(isPositive);
    cout << BLUE_FG << "Enter second number: ";

    int b = enter(isPositive);

    cout << BLUE_FG << "Choose variant:\n1. By Minus.\n2. By Mod\n...";

    int var = enter(static_cast<function<bool(int)>>([](int var) {
        return var == 1 || var == 2;
    }));

    int res = var == 1 ? euclidByMinus(a, b) : euclidByMod(a, b);

    cout << GREEN_FG << "GCD = " << res << "\n" << RESET;
}

#endif //FIRST_5_1_H
