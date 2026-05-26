// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/pvt_movement_interrupted_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when ongoing PVT movement is interrupted by another command or user input.
             */
            class PvtMovementInterruptedException: public MotionLibException {
            public:
                PvtMovementInterruptedException(const std::string& message, const std::string &customData);
                PvtMovementInterruptedException(const std::string& message, const PvtMovementInterruptedExceptionData &&customData);
                virtual ~PvtMovementInterruptedException() = default;

                /**
                 * Additional data for PvtMovementInterruptedException
                 */
                PvtMovementInterruptedExceptionData const & getDetails() const;
            private:
                PvtMovementInterruptedExceptionData details;
            protected:
                PvtMovementInterruptedException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                PvtMovementInterruptedException(const MotionLibException::ExceptionInfo& info, const PvtMovementInterruptedExceptionData &&customData);
            };
        }
    }
}
