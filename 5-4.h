//
// Created by sejapoe on 10/30/22.
//

#ifndef FIRST_5_4_H
#define FIRST_5_4_H

#include <iostream>
#include <fstream>
#include "colors.h"

int findIndex(const string& str, const char& c) {
    for (int i = 0; i < str.length(); i++) {
        if (c == str[i]) return i;
    }
    return -1;
}

void task5_4() {
    ifstream file;

    cout << BLUE_FG << "Enter filename: ";

    string inputBuffer;
    cin >> inputBuffer;
    file.open(inputBuffer);
    while (cin.fail() || !file) {
        cout << RED_FG << "Invalid filename. Try again: ";
        cin.clear();
        cin.ignore(32767, '\n');
        cin >> inputBuffer;
        file.open(inputBuffer);
    }

    string holder;
    string open = {'(', '{', '[', '<'};
    string closed = {')', '}', ']', '>'};

    char c;
    while (file >> c) {
        if (findIndex(open, c) != -1) {
            holder.push_back(c);
        } else {
            int closedIndex = findIndex(closed, c);
            if (closedIndex != -1) {
                char openPair = open[closedIndex];
                if (holder[holder.size() - 1] == openPair) {
                    holder.pop_back();
                } else {
                    holder.push_back(c);
                    break;
                }
            }
        }
    }
    cout << GREEN_FG << (holder.length() == 0 ? "Right brackets sequence!\n" : "Wrong brackets sequence!\n") << RESET;
}

#endif //FIRST_5_4_H
