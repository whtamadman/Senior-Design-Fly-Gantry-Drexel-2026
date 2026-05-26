// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/g_code_execution_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a block of G-Code cannot be executed.
             */
            class GCodeExecutionException: public MotionLibException {
            public:
                GCodeExecutionException(const std::string& message, const std::string &customData);
                GCodeExecutionException(const std::string& message, const GCodeExecutionExceptionData &&customData);
                virtual ~GCodeExecutionException() = default;

                /**
                 * Additional data for GCodeExecutionException
                 */
                GCodeExecutionExceptionData const & getDetails() const;
            private:
                GCodeExecutionExceptionData details;
            protected:
                GCodeExecutionException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                GCodeExecutionException(const MotionLibException::ExceptionInfo& info, const GCodeExecutionExceptionData &&customData);
            };
        }
    }
}
