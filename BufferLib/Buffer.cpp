#include "pch.h"
#include "Buffer.h"
#include <cstring>  // For memcpy

// Constructor
Buffer::Buffer(size_t initialSize)
    : data(initialSize), writeIndex(0), readIndex(0)
{
}

// Serialize unsigned int (32-bit)
void Buffer::Serialize(unsigned int value)
{
    if (writeIndex + sizeof(value) > data.size())
    {
        Grow(data.size() * 2);
    }
    std::memcpy(&data[writeIndex], &value, sizeof(value));
    writeIndex += sizeof(value);
}

// Serialize unsigned short (16-bit)
void Buffer::Serialize(unsigned short value)
{
    if (writeIndex + sizeof(value) > data.size())
    {
        Grow(data.size() * 2);
    }
    std::memcpy(&data[writeIndex], &value, sizeof(value));
    writeIndex += sizeof(value);
}

// Serialize string
void Buffer::Serialize(const std::string& value)
{
    unsigned int length = static_cast<unsigned int>(value.size());
    Serialize(length); // First, write the length of the string
    if (writeIndex + length > data.size())
    {
        Grow(data.size() * 2);
    }
    std::memcpy(&data[writeIndex], value.data(), length);
    writeIndex += length;
}

// Deserialize unsigned int (32-bit)
unsigned int Buffer::DeserializeUInt()
{
    unsigned int value;
    std::memcpy(&value, &data[readIndex], sizeof(value));
    readIndex += sizeof(value);
    return value;
}

// Deserialize unsigned short (16-bit)
unsigned short Buffer::DeserializeUShort()
{
    unsigned short value;
    std::memcpy(&value, &data[readIndex], sizeof(value));
    readIndex += sizeof(value);
    return value;
}

// Deserialize string
std::string Buffer::DeserializeString()
{
    unsigned int length = DeserializeUInt(); // Get the length of the string
    std::string value(&data[readIndex], length);
    readIndex += length;
    return value;
}

// Reset buffer
void Buffer::Reset()
{
    writeIndex = 0;
    readIndex = 0;
}

// Grow the buffer
void Buffer::Grow(size_t newSize)
{
    data.resize(newSize);
}
