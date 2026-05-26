// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/movement_failed_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a device registers a fault during movement.
             */
            class MovementFailedException: public MotionLibException {
            public:
                MovementFailedException(const std::string& message, const std::string &customData);
                MovementFailedException(const std::string& message, const MovementFailedExceptionData &&customData);
                virtual ~MovementFailedException() = default;

                /**
                 * Additional data for MovementFailedException
                 */
                MovementFailedExceptionData const & getDetails() const;
            private:
                MovementFailedExceptionData details;
            protected:
                MovementFailedException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                MovementFailedException(const MotionLibException::ExceptionInfo& info, const MovementFailedExceptionData &&customData);
            };
        }
    }
}
