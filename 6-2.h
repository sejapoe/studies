//
// Created by sejapoe on 10/30/22.
//

#ifndef FIRST_6_2_H
#define FIRST_6_2_H

using namespace std;

string const colors[]  = {
        "цзя",
        "и",
        "бин",
        "дин",
        "у",
        "цзи",
        "гэн",
        "синь",
        "жэнь",
        "гуй",
};

string const colorCodes[] = {
    GREEN_FG,
    RED_FG,
    YELLOW_FG,
    WHITE_FG,
    BLUE_FG
};

string const animals[] =  {
    "цзы",
    "чоу",
    "инь",
    "мао",
    "чэнь",
    "сы",
    "у",
    "вэй",
    "шэнь",
    "ю",
    "сюй",
    "хай"
};

void task6_2() {
    cout << "Enter year: ";

    int year;
    cin >> year;
    while (cin.fail() || year <= 0) {
        cout << RED_FG << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(32767, '\n');
        cin >> year;
    }

    year += 56;
    int color = year % 10;
    int animal = year % 12;
    cout << colorCodes[color / 2] << colors[color] << "-" << animals[animal] << "\n";
}

#endif //FIRST_6_2_H
