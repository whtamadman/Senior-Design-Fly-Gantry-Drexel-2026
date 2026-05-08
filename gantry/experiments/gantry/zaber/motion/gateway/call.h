#pragma once

#include <string>

#include "zaber/motion/dto/serializable.h"

namespace zaber
{
    namespace motion
    {
        void callGateway(const std::string& request, Serializable& requestData, Serializable* response);
        void callGateway(const std::string& request, Serializable* response);
        void callGateway(const std::string& request, Serializable& requestData);
        void callGateway(const std::string& request);
    }
}
