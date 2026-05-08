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
             * Thrown when a device registers fatal failure.
             * Contact support if you observe this exception.
             */
            class DeviceFailedException: public MotionLibException {
            public:
                DeviceFailedException(const std::string& message);
                virtual ~DeviceFailedException() = default;
            protected:
                DeviceFailedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
