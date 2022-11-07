//
// Created by sejapoe on 11/8/22.
//

#ifndef FIRST_ENTER_H
#define FIRST_ENTER_H

#include <functional>
#include <iostream>
#include <sstream>
#include "colors.h"

std::function<bool(int)> const isPositive = [](int a) { return a > 0; };
std::function<bool(double)> const anyDouble = [](double a) { return true; };
std::function<bool(int)> const anyInt = [](int a) { return true; };

template<typename T>
T enter(std::function<bool(T)> foo) {
    T t;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        if ((ss >> t) && ss.eof() && foo(t)) {
            break;
        }
        std::cout << RED_FG << "Invalid input. Try again: ";
    }
    return t;
}

#endif //FIRST_ENTER_H
