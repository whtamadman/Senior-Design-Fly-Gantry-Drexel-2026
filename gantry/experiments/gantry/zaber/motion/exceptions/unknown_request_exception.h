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
             * Used for internal error handling. Indicates mixed library binary files. Reinstall the library.
             */
            class UnknownRequestException: public MotionLibException {
            public:
                UnknownRequestException(const std::string& message);
                virtual ~UnknownRequestException() = default;
            protected:
                UnknownRequestException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
