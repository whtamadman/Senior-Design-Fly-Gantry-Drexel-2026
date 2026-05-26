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
             * Thrown when an operation is not supported by a mode the stream is currently set up in.
             */
            class StreamModeException: public MotionLibException {
            public:
                StreamModeException(const std::string& message);
                virtual ~StreamModeException() = default;
            protected:
                StreamModeException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
