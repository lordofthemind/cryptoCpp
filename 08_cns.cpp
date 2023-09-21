#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

int main() {
    int p, g, a, A, b, B, message, k, c1, c2, decryptedMessage;

    std::cout << "Enter p: ";
    std::cin >> p;
    std::cout << "Enter g (less than p): ";
    std::cin >> g;
    std::cout << "Enter Alice's private key (a): ";
    std::cin >> a;
    A = static_cast<int>(pow(g, a)) % p;
    std::cout << "Enter Bob's private key (b): ";
    std::cin >> b;
    B = static_cast<int>(pow(g, b)) % p;
    std::cout << "Enter the message (integer): ";
    std::cin >> message;

    srand(time(NULL));
    k = rand() % (p - 2) + 1;
    c1 = static_cast<int>(pow(g, k)) % p;
    c2 = (message * static_cast<int>(pow(A, k))) % p;

    // Calculate the modular inverse
    int inverse = modInverse(static_cast<int>(pow(c1, b)), p);
    if (inverse == -1) {
        std::cout << "Inverse doesn't exist" << std::endl;
        return 1;
    }

    decryptedMessage = (c2 * inverse) % p;

    std::cout << "Alice's public key (A): " << A << std::endl;
    std::cout << "Bob's public key (B): " << B << std::endl;
    std::cout << "Encrypted Message (c1, c2): (" << c1 << ", " << c2 << ")" << std::endl;
    std::cout << "Decrypted Message: " << decryptedMessage << std::endl;

    return 0;
}
