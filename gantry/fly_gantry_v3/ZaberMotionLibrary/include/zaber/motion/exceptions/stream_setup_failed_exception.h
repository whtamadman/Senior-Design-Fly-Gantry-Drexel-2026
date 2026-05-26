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
             * Thrown when setting up a stream fails.
             */
            class StreamSetupFailedException: public MotionLibException {
            public:
                StreamSetupFailedException(const std::string& message);
                virtual ~StreamSetupFailedException() = default;
            protected:
                StreamSetupFailedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
