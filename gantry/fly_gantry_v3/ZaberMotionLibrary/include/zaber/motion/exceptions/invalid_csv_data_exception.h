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
             * Thrown when CSV file cannot be parsed as expected.
             */
            class InvalidCsvDataException: public MotionLibException {
            public:
                InvalidCsvDataException(const std::string& message);
                virtual ~InvalidCsvDataException() = default;
            protected:
                InvalidCsvDataException(const MotionLibException::ExceptionInfo& info);
            };
        }
    }
}
