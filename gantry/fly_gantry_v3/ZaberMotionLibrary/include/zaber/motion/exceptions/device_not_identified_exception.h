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
             * Thrown when attempting an operation that requires an identified device.
             */
            class DeviceNotIdentifiedException: public MotionLibException {
            public:
                DeviceNotIdentifiedException(const std::string& message);
                virtual ~DeviceNotIdentifiedException() = default;
            protected:
                DeviceNotIdentifiedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
