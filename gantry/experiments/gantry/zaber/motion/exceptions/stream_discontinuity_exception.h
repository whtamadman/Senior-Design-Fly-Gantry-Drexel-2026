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
             * Thrown when a stream encounters discontinuity and interrupts the movement.
             */
            class StreamDiscontinuityException: public MotionLibException {
            public:
                StreamDiscontinuityException(const std::string& message);
                virtual ~StreamDiscontinuityException() = default;
            protected:
                StreamDiscontinuityException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
