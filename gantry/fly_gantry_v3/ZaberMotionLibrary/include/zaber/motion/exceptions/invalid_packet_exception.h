// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

#include "zaber/motion/exceptions/motion_lib_exception.h"
#include "zaber/motion/dto/exceptions/invalid_packet_exception_data.h"
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            /**
             * Thrown when a packet from a device cannot be parsed.
             */
            class InvalidPacketException: public MotionLibException {
            public:
                InvalidPacketException(const std::string& message, const std::string &customData);
                InvalidPacketException(const std::string& message, const InvalidPacketExceptionData &&customData);
                virtual ~InvalidPacketException() = default;

                /**
                 * Additional data for InvalidPacketException
                 */
                InvalidPacketExceptionData const & getDetails() const;
            private:
                InvalidPacketExceptionData details;
            protected:
                InvalidPacketException(const MotionLibException::ExceptionInfo& info, const std::string &customData);
                InvalidPacketException(const MotionLibException::ExceptionInfo& info, const InvalidPacketExceptionData &&customData);
            };
        }
    }
}
