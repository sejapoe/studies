//
// Created by sejapoe on 10/30/22.
//
// Шарики

#ifndef FIRST_6_1_H
#define FIRST_6_1_H

bool check(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == i) return true;
    }
    return false;
}

void permute(int *arr, int n, int level, int &count) {
    if (level == n) {
        if (check(arr, n)) {
            ++count;
        }
        return;
    }
    for (int i = level; i < n; ++i) {
        swap(arr[level], arr[i]);
        permute(arr, n, level + 1, count);
        swap(arr[level], arr[i]);
    }
}

void task6_1() {
    cout << BLUE_FG << "Enter N: ";
    int n = enter(static_cast<function<bool(int)>>([](int t) {
        return t > 0 && t < 13;
    }));

    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    int count = 0;
    permute(arr, n, 0, count);

    cout << GREEN_FG << "Result: " << count << "\n" << RESET;
}
/*
1 2 3 4
1 2 4 3
1 4 2 3
1 4 3 2
4 1 3 2
4 3 1 2
4 3 2 1


 */

#endif //FIRST_6_1_H
