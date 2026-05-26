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
             * Thrown when a movement command for a GE1 series gripper fails.
             */
            class Ge1GripperMovementFailedException: public MotionLibException {
            public:
                Ge1GripperMovementFailedException(const std::string& message);
                virtual ~Ge1GripperMovementFailedException() = default;
            protected:
                Ge1GripperMovementFailedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
