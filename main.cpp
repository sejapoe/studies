#include <iostream>
#include <map>
#include "5-1.h"
#include "5-2.h"
#include "5-3.h"
#include "5-4.h"
#include "5-5.h"
#include "5-6.h"
#include "5-7.h"

using namespace std;

int main() {
    map<string, void (*)()> functions{
            { "5-1", task5_1 },
            { "5-2", task5_2 },
            { "5-3", task5_3 },
            { "5-4", task5_4 },
            { "5-5", task5_5 },
            { "5-6", task5_6 },
            { "5-7", task5_7 }
    };
    cout << BLUE_FG_BOLD;
    while (true) {
        cout << "Enter task number (e.g. 5-1): ";

        string s;
        cin >> s;
        while (cin.fail() || functions.find(s) == functions.end()) {
            cout << RED_FG_BOLD << "Invalid task. Try again: ";
            cin.clear();
            cin.ignore(32767, '\n');
            cin >> s;
        }

        auto it = functions.find(s);

        char c = 'r';
        while (c == 'r') {
            cout << RESET;
            it->second();
            cout << BLUE_FG_BOLD;
            cout << "[e]xit, [r]estart or [c]ontinue (default)? ";
            cin >> c;
            cin.ignore(32767, '\n');
        }

        if (c == 'e') break;
    }
    cout << "Good bye!";
}
