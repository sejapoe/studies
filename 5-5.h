//
// Created by sejapoe on 10/30/22.
//
// Дано целое число n (вводится с клавиатуры). Вычислить:
// y = prod(int i = 1; i <= n; i++) {
//     i! / sum(int j = 1; j <= i; j++) { sin(2*j) }
// }

#ifndef FIRST_5_5_H
#define FIRST_5_5_H

#include <cmath>
#include <gmpxx.h>
#include "colors.h"

void task5_5() {
    cout << BLUE_FG << "Enter n: ";

    int n = enter(isPositive);

    mpf_class y = 1;
    mpf_class prevFact = 1;
    mpf_class sinSum = 0;

    for (int i = 1; i <= n; i++) {
        prevFact *= i;
        y *= prevFact;
        sinSum += sin(2 * i);
        y /= sinSum;

    }
    cout << GREEN_FG << y << "\n" << RESET;
}

#endif //FIRST_5_5_H
