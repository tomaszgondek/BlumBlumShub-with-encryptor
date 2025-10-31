#include "BlumBlumShub.h"
#include "NistStats.h"
#include "Encryptor.h"
#include <fstream>
#include <sstream>
int main() 
{
    cpp_int p = 499;
    cpp_int q = 547;
    std::string path;
    std::cout << "Enter path to the message file: ";
    std::getline(std::cin, path);
    std::ifstream file(path);
    if (!file) 
    {
        std::cerr << "Error: could not open file: " << path << "\n";
        return 1;
    }
    std::cout << "\n";
    std::ostringstream buffer;
    buffer << file.rdbuf();          
    std::string message = buffer.str();
    file.close();
    BlumBlumShub bbs(p, q);
    std::cout << "1.\n Generating bits with BlumBlumShub generator\n";
    auto key = bbs.makeBits(10000);
    std::cout << "Key is ready\n";
    std::cout << "Statistics tests: \n";
    std::cout << "Frequency within block \n";
    if (frequencyWithinBlockTest(key)) std::cout << "P value is lower than 0.01, sequence is random\n";
    else std::cout << "P value is larger than 0.01, sequence is not random\n";
    std::cout << "Monobit test \n";
    if (monobitTest(key)) std::cout << "P value is lower than 0.01, sequence is random\n";
    else std::cout << "P value is larger than 0.01, sequence is not random\n";
    std::cout << "\n2.\n Encrypting message\n";
    std::cout << "Message: " << message << "\n";
    auto encryptedMessageBits = encryptMessage(textToBits(message), key);
    std::cout << "Message after encryption: " << bitsToText(encryptedMessageBits) << "\n";
    std::cout << "\n3.\n Decrypting message\n";
    auto decryptedMessageBits = decryptMessage(encryptedMessageBits, key);
    std::cout << "Message after decryption:\n";
    std::cout << bitsToText(decryptedMessageBits);
    std::string outPath;
    std::cout << "\nEnter path to save encrypted message: ";
    std::getline(std::cin, outPath);
    std::ofstream outFile(outPath);
    if (!outFile) 
    {
        std::cerr << "Error: could not create file: " << outPath << "\n";
        return 1;
    }
    outFile << "=== BlumBlumShub Encrypted Output ===\n";
    for (size_t i = 0; i < key.size(); i++)
        outFile << int(key[i]);
    outFile << "\n\n";
    outFile << "Encrypted message:\n";
    outFile << bitsToText(encryptedMessageBits) << "\n";
    outFile.close();
    std::cout << "Encrypted message and key saved to: " << outPath << "\n";

}