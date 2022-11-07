//
// Created by sejapoe on 10/30/22.
//
// Решето Эратосфена

#ifndef FIRST_5_2_H
#define FIRST_5_2_H

#include "colors.h"

void task5_2() {
    cout << BLUE_FG << "Enter N: ";

    int n = enter(static_cast<function<bool(int)>>([](int t) {
        return t > 2;
    }));

    int *a = new int[n - 1];
    for (int i = 2; i <= n; i++) {
        a[i - 2] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] != -1 && a[i] != -1 && a[j] % a[i] == 0) {
                a[j] = -1;
            }
        }
    }

    int c = 0;
    cout << GREEN_FG;
    for (int i = 0; i < n; i++) {
        if (a[i] != -1) {
            cout << a[i] << " ";
            if (++c % 20 == 19) {
                cout << "\n";
            }
        }
    }

    cout << BOLD << "\nTotal primes: " << c << "\n" << RESET;
}

#endif //FIRST_5_2_H
