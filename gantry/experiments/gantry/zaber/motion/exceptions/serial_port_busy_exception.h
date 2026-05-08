// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/connection_failed_exception.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a serial port cannot be opened because it is in use by another application.
             */
            class SerialPortBusyException: public ConnectionFailedException {
            public:
                SerialPortBusyException(const std::string& message);
                virtual ~SerialPortBusyException() = default;
            protected:
                SerialPortBusyException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
