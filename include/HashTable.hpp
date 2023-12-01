#pragma once

#include <string>

void convertStringToHash(const std::string& st, int hash[5]);

bool checkPassword(const std::string& st, const int hash[5]);