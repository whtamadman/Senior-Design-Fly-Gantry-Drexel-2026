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
             * Thrown when a movement command gets preempted by another command.
             */
            class CommandPreemptedException: public MotionLibException {
            public:
                CommandPreemptedException(const std::string& message);
                virtual ~CommandPreemptedException() = default;
            protected:
                CommandPreemptedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
