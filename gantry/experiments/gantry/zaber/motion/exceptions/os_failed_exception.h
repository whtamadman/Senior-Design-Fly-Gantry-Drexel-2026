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
             * Thrown when an operation fails due to underlying operating system error.
             */
            class OsFailedException: public MotionLibException {
            public:
                OsFailedException(const std::string& message);
                virtual ~OsFailedException() = default;
            protected:
                OsFailedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
