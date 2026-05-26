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
             * Thrown when a device does not respond to a request in time.
             */
            class RequestTimeoutException: public MotionLibException {
            public:
                RequestTimeoutException(const std::string& message);
                virtual ~RequestTimeoutException() = default;
            protected:
                RequestTimeoutException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
