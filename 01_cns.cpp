#include <iostream>
#include <cstring>
using namespace std;

int main() {
    const char* str = "Hello World";
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        char result = str[i] ^ 0;
        cout << result;
    }

    cout << endl;
    return 0;
}
