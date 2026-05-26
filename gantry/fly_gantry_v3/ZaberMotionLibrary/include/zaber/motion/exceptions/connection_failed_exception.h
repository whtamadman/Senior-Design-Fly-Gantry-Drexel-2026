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
             * Thrown when a connection breaks during a request.
             */
            class ConnectionFailedException: public MotionLibException {
            public:
                ConnectionFailedException(const std::string& message);
                virtual ~ConnectionFailedException() = default;
            protected:
                ConnectionFailedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
