#include <iostream>
#include <string>
#include <cstdint>

// Function to perform bitwise left rotation
uint32_t leftRotate(uint32_t value, int shift) {
    return (value << shift) | (value >> (32 - shift));
}

// Function to calculate SHA-1 hash
std::string calculateSHA1(const std::string& input) {
    // Constants for SHA-1
    const uint32_t h0 = 0x67452301;
    const uint32_t h1 = 0xEFCDAB89;
    const uint32_t h2 = 0x98BADCFE;
    const uint32_t h3 = 0x10325476;
    const uint32_t h4 = 0xC3D2E1F0;

    // Pre-processing
    uint64_t totalBits = input.length() * 8;
    input += static_cast<char>(0x80); // Append 1 bit (0x80)

    while ((input.length() * 8) % 512 != 448) {
        input += static_cast<char>(0x00); // Append 0 bits (0x00) until length % 512 == 448
    }

    input.resize((input.length() * 8) + 64, 0); // Append original length as a 64-bit integer

    // Process the message in 512-bit blocks
    for (size_t chunkStart = 0; chunkStart < input.length(); chunkStart += 64) {
        std::vector<uint32_t> w(80, 0);

        // Break chunk into 16 32-bit words
        for (int i = 0; i < 16; i++) {
            w[i] = (static_cast<uint32_t>(input[chunkStart + i * 4]) << 24) |
                   (static_cast<uint32_t>(input[chunkStart + i * 4 + 1]) << 16) |
                   (static_cast<uint32_t>(input[chunkStart + i * 4 + 2]) << 8) |
                   (static_cast<uint32_t>(input[chunkStart + i * 4 + 3]));
        }

        // Extend the 16 32-bit words into 80 32-bit words
        for (int i = 16; i < 80; i++) {
            w[i] = leftRotate(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        }

        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;

        // Main loop
        for (int i = 0; i < 80; i++) {
            uint32_t f, k;
            if (i < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (i < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = leftRotate(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = leftRotate(b, 30);
            b = a;
            a = temp;
        }

        // Update hash values
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    // Concatenate hash values
    uint32_t hashValues[] = {h0, h1, h2, h3, h4};
    std::string hash;
    for (const auto& value : hashValues) {
        for (int i = 24; i >= 0; i -= 8) {
            hash += static_cast<char>((value >> i) & 0xFF);
        }
    }

    return hash;
}

int main() {
    // Input text
    std::string inputText = "Hello, world!";
    
    // Calculate SHA-1 hash
    std::string sha1Hash = calculateSHA1(inputText);

    // Print the SHA-1 hash in hexadecimal format
    for (char c : sha1Hash) {
        printf("%02x", static_cast<uint8_t>(c));
    }
    std::cout << std::endl;

    return 0;
}
