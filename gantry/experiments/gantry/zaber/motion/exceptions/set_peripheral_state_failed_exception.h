// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/set_peripheral_state_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when an axis cannot be set to the supplied state.
             */
            class SetPeripheralStateFailedException: public MotionLibException {
            public:
                SetPeripheralStateFailedException(const std::string& message, const std::string &customData);
                SetPeripheralStateFailedException(const std::string& message, const SetPeripheralStateExceptionData &&customData);
                virtual ~SetPeripheralStateFailedException() = default;

                /**
                 * Additional data for SetPeripheralStateFailedException
                 */
                SetPeripheralStateExceptionData const & getDetails() const;
            private:
                SetPeripheralStateExceptionData details;
            protected:
                SetPeripheralStateFailedException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                SetPeripheralStateFailedException(const MotionLibException::ExceptionInfo& info, const SetPeripheralStateExceptionData &&customData);
            };
        }
    }
}
