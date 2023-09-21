// Implement the Diffie-Hellman Key Exchange mechanism using CPP.Consider 
// the end user as one of 21-22 the parties (Alice) and the CPP application as other party (bob).

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Function to check if a number is prime
bool isPrime(long long num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;

    for (long long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }

    return true;
}

// Function to calculate modular exponentiation (x^y mod m)
long long modExp(long long x, long long y, long long m) {
    if (y == 0) return 1;
    long long temp = modExp(x, y / 2, m);
    long long result = (temp * temp) % m;
    if (y % 2 == 1) result = (result * x) % m;
    return result;
}

// Function to generate a random prime number between min and max
long long generateRandomPrime(long long min, long long max) {
    long long num;
    do {
        num = rand() % (max - min + 1) + min;
    } while (!isPrime(num));
    return num;
}

int main() {
    srand(time(nullptr));

    // Commonly agreed upon prime modulus and base
    long long primeModulus = generateRandomPrime(100, 500);
    long long base = 2; // A common choice for the base

    // Alice's private key and public key calculation
    long long alicePrivateKey = generateRandomPrime(2, primeModulus - 2); // Random private key for Alice
    long long alicePublicKey = modExp(base, alicePrivateKey, primeModulus); // Alice's public key

    // Bob's private key and public key calculation
    long long bobPrivateKey = generateRandomPrime(2, primeModulus - 2); // Random private key for Bob
    long long bobPublicKey = modExp(base, bobPrivateKey, primeModulus); // Bob's public key

    // Key exchange
    long long sharedSecretAlice = modExp(bobPublicKey, alicePrivateKey, primeModulus);
    long long sharedSecretBob = modExp(alicePublicKey, bobPrivateKey, primeModulus);

    // Both Alice and Bob should now have the same shared secret
    std::cout << "Alice's Private Key: " << alicePrivateKey << std::endl;
    std::cout << "Alice's Public Key: " << alicePublicKey << std::endl;
    std::cout << "Bob's Private Key: " << bobPrivateKey << std::endl;
    std::cout << "Bob's Public Key: " << bobPublicKey << std::endl;
    std::cout << "Shared Secret (Alice): " << sharedSecretAlice << std::endl;
    std::cout << "Shared Secret (Bob): " << sharedSecretBob << std::endl;

    return 0;
}
