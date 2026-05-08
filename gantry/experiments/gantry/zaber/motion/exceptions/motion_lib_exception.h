#pragma once

#include <stdexcept>
#include <string>

namespace zaber
{
    namespace motion
    {
        namespace exceptions
        {
            class MotionLibException: public std::runtime_error {
            public:
                struct ExceptionInfo {
                    std::string message;
                    const char* typeName;
                };

                MotionLibException(const std::string& message);
                MotionLibException(const ExceptionInfo& info);
                virtual ~MotionLibException() = default;

                /**
                 * Error message of the exception
                **/
                const std::string& getMessage() const;

                virtual std::string toString() const;
            private:
                std::string message;
            };
        }
    }
}
