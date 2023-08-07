#include <iostream>
#include <string>

using namespace std;

string railFenceEncrypt(const string& plainText, int rails) {
    int len = plainText.length();
    string encryptedText;

    for (int rail = 0; rail < rails; ++rail) {
        for (int i = rail; i < len; i += rails * 2 - 2) {
            encryptedText.push_back(plainText[i]);

            if (rail > 0 && rail < rails - 1) {
                int j = i + (rails - rail - 1) * 2;
                if (j < len)
                    encryptedText.push_back(plainText[j]);
            }
        }
    }

    return encryptedText;
}


int main() {
    string plaintext;
    int rails;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    cout << "Enter the number of rails: ";
    cin >> rails;

    string encryptedText = railFenceEncrypt(plaintext, rails);
    cout << "Encrypted Text: " << encryptedText << endl;

    return 0;
}