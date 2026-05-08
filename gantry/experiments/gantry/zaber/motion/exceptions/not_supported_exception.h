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
             * Thrown when a device does not support a requested command or setting.
             */
            class NotSupportedException: public MotionLibException {
            public:
                NotSupportedException(const std::string& message);
                virtual ~NotSupportedException() = default;
            protected:
                NotSupportedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
