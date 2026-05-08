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
             * Thrown when the loaded shared library is incompatible with the running code.
             * Typically caused by mixed library binary files. Reinstall the library.
             */
            class IncompatibleSharedLibraryException: public MotionLibException {
            public:
                IncompatibleSharedLibraryException(const std::string& message);
                virtual ~IncompatibleSharedLibraryException() = default;
            protected:
                IncompatibleSharedLibraryException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
