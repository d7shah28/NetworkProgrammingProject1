#include "pch.h"
#include <iostream>
#include "Buffer.h"
#include "Protocol.h"

int main()
{
    // Create a buffer for the test
    Buffer buffer;

    // Original message
    std::string message = "Hello, Protocol!";

    // Pack the message into the buffer
    Protocol::PackMessage(buffer, message);

    // Reset the buffer's read index for unpacking
    buffer.Reset();

    // Unpack the message from the buffer
    std::string unpackedMessage = Protocol::UnpackMessage(buffer);

    // Output the result
    std::cout << "Original message: " << message << std::endl;
    std::cout << "Unpacked message: " << unpackedMessage << std::endl;

    return 0;
}
