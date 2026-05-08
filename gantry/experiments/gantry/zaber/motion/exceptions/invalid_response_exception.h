// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/invalid_response_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a device sends a response with unexpected type or data.
             */
            class InvalidResponseException: public MotionLibException {
            public:
                InvalidResponseException(const std::string& message, const std::string &customData);
                InvalidResponseException(const std::string& message, const InvalidResponseExceptionData &&customData);
                virtual ~InvalidResponseException() = default;

                /**
                 * Additional data for InvalidResponseException
                 */
                InvalidResponseExceptionData const & getDetails() const;
            private:
                InvalidResponseExceptionData details;
            protected:
                InvalidResponseException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                InvalidResponseException(const MotionLibException::ExceptionInfo& info, const InvalidResponseExceptionData &&customData);
            };
        }
    }
}
