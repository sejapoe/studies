//
// Created by sejapoe on 10/30/22.
//
// Преобразование разделителей: превращение строк в столбцы фраз.

#ifndef FIRST_5_3_H
#define FIRST_5_3_H

#include <iostream>
#include <fstream>
#include "colors.h"

bool isEndOfSentence(const char &c) {
    return c == '.' || c == '!' || c == '?';
}

void task5_3() {
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

    string phraseBuffer;
    cout << GREEN_FG;
    while (getline(file, inputBuffer)) {
        for (const char &c : inputBuffer) {
            if (!isEndOfSentence(c)) {
                if (!phraseBuffer.empty() || c != ' ') phraseBuffer += c;
            } else if (!phraseBuffer.empty()) {
                phraseBuffer += c;
                cout << phraseBuffer << "\n";
                phraseBuffer.clear();
            }
        }

        if (!phraseBuffer.empty()) {
            cout << phraseBuffer << "\n";
            phraseBuffer.clear();
        }
    }
    cout << RESET;
}

#endif //FIRST_5_3_H
