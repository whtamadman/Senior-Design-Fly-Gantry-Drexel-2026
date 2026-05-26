// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/binary_command_failed_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a device rejects a binary command with an error.
             */
            class BinaryCommandFailedException: public MotionLibException {
            public:
                BinaryCommandFailedException(const std::string& message, const std::string &customData);
                BinaryCommandFailedException(const std::string& message, const BinaryCommandFailedExceptionData &&customData);
                virtual ~BinaryCommandFailedException() = default;

                /**
                 * Additional data for BinaryCommandFailedException
                 */
                BinaryCommandFailedExceptionData const & getDetails() const;
            private:
                BinaryCommandFailedExceptionData details;
            protected:
                BinaryCommandFailedException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                BinaryCommandFailedException(const MotionLibException::ExceptionInfo& info, const BinaryCommandFailedExceptionData &&customData);
            };
        }
    }
}
