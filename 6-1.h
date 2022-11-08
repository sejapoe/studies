//
// Created by sejapoe on 10/30/22.
//
// Шарики

#ifndef FIRST_6_1_H
#define FIRST_6_1_H

#include <vector>

void task6_1() {
    cout << BLUE_FG << "Enter N: ";
    int n = enter(isPositive);

    int64_t prev = 0;
    for (int i = 1; i < n; i++) {
        prev = i * prev + pow(-1, i + 1);
    }
    cout << GREEN_FG << "Result: " << prev << "\n" << RESET;
}

#endif //FIRST_6_1_H
