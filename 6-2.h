//
// Created by sejapoe on 10/30/22.
//
// В восточном календаре принят 60-летний цикл, состоящий из 12-летних подциклов,
// обозначаемых названиями цвета: зеленый, красный, желтый, белый и черный. В каждом
// подцикле годы носят названия животных: крысы, коровы, тигра, зайца, дракона, змеи,
// лошади, овцы, обезьяны, курицы, собаки и свиньи.
// По номеру года вывести его название, если 1984 год был началом цикла — годом зеленой крысы.

#ifndef FIRST_6_2_H
#define FIRST_6_2_H

using namespace std;

string const colors[] = {
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

string const animals[] = {
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
    cout << GREEN_FG << "Enter year: " << RESET;

    int year = enter(isPositive);

    year += 56;
    int color = year % 10;
    int animal = year % 12;
    cout << colorCodes[color / 2] << colors[color] << "-" << animals[animal] << "\n";
}

#endif //FIRST_6_2_H
