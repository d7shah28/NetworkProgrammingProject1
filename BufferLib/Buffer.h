#pragma once
#include "pch.h"
#include "framework.h"
#include <string>
#include <vector>

class Buffer
{
public:
    // Constructor
    Buffer(size_t initialSize = 1024);

    // Serialize methods
    void Serialize(unsigned int value);
    void Serialize(unsigned short value);
    void Serialize(const std::string& value);

    // Deserialize methods
    unsigned int DeserializeUInt();
    unsigned short DeserializeUShort();
    std::string DeserializeString();

    // Reset buffer
    void Reset();

private:
    void Grow(size_t newSize);

    std::vector<char> data;
    size_t writeIndex;
    size_t readIndex;
};

