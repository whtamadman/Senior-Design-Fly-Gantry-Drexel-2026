// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/command_failed_exception.h"
#include "zaber/motion/dto/exceptions/command_failed_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a parameter of a command is judged to be out of range by the receiving device.
             */
            class BadDataException: public CommandFailedException {
            public:
                BadDataException(const std::string& message, const std::string &customData);
                BadDataException(const std::string& message, const CommandFailedExceptionData &&customData);
                virtual ~BadDataException() = default;
            protected:
                BadDataException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                BadDataException(const MotionLibException::ExceptionInfo& info, const CommandFailedExceptionData &&customData);
            };
        }
    }
}
