#pragma once

#include <stdexcept>
#include <string>

namespace zaber
{
    namespace motion
    {
        class LibraryIntegrationException: public std::runtime_error {
        public:
            LibraryIntegrationException(const std::string& message);
            virtual ~LibraryIntegrationException() = default;

            std::string message() const;
        };
    }
}