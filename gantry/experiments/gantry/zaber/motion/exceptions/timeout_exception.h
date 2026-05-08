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
             * Thrown for various timeouts across the library excluding request to a device (see RequestTimeoutException).
             */
            class TimeoutException: public MotionLibException {
            public:
                TimeoutException(const std::string& message);
                virtual ~TimeoutException() = default;
            protected:
                TimeoutException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
