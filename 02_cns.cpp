#include <iostream>
#include <cstring>
using namespace std;

int main() {
    const char* str = "Hello World";
    int len = strlen(str);

    cout << "XOR Operatin" << endl;
    for (int i = 0; i < len; i++) {
        char result = str[i] ^ 127;
        cout << result;
    }
    cout << endl;

    cout << "AND Operatin" << endl;
    for (int i = 0; i < len; i++) {
        char result = str[i] & 127;
        cout << result;
    }
    cout << endl;

    cout << "OR Operatin" << endl;
    for (int i = 0; i < len; i++) {
        char result = str[i] | 127;
        cout << result;
    }

    return 0;
}