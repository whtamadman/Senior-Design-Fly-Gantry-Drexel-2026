// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/device_address_conflict_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when there is a conflict in device numbers preventing unique addressing.
             */
            class DeviceAddressConflictException: public MotionLibException {
            public:
                DeviceAddressConflictException(const std::string& message, const std::string &customData);
                DeviceAddressConflictException(const std::string& message, const DeviceAddressConflictExceptionData &&customData);
                virtual ~DeviceAddressConflictException() = default;

                /**
                 * Additional data for DeviceAddressConflictException
                 */
                DeviceAddressConflictExceptionData const & getDetails() const;
            private:
                DeviceAddressConflictExceptionData details;
            protected:
                DeviceAddressConflictException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                DeviceAddressConflictException(const MotionLibException::ExceptionInfo& info, const DeviceAddressConflictExceptionData &&customData);
            };
        }
    }
}
