//
// Created by sejapoe on 11/3/22.
//
// 131. Сократить число пробелов, разделяющих слова в строке до одного

#ifndef FIRST_6_4_H
#define FIRST_6_4_H

void task6_4() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    string res;
    string s;
    while (ss >> s) {
        res += s + " ";
    }
    if (!res.empty()) res.erase(res.end() - 1);
    cout << GREEN_FG << res << RESET << "\n";
}

#endif //FIRST_6_4_H
