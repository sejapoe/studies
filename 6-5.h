//
// Created by sejapoe on 11/7/22.
//

#ifndef FIRST_6_5_H
#define FIRST_6_5_H

#include <iostream>
#include "colors.h"

using namespace std;

class ComplexNumber {
    double realPart;
    double imaginaryPart;

public:
    ComplexNumber(double realPart) : realPart(realPart), imaginaryPart(0) {} // NOLINT(google-explicit-constructor)

    ComplexNumber(double realPart, double complexPart) : realPart(realPart), imaginaryPart(complexPart) {}

    friend std::ostream &operator<<(std::ostream &os, const ComplexNumber &complex) {
        os << complex.realPart << (complex.imaginaryPart >= 0 ? "+" : "-") << std::abs(complex.imaginaryPart) << "i";
        return os;
    }

    bool operator==(const ComplexNumber &rhs) const {
        return realPart == rhs.realPart &&
               imaginaryPart == rhs.imaginaryPart;
    }

    bool operator!=(const ComplexNumber &rhs) const {
        return !(rhs == *this);
    }

    ComplexNumber operator+(const ComplexNumber &rhs) const {
        return {this->realPart + rhs.realPart, this->imaginaryPart + rhs.imaginaryPart};
    }

    ComplexNumber &operator+=(const ComplexNumber &rhs) {
        this->realPart += rhs.realPart;
        this->imaginaryPart += rhs.imaginaryPart;
        return *this;
    }

    ComplexNumber operator-(const ComplexNumber &rhs) const {
        return {this->realPart - rhs.realPart, this->imaginaryPart - rhs.imaginaryPart};
    }

    ComplexNumber &operator-=(const ComplexNumber &rhs) {
        this->realPart -= rhs.realPart;
        this->imaginaryPart -= rhs.imaginaryPart;
        return *this;
    }

    ComplexNumber operator*(const ComplexNumber &rhs) const {
        return {this->realPart * rhs.realPart - this->imaginaryPart * rhs.imaginaryPart,
                this->imaginaryPart * rhs.realPart + this->realPart * rhs.imaginaryPart};
    }

    ComplexNumber &operator*=(const ComplexNumber &rhs) {
        const double t = this->realPart * rhs.realPart - this->imaginaryPart * rhs.imaginaryPart;
        this->imaginaryPart = this->imaginaryPart * rhs.realPart + this->realPart * rhs.imaginaryPart;
        this->realPart = t;
        return *this;
    }

    ComplexNumber operator/(const ComplexNumber &rhs) const {
        const double de = rhs.imaginaryPart * rhs.imaginaryPart + rhs.realPart * rhs.realPart;
        return {(this->realPart * rhs.realPart + this->imaginaryPart * rhs.imaginaryPart) / de,
                ((this->imaginaryPart * rhs.realPart - this->realPart * rhs.imaginaryPart) / de)};
    }

    ComplexNumber &operator/=(const ComplexNumber &rhs) {
        const double de = rhs.imaginaryPart * rhs.imaginaryPart + rhs.realPart * rhs.realPart;
        const double t = (this->realPart * rhs.realPart + this->imaginaryPart * rhs.imaginaryPart) / de;
        this->imaginaryPart = ((this->imaginaryPart * rhs.realPart - this->realPart * rhs.imaginaryPart) / de);
        this->realPart = t;
        return *this;
    }

    ComplexNumber operator-() const {
        return {-this->realPart, -this->imaginaryPart};
    }
};

double enterDouble() {
    double t;
    cin >> t;
    while (cin.fail()) {
        cout << RED_FG << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(32767, '\n');
        cin >> t;
    }
    return t;
}

void task6_5() {
    cout << BLUE_FG << "Enter real part of u: " << RESET;
    double u1 = enterDouble();
    cout << BLUE_FG << "Enter imaginary part of u: " << RESET;
    double u2 = enterDouble();
    ComplexNumber u(u1, u2);

    cout << BLUE_FG << "Enter real part of v: " << RESET;
    double v1 = enterDouble();
    cout << BLUE_FG << "Enter imaginary part of v: " << RESET;
    double v2 = enterDouble();
    ComplexNumber v(v1, v2);

    cout << BLUE_FG << "Enter real part of w: " << RESET;
    double w1 = enterDouble();
    cout << BLUE_FG << "Enter imaginary part of w: " << RESET;
    double w2 = enterDouble();
    ComplexNumber w(w1, w2);

    ComplexNumber result =
            u * 2.0 + (u * w * 3.0) / (w + v + 2.0) - 7.0;
    cout << GREEN_FG << "Result is " << result << RESET << "\n";
}

#endif //FIRST_6_5_H
