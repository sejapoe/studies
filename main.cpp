#include <iostream>


using namespace std;

int sign(int x) {
    return x == 0 ? 0 : x / abs(x);
}

int main() {
    cout << "Enter a number: ";
    int t;
    cin >> t;
    cout << "Sign(x) = " << sign(t) << "\n";
}
