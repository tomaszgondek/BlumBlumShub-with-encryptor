#include "BlumBlumShub.h"
#include "NistStats.h"
#include "Encryptor.h"
#include <fstream>
#include <sstream>
int main() 
{
    cpp_int p("91777237090291353103989894182185945674257000143945633478631741458952691840031438763154345784481010888003008833208980426431265478111827053121753567075866788790583972287892135096866625241368941502637826296339133850089972171595470272552783581782636830770605126507159065272854466161640254904752074945652530746983");
    cpp_int q("153345449593756101827622485891574961545180946420557464261495245607567632005526380071055108122229387034936937856376565767814969199001789595780567448347730118700043815773987857360793291228359669929856174933407917162754123320813180202591112098603849743469699340719988055991864553268426994169715792761335584273703");
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
    auto key = bbs.makeBits(message.length()*8);
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
    outFile << "=== KEY ===\n";
    for (size_t i = 0; i < key.size(); i++)
        outFile << int(key[i]);
    outFile << "\n=== END ===";
    outFile << "\n\n";
    outFile << "Encrypted message:\n";
    outFile << "=== Bits ===\n";
    for (size_t i = 0; i < encryptedMessageBits.size(); i++)
        outFile << int(encryptedMessageBits[i]);
    outFile << "\n=== END ===\n\n";
    outFile << "Encrypted message in text:\n";
    outFile << bitsToText(encryptedMessageBits) << "\n";
    outFile.close();
    std::cout << "Encrypted message and key saved to: " << outPath << "\n";
}