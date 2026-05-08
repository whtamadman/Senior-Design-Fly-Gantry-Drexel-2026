// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/stream_movement_interrupted_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when ongoing stream movement is interrupted by another command or user input.
             */
            class StreamMovementInterruptedException: public MotionLibException {
            public:
                StreamMovementInterruptedException(const std::string& message, const std::string &customData);
                StreamMovementInterruptedException(const std::string& message, const StreamMovementInterruptedExceptionData &&customData);
                virtual ~StreamMovementInterruptedException() = default;

                /**
                 * Additional data for StreamMovementInterruptedException
                 */
                StreamMovementInterruptedExceptionData const & getDetails() const;
            private:
                StreamMovementInterruptedExceptionData details;
            protected:
                StreamMovementInterruptedException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                StreamMovementInterruptedException(const MotionLibException::ExceptionInfo& info, const StreamMovementInterruptedExceptionData &&customData);
            };
        }
    }
}
