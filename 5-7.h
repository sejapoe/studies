//
// Created by sejapoe on 10/30/22.
//
// Организовать файл 1, компонентами которого являются 10 целочисленных одномерных массивов.
// Максимальные и минимальные элементы всех массивов заменить на нули.
// Полученные массивы сохранить в файл 2.
// Каждый массив преобразовать в квадратную матрицу размера 10*10.
// Если количество элементов недостаточно, то добавить их с использованием генератора случайных чисел.
// Результат сохранить в файл 3. Предусмотреть возможность просмотра полученных файлов.

#ifndef FIRST_5_7_H
#define FIRST_5_7_H

#include "colors.h"

void fillWithRandom(int minSize, int maxSize, int minBound, int maxBound) {
    ofstream file("result-5-7_1");
    for (int i = 0; i < 10; i++) {
        int n = random() % (maxSize - minSize) + minSize;
        file << n << "\n";
        for (int j = 0; j < n; j++) {
            file << random() % (maxBound - minBound) + minBound << " ";
        }
        file << "\n";
    }
}

void readTo(int **arr, int *sizes) {
    ifstream file("result-5-7_1");
    for (int i = 0; i < 10; i++) {
        file >> sizes[i];
        arr[i] = new int[sizes[i]];
        for (int j = 0; j < sizes[i]; j++) {
            file >> arr[i][j];
        }
    }
}

void replaceMinAndMaxWithZeros(int *arr, int size) {
    auto curMax = 0, curMin = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > curMax) curMax = arr[i];
        if (arr[i] < curMin) curMin = arr[i];
    }

    for (int i = 0; i < size; i++) {
        if (arr[i] == curMax || arr[i] == curMin) {
            arr[i] = 0;
        }
    }
}

void writeFrom(int **arr, int *sizes) {
    ofstream file("result-5-7_2");
    for (int i = 0; i < 10; i++) {
        file << sizes[i] << "\n";
        for (int j = 0; j < sizes[i]; j++) {
            file << arr[i][j] << " ";
        }
        file << "\n";
    }
}

void convertToMatrix(int matrix[10][10], const int *source, int sourceSize, int randomMinBound, int randomMaxBound) {
    for (int i = 0; i < min(sourceSize, 100); i++) {
        matrix[i / 10][i % 10] = source[i];
    }
    for (int i = sourceSize; i < 100; i++) {
        matrix[i / 10][i % 10] = random() % (randomMaxBound - randomMinBound) + randomMinBound;
    }
}

void writeMatricesFrom(int matrices[10][10][10]) {
    ofstream file("result-5-7_3");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                file << matrices[i][j][k] << " ";
            }
            file << "\n";
        }
        file << "-------------------------\n";
    }
}

void task5_7() {
    fillWithRandom(0, 100, 0, 100);
    auto arr = new int *[10];
    auto sizes = new int[10];
    readTo(arr, sizes);
    for (int i = 0; i < 10; i++) {
        replaceMinAndMaxWithZeros(arr[i], sizes[i]);
    }
    writeFrom(arr, sizes);
    int matrices[10][10][10];
    for (int i = 0; i < 10; i++) {
        convertToMatrix(matrices[i], arr[i], sizes[i], 0, 100);
    }
    writeMatricesFrom(matrices);
    cout << GREEN_FG << "File with arrays filled with random values: "
         << "file://" << canonicalize_file_name("result-5-7_1") << "\n";
    cout << "File with array with replaced minis and maxes: "
         << "file://" << canonicalize_file_name("result-5-7_2") << "\n";
    cout << "File with matrices: "
         << "file://" << canonicalize_file_name("result-5-7_3") << "\n";
}

#endif //FIRST_5_7_H
