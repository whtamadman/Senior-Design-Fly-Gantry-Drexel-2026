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
             * Thrown when a device IO operation cannot be performed because the provided channel is not valid.
             */
            class IoChannelOutOfRangeException: public MotionLibException {
            public:
                IoChannelOutOfRangeException(const std::string& message);
                virtual ~IoChannelOutOfRangeException() = default;
            protected:
                IoChannelOutOfRangeException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
