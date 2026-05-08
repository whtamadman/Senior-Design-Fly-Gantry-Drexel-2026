// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/pvt_movement_failed_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a device registers a fault during PVT movement.
             */
            class PvtMovementFailedException: public MotionLibException {
            public:
                PvtMovementFailedException(const std::string& message, const std::string &customData);
                PvtMovementFailedException(const std::string& message, const PvtMovementFailedExceptionData &&customData);
                virtual ~PvtMovementFailedException() = default;

                /**
                 * Additional data for PvtMovementFailedException
                 */
                PvtMovementFailedExceptionData const & getDetails() const;
            private:
                PvtMovementFailedExceptionData details;
            protected:
                PvtMovementFailedException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                PvtMovementFailedException(const MotionLibException::ExceptionInfo& info, const PvtMovementFailedExceptionData &&customData);
            };
        }
    }
}
