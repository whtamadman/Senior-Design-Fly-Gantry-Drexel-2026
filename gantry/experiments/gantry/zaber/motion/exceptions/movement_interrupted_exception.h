// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/movement_interrupted_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when ongoing movement is interrupted by another command or user input.
             */
            class MovementInterruptedException: public MotionLibException {
            public:
                MovementInterruptedException(const std::string& message, const std::string &customData);
                MovementInterruptedException(const std::string& message, const MovementInterruptedExceptionData &&customData);
                virtual ~MovementInterruptedException() = default;

                /**
                 * Additional data for MovementInterruptedException
                 */
                MovementInterruptedExceptionData const & getDetails() const;
            private:
                MovementInterruptedExceptionData details;
            protected:
                MovementInterruptedException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                MovementInterruptedException(const MotionLibException::ExceptionInfo& info, const MovementInterruptedExceptionData &&customData);
            };
        }
    }
}
