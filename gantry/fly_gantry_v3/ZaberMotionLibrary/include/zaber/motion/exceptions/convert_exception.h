// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include <string>
#include <memory>

#include "zaber/motion/dto/requests/includes.h"

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /* Forward Declarations */
            class MotionLibException;

            void convertException(requests::Errors error, const std::string &message);
            void convertException(requests::Errors error, const std::string &message, const std::string &customData);
            std::shared_ptr<exceptions::MotionLibException> convertExceptionSP(requests::Errors error, const std::string &message);
            std::shared_ptr<exceptions::MotionLibException> convertExceptionSP(requests::Errors error, const std::string &message, const std::string &customData);
        }
    }
}
