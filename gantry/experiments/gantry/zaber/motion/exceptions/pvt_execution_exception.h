// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/pvt_execution_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a PVT sequence motion fails.
             */
            class PvtExecutionException: public MotionLibException {
            public:
                PvtExecutionException(const std::string& message, const std::string &customData);
                PvtExecutionException(const std::string& message, const PvtExecutionExceptionData &&customData);
                virtual ~PvtExecutionException() = default;

                /**
                 * Additional data for PvtExecutionException
                 */
                PvtExecutionExceptionData const & getDetails() const;
            private:
                PvtExecutionExceptionData details;
            protected:
                PvtExecutionException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                PvtExecutionException(const MotionLibException::ExceptionInfo& info, const PvtExecutionExceptionData &&customData);
            };
        }
    }
}
