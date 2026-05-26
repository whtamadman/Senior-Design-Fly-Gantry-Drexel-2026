// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/command_too_long_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a command is too long to be written by the ASCII protocol, even when continued across multiple lines.
             */
            class CommandTooLongException: public MotionLibException {
            public:
                CommandTooLongException(const std::string& message, const std::string &customData);
                CommandTooLongException(const std::string& message, const CommandTooLongExceptionData &&customData);
                virtual ~CommandTooLongException() = default;

                /**
                 * Additional data for CommandTooLongException
                 */
                CommandTooLongExceptionData const & getDetails() const;
            private:
                CommandTooLongExceptionData details;
            protected:
                CommandTooLongException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                CommandTooLongException(const MotionLibException::ExceptionInfo& info, const CommandTooLongExceptionData &&customData);
            };
        }
    }
}
