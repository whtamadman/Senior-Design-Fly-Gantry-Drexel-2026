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
             * Thrown when a PVT sequence encounters discontinuity and interrupts the sequence.
             */
            class PvtDiscontinuityException: public MotionLibException {
            public:
                PvtDiscontinuityException(const std::string& message);
                virtual ~PvtDiscontinuityException() = default;
            protected:
                PvtDiscontinuityException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
