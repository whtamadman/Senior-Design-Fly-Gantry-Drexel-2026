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
             * Thrown when operation cannot be performed at given time or context.
             */
            class InvalidOperationException: public MotionLibException {
            public:
                InvalidOperationException(const std::string& message);
                virtual ~InvalidOperationException() = default;
            protected:
                InvalidOperationException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
