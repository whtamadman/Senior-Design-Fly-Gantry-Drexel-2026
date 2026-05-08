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
             * Thrown when a device receives an invalid command.
             */
            class BadCommandException: public CommandFailedException {
            public:
                BadCommandException(const std::string& message, const std::string &customData);
                BadCommandException(const std::string& message, const CommandFailedExceptionData &&customData);
                virtual ~BadCommandException() = default;
            protected:
                BadCommandException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                BadCommandException(const MotionLibException::ExceptionInfo& info, const CommandFailedExceptionData &&customData);
            };
        }
    }
}
