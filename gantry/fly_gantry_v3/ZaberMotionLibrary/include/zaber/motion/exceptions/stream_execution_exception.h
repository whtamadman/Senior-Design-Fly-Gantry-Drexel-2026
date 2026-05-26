// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/stream_execution_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a streamed motion fails.
             */
            class StreamExecutionException: public MotionLibException {
            public:
                StreamExecutionException(const std::string& message, const std::string &customData);
                StreamExecutionException(const std::string& message, const StreamExecutionExceptionData &&customData);
                virtual ~StreamExecutionException() = default;

                /**
                 * Additional data for StreamExecutionException
                 */
                StreamExecutionExceptionData const & getDetails() const;
            private:
                StreamExecutionExceptionData details;
            protected:
                StreamExecutionException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                StreamExecutionException(const MotionLibException::ExceptionInfo& info, const StreamExecutionExceptionData &&customData);
            };
        }
    }
}
