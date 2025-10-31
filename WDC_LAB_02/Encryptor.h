#pragma once
#include <iostream>
#include <vector>
#include "BlumBlumShub.h"

std::vector<uint8_t> textToBits(const std::string& msg);
std::vector<uint8_t> encryptMessage(const std::vector<uint8_t> m, const std::vector<uint8_t> k);
std::string bitsToText(const std::vector<uint8_t>& bits);
std::vector<uint8_t> decryptMessage(const std::vector<uint8_t> m, const std::vector<uint8_t> k);
