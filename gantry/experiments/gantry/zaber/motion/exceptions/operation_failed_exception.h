// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/operation_failed_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a non-motion device fails to perform a requested operation.
             */
            class OperationFailedException: public MotionLibException {
            public:
                OperationFailedException(const std::string& message, const std::string &customData);
                OperationFailedException(const std::string& message, const OperationFailedExceptionData &&customData);
                virtual ~OperationFailedException() = default;

                /**
                 * Additional data for OperationFailedException
                 */
                OperationFailedExceptionData const & getDetails() const;
            private:
                OperationFailedExceptionData details;
            protected:
                OperationFailedException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                OperationFailedException(const MotionLibException::ExceptionInfo& info, const OperationFailedExceptionData &&customData);
            };
        }
    }
}
