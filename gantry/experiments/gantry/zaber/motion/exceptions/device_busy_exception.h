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
             * Thrown when a requested operation fails because the device is currently busy.
             */
            class DeviceBusyException: public MotionLibException {
            public:
                DeviceBusyException(const std::string& message);
                virtual ~DeviceBusyException() = default;
            protected:
                DeviceBusyException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
