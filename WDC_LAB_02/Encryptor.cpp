#include "Encryptor.h"

std::vector<uint8_t> textToBits(const std::string& msg)
{
    //std::cout << "\nConverting text to bits\n";
    //std::cout << "Message: " << msg << "\n\n";
    std::vector<uint8_t> bits;
    bits.reserve(msg.size() * 8);
    for (unsigned char ch : msg)
        for (int b = 7; b >= 0; b--)
            bits.push_back((ch >> b) & 1);
    //std::cout << "Message as bits: \n\n";
    //for (auto b : bits) std::cout << int(b);
    std::cout << "\n";
    return bits;
}

std::vector<uint8_t> encryptMessage(const std::vector<uint8_t> m, const std::vector<uint8_t> k)
{
    //std::cout << "\nEncrypting message\n";
    std::vector<uint8_t> encrypted;
    encrypted.reserve(m.size());
    if (k.size() < m.size()) throw std::invalid_argument("Key is too short!");
    for (uint64_t i = 0; i < m.size(); i++)
    {
        encrypted.push_back(m[i] ^ k[i]);
    }
    //std::cout << "Message after encryption in bits: \n\n";
    //for (auto b : encrypted) std::cout << int(b);
    //std::cout << "\n";
    return encrypted;
}

std::vector<uint8_t> decryptMessage(const std::vector<uint8_t> m, const std::vector<uint8_t> k)
{
    //std::cout << "\nDecrypting message\n";
    std::vector<uint8_t> decrypted;
    decrypted.reserve(m.size());
    if (k.size() < m.size()) throw std::invalid_argument("Key is too short!");
    for (uint64_t i = 0; i < m.size(); i++)
    {
        decrypted.push_back(m[i] ^ k[i]);
    }
    //std::cout << "Message after decryption in bits: \n\n";
    //for (auto b : decrypted) std::cout << int(b);
    //std::cout << "\n";
    return decrypted;
}

std::string bitsToText(const std::vector<uint8_t>& bits)
{
    if (bits.empty()) return "";
    if (bits.size() % 8 != 0)
    {
        std::cerr << "Warning: bit vector length is not a multiple of 8, truncating extra bits.\n";
    }
    std::string text;
    text.reserve(bits.size() / 8);
    for (size_t i = 0; i + 7 < bits.size(); i += 8)
    {
        unsigned char value = 0;
        for (int b = 0; b < 8; ++b)
        {
            value <<= 1;
            value |= bits[i + b] & 1;
        }
        text.push_back(static_cast<char>(value));
    }
    //std::cout << text << "\n";
    return text;
}
