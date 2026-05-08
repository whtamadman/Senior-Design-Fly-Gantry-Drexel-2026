// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/set_device_state_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a device cannot be set to the supplied state.
             */
            class SetDeviceStateFailedException: public MotionLibException {
            public:
                SetDeviceStateFailedException(const std::string& message, const std::string &customData);
                SetDeviceStateFailedException(const std::string& message, const SetDeviceStateExceptionData &&customData);
                virtual ~SetDeviceStateFailedException() = default;

                /**
                 * Additional data for SetDeviceStateFailedException
                 */
                SetDeviceStateExceptionData const & getDetails() const;
            private:
                SetDeviceStateExceptionData details;
            protected:
                SetDeviceStateFailedException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                SetDeviceStateFailedException(const MotionLibException::ExceptionInfo& info, const SetDeviceStateExceptionData &&customData);
            };
        }
    }
}
