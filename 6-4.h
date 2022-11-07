//
// Created by sejapoe on 11/3/22.
//

#ifndef FIRST_6_4_H
#define FIRST_6_4_H

void task6_4() {
    string s;
    string res;
    while (cin >> s) {
        res += s + " ";
    }
    if (!res.empty()) res.erase(res.end() - 1);
    cout << res;
}

#endif //FIRST_6_4_H
