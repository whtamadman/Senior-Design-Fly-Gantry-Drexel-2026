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
             * Thrown when a PVT sequence generator function fails to find a sequence.
             */
            class PvtSequenceGenerationFailedException: public MotionLibException {
            public:
                PvtSequenceGenerationFailedException(const std::string& message);
                virtual ~PvtSequenceGenerationFailedException() = default;
            protected:
                PvtSequenceGenerationFailedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
