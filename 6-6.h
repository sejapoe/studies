//
// Created by sejapoe on 11/8/22.
//

#ifndef FIRST_6_6_H
#define FIRST_6_6_H

using namespace std;

int const M = 2;
int const N = 5;
int const a = -3;
int const b = 6;

int enterInt() {
    int t;
    cin >> t;
    while (cin.fail()) {
        cout << RED_FG << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(32767, '\n');
        cin >> t;
    }
    return t;
}

void printMatrix(int **arr) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}

void task6_6() {
    int **A = new int *[M];
    int **B = new int *[M];
    int **C = new int *[M];
    int **D = new int *[M];
    int **E = new int *[M];
    for (int i = 0; i < M; ++i) {
        A[i] = new int[N];
        B[i] = new int[N];
        C[i] = new int[N];
        D[i] = new int[N];
        E[i] = new int[N];
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << BLUE_FG << "Enter A[" << i << "][" << j << "]: " << RESET;
            A[i][j] = enterInt();
            B[i][j] = i * j - (5 - i - j);
            C[i][j] = std::rand() % (b - a) + a; // NOLINT(cert-msc50-cpp)
            E[i][j] = 1;
            D[i][j] = 6 * E[i][j] - C[i][j] - 2 * B[i][j] - 3 * A[i][j];
        }
    }

    cout << GREEN_FG << BOLD << "Matrix A" << RESET << GREEN_FG << "\n";
    printMatrix(A);
    cout << GREEN_FG << BOLD << "Matrix B" << RESET << GREEN_FG << "\n";
    printMatrix(B);
    cout << GREEN_FG << BOLD << "Matrix C" << RESET << GREEN_FG << "\n";
    printMatrix(C);
    cout << GREEN_FG << BOLD << "Matrix D" << RESET << GREEN_FG << "\n";
    printMatrix(D);
    cout << GREEN_FG << BOLD << "Matrix E" << RESET << GREEN_FG << "\n";
    printMatrix(E);
}

#endif //FIRST_6_6_H
