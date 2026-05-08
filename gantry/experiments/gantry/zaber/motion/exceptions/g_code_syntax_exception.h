// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/g_code_syntax_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a block of G-Code cannot be parsed.
             */
            class GCodeSyntaxException: public MotionLibException {
            public:
                GCodeSyntaxException(const std::string& message, const std::string &customData);
                GCodeSyntaxException(const std::string& message, const GCodeSyntaxExceptionData &&customData);
                virtual ~GCodeSyntaxException() = default;

                /**
                 * Additional data for GCodeSyntaxException
                 */
                GCodeSyntaxExceptionData const & getDetails() const;
            private:
                GCodeSyntaxExceptionData details;
            protected:
                GCodeSyntaxException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                GCodeSyntaxException(const MotionLibException::ExceptionInfo& info, const GCodeSyntaxExceptionData &&customData);
            };
        }
    }
}
