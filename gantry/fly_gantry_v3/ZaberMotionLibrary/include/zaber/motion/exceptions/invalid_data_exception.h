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
             * Thrown when incoming device data cannot be parsed as expected.
             */
            class InvalidDataException: public MotionLibException {
            public:
                InvalidDataException(const std::string& message);
                virtual ~InvalidDataException() = default;
            protected:
                InvalidDataException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
