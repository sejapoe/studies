//
// Created by sejapoe on 10/30/22.
//

#ifndef FIRST_6_1_H
#define FIRST_6_1_H

#include <vector>

void task6_1() {
    int n;
    cout << BLUE_FG << "Enter N: ";
    cin >> n;
    while (cin.fail() || n <= 0) {
        cout << RED_FG << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(32767, '\n');
        cin >> n;
    }

    int prev = 0;
    for (int i = 1; i < n; i++) {
        prev = i*prev + pow(-1, i + 1);
    }
    cout << GREEN_FG << "Result: " << prev << "\n" << RESET;
}

#endif //FIRST_6_1_H
