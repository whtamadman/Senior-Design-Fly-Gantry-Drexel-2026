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
             * Thrown when a transport has already been used to open another connection.
             */
            class TransportAlreadyUsedException: public MotionLibException {
            public:
                TransportAlreadyUsedException(const std::string& message);
                virtual ~TransportAlreadyUsedException() = default;
            protected:
                TransportAlreadyUsedException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
