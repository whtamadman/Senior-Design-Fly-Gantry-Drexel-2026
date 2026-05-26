// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/stream_movement_failed_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a device registers a fault during streamed movement.
             */
            class StreamMovementFailedException: public MotionLibException {
            public:
                StreamMovementFailedException(const std::string& message, const std::string &customData);
                StreamMovementFailedException(const std::string& message, const StreamMovementFailedExceptionData &&customData);
                virtual ~StreamMovementFailedException() = default;

                /**
                 * Additional data for StreamMovementFailedException
                 */
                StreamMovementFailedExceptionData const & getDetails() const;
            private:
                StreamMovementFailedExceptionData details;
            protected:
                StreamMovementFailedException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                StreamMovementFailedException(const MotionLibException::ExceptionInfo& info, const StreamMovementFailedExceptionData &&customData);
            };
        }
    }
}
