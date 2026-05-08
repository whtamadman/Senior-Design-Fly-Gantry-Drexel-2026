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
             * Thrown when an operation is not supported by a mode the PVT sequence is currently set up in.
             */
            class PvtModeException: public MotionLibException {
            public:
                PvtModeException(const std::string& message);
                virtual ~PvtModeException() = default;
            protected:
                PvtModeException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
