#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

// Initial Permutation Table (IP)
const int initial_permutation[] = {58, 50, 42, 34, 26, 18, 10, 2,
                                   60, 52, 44, 36, 28, 20, 12, 4,
                                   62, 54, 46, 38, 30, 22, 14, 6,
                                   64, 56, 48, 40, 32, 24, 16, 8,
                                   57, 49, 41, 33, 25, 17, 9, 1,
                                   59, 51, 43, 35, 27, 19, 11, 3,
                                   61, 53, 45, 37, 29, 21, 13, 5,
                                   63, 55, 47, 39, 31, 23, 15, 7};

// Initial Permutation Inverse Table (IP^-1)
const int initial_permutation_inverse[] = {40, 8, 48, 16, 56, 24, 64, 32,
                                           39, 7, 47, 15, 55, 23, 63, 31,
                                           38, 6, 46, 14, 54, 22, 62, 30,
                                           37, 5, 45, 13, 53, 21, 61, 29,
                                           36, 4, 44, 12, 52, 20, 60, 28,
                                           35, 3, 43, 11, 51, 19, 59, 27,
                                           34, 2, 42, 10, 50, 18, 58, 26,
                                           33, 1, 41, 9, 49, 17, 57, 25};

// Expansion Permutation Table (E)
const int expansion_permutation[] = {32, 1, 2, 3, 4, 5,
                                     4, 5, 6, 7, 8, 9,
                                     8, 9, 10, 11, 12, 13,
                                     12, 13, 14, 15, 16, 17,
                                     16, 17, 18, 19, 20, 21,
                                     20, 21, 22, 23, 24, 25,
                                     24, 25, 26, 27, 28, 29,
                                     28, 29, 30, 31, 32, 1};

// S-Box Tables
const int sbox[8][4][16] = {
    // S1
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    // S2
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    // S3
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    // S4
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    // S5
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    // S6
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    // S7
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    // S8
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

// Permutation Table (P)
const int permutation[] = {16, 7, 20, 21,
                           29, 12, 28, 17,
                           1, 15, 23, 26,
                           5, 18, 31, 10,
                           2, 8, 24, 14,
                           32, 27, 3, 9,
                           19, 13, 30, 6,
                           22, 11, 4, 25};

// Initial Key Permutation Table (PC-1)
const int initial_key_permutation[] = {57, 49, 41, 33, 25, 17, 9,
                                       1, 58, 50, 42, 34, 26, 18,
                                       10, 2, 59, 51, 43, 35, 27,
                                       19, 11, 3, 60, 52, 44, 36,
                                       63, 55, 47, 39, 31, 23, 15,
                                       7, 62, 54, 46, 38, 30, 22,
                                       14, 6, 61, 53, 45, 37, 29,
                                       21, 13, 5, 28, 20, 12, 4};

// Key Permutation Table (PC-2)
const int key_permutation[] = {14, 17, 11, 24, 1, 5,
                               3, 28, 15, 6, 21, 10,
                               23, 19, 12, 4, 26, 8,
                               16, 7, 27, 20, 13, 2,
                               41, 52, 31, 37, 47, 55,
                               30, 40, 51, 45, 33, 48,
                               44, 49, 39, 56, 34, 53,
                               46, 42, 50, 36, 29, 32};

// Circular Left Shifts for Key Generation
const int key_shifts[] = {1, 1, 2, 2, 2, 2, 2, 2,
                          1, 2, 2, 2, 2, 2, 2, 1};

// Convert an integer to a binary string of a specified length
string intToBinaryString(int num, int length) {
    string binary = "";
    for (int i = length - 1; i >= 0; i--) {
        binary += ((num >> i) & 1) ? "1" : "0";
    }
    return binary;
}

// Convert a binary string to an integer
int binaryStringToInt(const string& binary) {
    int result = 0;
    for (char bit : binary) {
        result = (result << 1) | (bit - '0');
    }
    return result;
}

// Initial permutation (IP)
string initialPermutation(const string& plaintext) {
    string permuted = "";
    for (int i = 0; i < 64; i++) {
        permuted += plaintext[initial_permutation[i] - 1];
    }
    return permuted;
}

// Final permutation (IP^-1)
string finalPermutation(const string& ciphertext) {
    string permuted = "";
    for (int i = 0; i < 64; i++) {
        permuted += ciphertext[initial_permutation_inverse[i] - 1];
    }
    return permuted;
}

// Expansion permutation (E)
string expansionPermutation(const string& right_half) {
    string expanded = "";
    for (int i = 0; i < 48; i++) {
        expanded += right_half[expansion_permutation[i] - 1];
    }
    return expanded;
}

// S-box substitution
string sBoxSubstitution(const string& input) {
    string output = "";
    for (int i = 0; i < 8; i++) {
        int row = binaryStringToInt(input.substr(i * 6, 1) + input.substr(i * 6 + 5, 1));
        int col = binaryStringToInt(input.substr(i * 6 + 1, 4));
        int val = sbox[i][row][col];
        output += intToBinaryString(val, 4);
    }
    return output;
}

// Permutation (P)
string permutationFunction(const string& input) {
    string permuted = "";
    for (int i = 0; i < 32; i++) {
        permuted += input[permutation[i] - 1];
    }
    return permuted;
}

// Perform the Feistel function
string feistelFunction(const string& right_half, const string& round_key) {
    // Expand the right half
    string expanded = expansionPermutation(right_half);
    
    // XOR with round key
    string xored = "";
    for (size_t i = 0; i < expanded.length(); i++) {
        xored += (expanded[i] == round_key[i]) ? '0' : '1';
    }
    
    // S-box substitution
    string substituted = sBoxSubstitution(xored);
    
    // Permutation
    string permuted = permutationFunction(substituted);
    
    return permuted;
}

// Generate round keys from the master key
vector<string> generateRoundKeys(const string& master_key) {
    vector<string> round_keys;
    
    // Perform initial key permutation (PC-1)
    string key_permuted = "";
    for (int i = 0; i < 56; i++) {
        key_permuted += master_key[initial_key_permutation[i] - 1];
    }
    
    // Split the key into left and right halves
    string left_half = key_permuted.substr(0, 28);
    string right_half = key_permuted.substr(28, 28);
    
    for (int round = 0; round < 16; round++) {
        // Perform circular left shift on both halves
        for (int shift = 0; shift < key_shifts[round]; shift++) {
            left_half = left_half.substr(1) + left_half[0];
            right_half = right_half.substr(1) + right_half[0];
        }
        
        // Combine the halves
        string combined_half = left_half + right_half;
        
        // Perform key permutation (PC-2)
        string round_key = "";
        for (int i = 0; i < 48; i++) {
            round_key += combined_half[key_permutation[i] - 1];
        }
        
        round_keys.push_back(round_key);
    }
    
    return round_keys;
}

// Encrypt a 64-bit block of plaintext using DES
string desEncrypt(const string& plaintext, const string& master_key) {
    // Check if the plaintext and master_key are 64 bits each
    if (plaintext.length() != 64 || master_key.length() != 64) {
        return "Input length must be 64 bits.";
    }
    
    // Generate round keys
    vector<string> round_keys = generateRoundKeys(master_key);
    
    // Initial permutation (IP)
    string input_block = initialPermutation(plaintext);
    
    // Split the block into left and right halves
    string left_half = input_block.substr(0, 32);
    string right_half = input_block.substr(32, 32);
    
    for (int round = 0; round < 16; round++) {
        // Save the current right half for the next round
        string temp = right_half;
        
        // Calculate the new right half
        right_half = "";
        for (size_t i = 0; i < 32; i++) {
            right_half += (left_half[i] == feistelFunction(temp, round_keys[round])[i]) ? '0' : '1';
        }
        
        // Set the left half to the previous right half
        left_half = temp;
    }
    
    // Combine the left and right halves
    string combined_block = left_half + right_half;
    
    // Final permutation (IP^-1)
    string ciphertext = finalPermutation(combined_block);
    
    return ciphertext;
}

int main() {
    // Example plaintext and master key (64 bits each)
    string plaintext = "1100101001101010100011001100110010100101010011010010110100101010";
    string master_key = "1111000011001100101010101111010101010110011001111000011001100101";

    // Encrypt the plaintext
    string ciphertext = desEncrypt(plaintext, master_key);

    // Display the ciphertext
    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}