#include <iostream>
#include "Buffer.h"

int main()
{
    Buffer buffer;

    // Test serialization
    buffer.Serialize(42u);                   // Serialize an unsigned int
    buffer.Serialize(static_cast<unsigned short>(300)); // Serialize an unsigned short
    buffer.Serialize("Hello, Buffer!");     // Serialize a string

    // Reset read index
    buffer.Reset();

    // Test deserialization
    unsigned int val1 = buffer.DeserializeUInt();
    unsigned short val2 = buffer.DeserializeUShort();
    std::string str = buffer.DeserializeString();

    // Output the results
    std::cout << "Deserialized unsigned int: " << val1 << std::endl;
    std::cout << "Deserialized unsigned short: " << val2 << std::endl;
    std::cout << "Deserialized string: " << str << std::endl;

    return 0;
}
