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
             * Thrown when trying to access a key that has not been set.
             */
            class NoValueForKeyException: public MotionLibException {
            public:
                NoValueForKeyException(const std::string& message);
                virtual ~NoValueForKeyException() = default;
            protected:
                NoValueForKeyException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
