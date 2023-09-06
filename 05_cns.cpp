#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to convert a character to its corresponding numerical value (A=0, B=1, ..., Z=25)
int charToNum(char c) {
    return c - 'A';
}

// Function to convert a numerical value to its corresponding character (0=A, 1=B, ..., 25=Z)
char numToChar(int num) {
    return 'A' + num;
}

// Function to perform matrix multiplication
vector<int> matrixMultiply(const vector<vector<int>>& key, const vector<int>& input) {
    int n = key.size();
    vector<int> result(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += key[i][j] * input[j];
        }
        result[i] %= 26; // Perform modulo 26 to keep the result within the range [0, 25]
    }

    return result;
}

// Function to encrypt a plaintext using Hill Cipher
string hillCipherEncrypt(const string& plaintext, const vector<vector<int>>& key) {
    int n = key.size();
    string ciphertext = "";

    for (int i = 0; i < plaintext.length(); i += n) {
        vector<int> input(n, 0);
        vector<int> result(n, 0);

        // Convert a block of characters to numerical values
        for (int j = 0; j < n; j++) {
            input[j] = charToNum(plaintext[i + j]);
        }

        // Perform matrix multiplication
        result = matrixMultiply(key, input);

        // Convert numerical values back to characters and append to ciphertext
        for (int j = 0; j < n; j++) {
            ciphertext += numToChar(result[j]);
        }
    }

    return ciphertext;
}

int main() {
    // Define the key matrix (3x3 matrix for a 3x3 Hill Cipher)
    vector<vector<int>> key = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };

    // Get plaintext input from the user
    string plaintext;
    cout << "Enter the plaintext (letters only, uppercase): ";
    cin >> plaintext;

    // Encrypt the plaintext using Hill Cipher
    string ciphertext = hillCipherEncrypt(plaintext, key);

    // Display the ciphertext
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}
