#include "BlumBlumShub.h"
#include "NistStats.h"
#include "Encryptor.h"

int main() 
{
    cpp_int p = 499;
    cpp_int q = 547;
    std::string message = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    BlumBlumShub bbs(p, q);
    std::cout << "1. Generating bits with BlumBlumShub generator\n";
    auto key = bbs.makeBits(10000);
    std::cout << "Key is ready\n";
    std::cout << "Statistics tests: \n";
    std::cout << "Frequency within block \n";
    if (frequencyWithinBlockTest(key)) std::cout << "P value is lower than 0.01, sequence is random\n";
    else std::cout << "P value is larger than 0.01, sequence is not random\n";
    std::cout << "Monobit test \n";
    if (monobitTest(key)) std::cout << "P value is lower than 0.01, sequence is random\n";
    else std::cout << "P value is larger than 0.01, sequence is not random\n";
    std::cout << "\n2. Encrypting message\n";
    std::cout << "Message: " << message << "\n";
    auto encryptedMessageBits = encryptMessage(textToBits(message), key);
    std::cout << "Message after encryption: " << bitsToText(encryptedMessageBits) << "\n";
    std::cout << "\n3. Decrypting message\n";
    auto decryptedMessageBits = decryptMessage(encryptedMessageBits, key);
    std::cout << "Message after decryption:\n";
    std::cout << bitsToText(decryptedMessageBits);
}