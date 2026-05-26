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
             * Thrown when no devices can be found on a connection.
             */
            class NoDeviceFoundException: public MotionLibException {
            public:
                NoDeviceFoundException(const std::string& message);
                virtual ~NoDeviceFoundException() = default;
            protected:
                NoDeviceFoundException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
