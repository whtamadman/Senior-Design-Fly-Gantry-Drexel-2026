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
             * Thrown when attempting to communicate on a closed connection.
             */
            class ConnectionClosedException: public MotionLibException {
            public:
                ConnectionClosedException(const std::string& message);
                virtual ~ConnectionClosedException() = default;
            protected:
                ConnectionClosedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
