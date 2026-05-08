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
             * Thrown when a device is unable to park.
             */
            class InvalidParkStateException: public MotionLibException {
            public:
                InvalidParkStateException(const std::string& message);
                virtual ~InvalidParkStateException() = default;
            protected:
                InvalidParkStateException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
