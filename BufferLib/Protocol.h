#pragma once
#include "Buffer.h"

class Protocol
{
public:
    // Method to pack a message into a buffer (adds length prefix)
    static void PackMessage(Buffer& buffer, const std::string& message);

    // Method to unpack a message from a buffer (reads length prefix)
    static std::string UnpackMessage(Buffer& buffer);
};

