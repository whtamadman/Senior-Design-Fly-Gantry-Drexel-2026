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
             * Thrown when an operation cannot be performed because lockstep motion is not enabled.
             */
            class LockstepNotEnabledException: public MotionLibException {
            public:
                LockstepNotEnabledException(const std::string& message);
                virtual ~LockstepNotEnabledException() = default;
            protected:
                LockstepNotEnabledException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
