// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/command_failed_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a device rejects a command.
             */
            class CommandFailedException: public MotionLibException {
            public:
                CommandFailedException(const std::string& message, const std::string &customData);
                CommandFailedException(const std::string& message, const CommandFailedExceptionData &&customData);
                virtual ~CommandFailedException() = default;

                /**
                 * Additional data for CommandFailedException
                 */
                CommandFailedExceptionData const & getDetails() const;
            private:
                CommandFailedExceptionData details;
            protected:
                CommandFailedException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                CommandFailedException(const MotionLibException::ExceptionInfo& info, const CommandFailedExceptionData &&customData);
            };
        }
    }
}
