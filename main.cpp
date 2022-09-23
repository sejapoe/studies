#include <iostream>

using namespace std;

class complexNumber {
    double realPart;
    double complexPart;

public:
    explicit complexNumber(double realPart) : realPart(realPart), complexPart(0) {}

    complexNumber(double realPart, double complexPart) : realPart(realPart), complexPart(complexPart) {}

    friend ostream &operator<<(ostream &os, const complexNumber &complex) {
        os << complex.realPart << (complex.complexPart >= 0 ? "+" : "-") << abs(complex.complexPart) << "i";
        return os;
    }

    bool operator==(const complexNumber &rhs) const {
        return realPart == rhs.realPart &&
               complexPart == rhs.complexPart;
    }

    bool operator!=(const complexNumber &rhs) const {
        return !(rhs == *this);
    }

    complexNumber operator+(const complexNumber &rhs) const {
        return {this->realPart + rhs.realPart, this->complexPart + rhs.complexPart};
    }

    complexNumber &operator+=(const complexNumber &rhs) {
        this->realPart += rhs.realPart;
        this->complexPart += rhs.complexPart;
        return *this;
    }

    complexNumber operator-(const complexNumber &rhs) const {
        return {this->realPart - rhs.realPart, this->complexPart - rhs.complexPart};
    }

    complexNumber &operator-=(const complexNumber &rhs) {
        this->realPart -= rhs.realPart;
        this->complexPart -= rhs.complexPart;
        return *this;
    }

    complexNumber operator*(const complexNumber &rhs) const {
        return {this->realPart * rhs.realPart - this->complexPart * rhs.complexPart,
                this->complexPart * rhs.realPart + this->realPart * rhs.complexPart};
    }

    complexNumber &operator*=(const complexNumber &rhs) {
        const double t = this->realPart * rhs.realPart - this->complexPart * rhs.complexPart;
        this->complexPart = this->complexPart * rhs.realPart + this->realPart * rhs.complexPart;
        this->realPart = t;
        return *this;
    }

    complexNumber operator/(const complexNumber &rhs) const {
        const double de = rhs.complexPart * rhs.complexPart + rhs.realPart * rhs.realPart;
        return {(this->realPart * rhs.realPart + this->complexPart * rhs.complexPart) / de,
                ((this->complexPart * rhs.realPart - this->realPart * rhs.complexPart) / de)};
    }

    complexNumber &operator/(const complexNumber &rhs) {
        const double de = rhs.complexPart * rhs.complexPart + rhs.realPart * rhs.realPart;
        const double t = (this->realPart * rhs.realPart + this->complexPart * rhs.complexPart) / de;
        this->complexPart = ((this->complexPart * rhs.realPart - this->realPart * rhs.complexPart) / de);
        this->realPart = t;
        return *this;
    }

    complexNumber operator-() const {
        return {-this->realPart, -this->complexPart};
    }
};

int main() {
    complexNumber a(15, 4);
    complexNumber b(4, -5);
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    cout << a / b << endl;
    b = a;
    a *= a;
    cout << (a == b*b) << endl;
}
