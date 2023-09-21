#include <iostream>
#include <vector>
using namespace std;

string encrypt(string plaintext, vector<vector<int>> keyMatrix) {
    int n = keyMatrix.size();
    string ciphertext = "";

    for (int i = 0; i < plaintext.length(); i += n) {
        vector<int> block(n, 0);
        for (int j = 0; j < n; j++) {
            block[j] = plaintext[i + j] - 'A';
        }
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += keyMatrix[j][k] * block[k];
            }
            ciphertext += (sum % 26) + 'A';
        }
    }
    return ciphertext;
}

int main() {
    vector<vector<int>> keyMatrix = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };
    string plaintext = "HELLO FROM HILLCIPHER";
    cout << "Plaintext: " << plaintext << endl;
    string ciphertext = encrypt(plaintext, keyMatrix);
    cout << "Encrypted text: " << ciphertext << endl;
    return 0;
}