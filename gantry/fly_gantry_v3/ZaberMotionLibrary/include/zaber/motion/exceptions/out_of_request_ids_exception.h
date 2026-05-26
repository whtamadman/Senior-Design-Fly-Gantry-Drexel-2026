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
             * Thrown when the library is overwhelmed with too many simultaneous requests.
             */
            class OutOfRequestIdsException: public MotionLibException {
            public:
                OutOfRequestIdsException(const std::string& message);
                virtual ~OutOfRequestIdsException() = default;
            protected:
                OutOfRequestIdsException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
