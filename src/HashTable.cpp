#include "HashTable.hpp"

const long long OFFSET = 257;

const int PRIME[5] = {1610612741, 805306457, 402653189, 201326611, 100663319};

void convertStringToHash(const std::string& st, int hash[5])
{
    for(int i = 0; i < 5; ++i)
        hash[i] = 0;

    for(int i = 0; i < st.size(); ++i)
        for(int j = 0; j < 5; ++j)
            hash[j] = (hash[j] * OFFSET + st[i]) % PRIME[j];
}

bool checkPassword(const std::string& st, const int hash[5])
{
    int hashSt[5];
    convertStringToHash(st, hashSt);
    for(int i = 0; i < 5; ++i)
        if(hashSt[i] != hash[i])
            return false; 
    return true;
}
