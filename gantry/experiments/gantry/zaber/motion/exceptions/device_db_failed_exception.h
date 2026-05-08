// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/device_db_failed_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when device information cannot be retrieved from the device database.
             */
            class DeviceDbFailedException: public MotionLibException {
            public:
                DeviceDbFailedException(const std::string& message, const std::string &customData);
                DeviceDbFailedException(const std::string& message, const DeviceDbFailedExceptionData &&customData);
                virtual ~DeviceDbFailedException() = default;

                /**
                 * Additional data for DeviceDbFailedException
                 */
                DeviceDbFailedExceptionData const & getDetails() const;
            private:
                DeviceDbFailedExceptionData details;
            protected:
                DeviceDbFailedException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                DeviceDbFailedException(const MotionLibException::ExceptionInfo& info, const DeviceDbFailedExceptionData &&customData);
            };
        }
    }
}
