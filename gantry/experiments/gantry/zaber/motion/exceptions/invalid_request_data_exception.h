// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Used for internal error handling.
             * Indicates passing values of incorrect type from scripting languages or mixed library binary files.
             */
            class InvalidRequestDataException: public MotionLibException {
            public:
                InvalidRequestDataException(const std::string& message);
                virtual ~InvalidRequestDataException() = default;
            protected:
                InvalidRequestDataException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
