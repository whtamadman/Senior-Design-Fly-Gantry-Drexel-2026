#pragma once

#include <string>
#include <vector>

#include "zaber/motion/dto/serializable.h"

namespace zaber {
namespace motion {

class Serializer {
public:
    static std::string serialize(const std::vector<const Serializable*>& messages);
    static std::vector<std::string> deserialize(const std::string& responseBuffer);
    static void populateFromBuffer(const std::string& buffer, Serializable& serializable);
};

} // namespace motion
} // namespace zaber
