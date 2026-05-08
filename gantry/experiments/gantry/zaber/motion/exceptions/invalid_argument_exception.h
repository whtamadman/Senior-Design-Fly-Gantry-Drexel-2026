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
             * Thrown when a function is called with invalid values.
             */
            class InvalidArgumentException: public MotionLibException {
            public:
                InvalidArgumentException(const std::string& message);
                virtual ~InvalidArgumentException() = default;
            protected:
                InvalidArgumentException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
