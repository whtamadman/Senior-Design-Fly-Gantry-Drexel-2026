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
             * Used for internal error handling. Please report an issue if observed.
             */
            class InternalErrorException: public MotionLibException {
            public:
                InternalErrorException(const std::string& message);
                virtual ~InternalErrorException() = default;
            protected:
                InternalErrorException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
