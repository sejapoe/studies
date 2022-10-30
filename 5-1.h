//
// Created by sejapoe on 10/30/22.
//

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
    cout << BLUE_FG << "Enter two numbers: ";

    int a, b;
    cin >> a >> b;
    while (cin.fail() || a < 0 || b < 0) {
        cout << RED_FG << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(32767, '\n');
        cin >> a >> b;
    }

    cout << BLUE_FG << "Choose variant:\n1. By Minus.\n2. By Mod\n...";

    int var;
    cin >> var;
    while (cin.fail() || !(var == 1 || var == 2)) {
        cout << RED_FG << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(32767, '\n');
        cin >> var;
    }

    int res = var == 1 ? euclidByMinus(a, b) : euclidByMod(a, b);

    cout << GREEN_FG << "GCD = " << res << "\n" << RESET;
}

#endif //FIRST_5_1_H
