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
             * Thrown when a device cannot carry out a movement command because the motor driver is disabled.
             */
            class DriverDisabledException: public CommandFailedException {
            public:
                DriverDisabledException(const std::string& message, const std::string &customData);
                DriverDisabledException(const std::string& message, const CommandFailedExceptionData &&customData);
                virtual ~DriverDisabledException() = default;
            protected:
                DriverDisabledException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                DriverDisabledException(const MotionLibException::ExceptionInfo& info, const CommandFailedExceptionData &&customData);
            };
        }
    }
}
