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
             * Thrown when the library cannot perform an operation on a file.
             */
            class IoFailedException: public MotionLibException {
            public:
                IoFailedException(const std::string& message);
                virtual ~IoFailedException() = default;
            protected:
                IoFailedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
