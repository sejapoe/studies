#include <iostream>


using namespace std;

int signx(int x) {
    return x == 0 ? 0 : x / abs(x);
}

int main() {
    cout << "Enter a number: ";
    int t;
    cin >> t;
    cout << "SignX = " << signx(t) << "\n";
}
