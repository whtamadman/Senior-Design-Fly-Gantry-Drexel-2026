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
             * Thrown when an operation cannot be performed because lockstep motion is enabled.
             */
            class LockstepEnabledException: public MotionLibException {
            public:
                LockstepEnabledException(const std::string& message);
                virtual ~LockstepEnabledException() = default;
            protected:
                LockstepEnabledException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
