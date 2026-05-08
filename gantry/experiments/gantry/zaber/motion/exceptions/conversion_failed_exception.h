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
             * Thrown when a value cannot be converted using the provided units.
             */
            class ConversionFailedException: public MotionLibException {
            public:
                ConversionFailedException(const std::string& message);
                virtual ~ConversionFailedException() = default;
            protected:
                ConversionFailedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
