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
             * Thrown when device detection fails.
             */
            class DeviceDetectionFailedException: public MotionLibException {
            public:
                DeviceDetectionFailedException(const std::string& message);
                virtual ~DeviceDetectionFailedException() = default;
            protected:
                DeviceDetectionFailedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
