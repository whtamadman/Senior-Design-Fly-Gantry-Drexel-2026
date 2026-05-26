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
             * Thrown when setting up a PVT sequence fails.
             */
            class PvtSetupFailedException: public MotionLibException {
            public:
                PvtSetupFailedException(const std::string& message);
                virtual ~PvtSetupFailedException() = default;
            protected:
                PvtSetupFailedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
