#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

// Function to find the greatest common divisor (GCD) of two numbers using Euclidean algorithm
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Function to generate a random prime number in a given range
int generateRandomPrime(int min, int max) {
    int num;
    do {
        num = rand() % (max - min + 1) + min;
    } while (!isPrime(num));
    return num;
}

// Function to generate public and private keys
void generateRSAKeys(int& publicKey, int& privateKey, int& modulus) {
    srand(time(nullptr));

    // Choose two distinct prime numbers
    int p = generateRandomPrime(2, 100);
    int q = generateRandomPrime(2, 100);

    modulus = p * q;
    int phi = (p - 1) * (q - 1);

    // Choose a public key (usually a small prime number)
    publicKey = generateRandomPrime(2, phi - 1);

    // Calculate the corresponding private key
    privateKey = 0;
    while ((publicKey * privateKey) % phi != 1) {
        privateKey++;
    }
}

// Function to encrypt a message using RSA
int encrypt(int plaintext, int publicKey, int modulus) {
    return static_cast<int>(pow(plaintext, publicKey)) % modulus;
}

// Function to decrypt a message using RSA
int decrypt(int ciphertext, int privateKey, int modulus) {
    return static_cast<int>(pow(ciphertext, privateKey)) % modulus;
}

int main() {
    int publicKey, privateKey, modulus;

    // Generate RSA keys
    generateRSAKeys(publicKey, privateKey, modulus);

    // Message to be encrypted
    int plaintext;
    cout << "Enter a plaintext message (integer): ";
    cin >> plaintext;

    // Encrypt the message
    int ciphertext = encrypt(plaintext, publicKey, modulus);
    cout << "Ciphertext: " << ciphertext << endl;

    // Decrypt the ciphertext
    int decryptedText = decrypt(ciphertext, privateKey, modulus);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
