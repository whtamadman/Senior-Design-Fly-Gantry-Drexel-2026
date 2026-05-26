// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //

#pragma once

namespace zaber {
namespace motion {

class AsyncContext;
class Serializer;
class SdkEvent;

namespace exceptions {
class BadCommandException;
class BadDataException;
class BinaryCommandFailedException;
class CommandFailedException;
class CommandPreemptedException;
class CommandTooLongException;
class ConnectionClosedException;
class ConnectionFailedException;
class ConversionFailedException;
class DeviceAddressConflictException;
class DeviceBusyException;
class DeviceDbFailedException;
class DeviceDetectionFailedException;
class DeviceFailedException;
class DeviceNotIdentifiedException;
class DriverDisabledException;
class GCodeExecutionException;
class GCodeSyntaxException;
class IncompatibleSharedLibraryException;
class InternalErrorException;
class InvalidArgumentException;
class InvalidCsvDataException;
class InvalidDataException;
class InvalidOperationException;
class InvalidPacketException;
class InvalidParkStateException;
class InvalidRequestDataException;
class InvalidResponseException;
class IoChannelOutOfRangeException;
class IoFailedException;
class LockstepEnabledException;
class LockstepNotEnabledException;
class MovementFailedException;
class MovementInterruptedException;
class NoDeviceFoundException;
class NoValueForKeyException;
class NotSupportedException;
class OperationFailedException;
class OsFailedException;
class OutOfRequestIdsException;
class PvtDiscontinuityException;
class PvtExecutionException;
class PvtModeException;
class PvtMovementFailedException;
class PvtMovementInterruptedException;
class PvtSequenceGenerationFailedException;
class PvtSetupFailedException;
class RemoteModeException;
class RequestTimeoutException;
class SerialPortBusyException;
class SetDeviceStateFailedException;
class SetPeripheralStateFailedException;
class StreamDiscontinuityException;
class StreamExecutionException;
class StreamModeException;
class StreamMovementFailedException;
class StreamMovementInterruptedException;
class StreamSetupFailedException;
class TimeoutException;
class TransportAlreadyUsedException;
class UnknownRequestException;
class Ge1GripperMovementFailedException;
} // namespace exceptions

class Serializable {
public:
    virtual ~Serializable() { }

protected:
    friend AsyncContext;
    friend Serializer;
    friend SdkEvent;
    friend exceptions::BadCommandException;
    friend exceptions::BadDataException;
    friend exceptions::BinaryCommandFailedException;
    friend exceptions::CommandFailedException;
    friend exceptions::CommandPreemptedException;
    friend exceptions::CommandTooLongException;
    friend exceptions::ConnectionClosedException;
    friend exceptions::ConnectionFailedException;
    friend exceptions::ConversionFailedException;
    friend exceptions::DeviceAddressConflictException;
    friend exceptions::DeviceBusyException;
    friend exceptions::DeviceDbFailedException;
    friend exceptions::DeviceDetectionFailedException;
    friend exceptions::DeviceFailedException;
    friend exceptions::DeviceNotIdentifiedException;
    friend exceptions::DriverDisabledException;
    friend exceptions::GCodeExecutionException;
    friend exceptions::GCodeSyntaxException;
    friend exceptions::IncompatibleSharedLibraryException;
    friend exceptions::InternalErrorException;
    friend exceptions::InvalidArgumentException;
    friend exceptions::InvalidCsvDataException;
    friend exceptions::InvalidDataException;
    friend exceptions::InvalidOperationException;
    friend exceptions::InvalidPacketException;
    friend exceptions::InvalidParkStateException;
    friend exceptions::InvalidRequestDataException;
    friend exceptions::InvalidResponseException;
    friend exceptions::IoChannelOutOfRangeException;
    friend exceptions::IoFailedException;
    friend exceptions::LockstepEnabledException;
    friend exceptions::LockstepNotEnabledException;
    friend exceptions::MovementFailedException;
    friend exceptions::MovementInterruptedException;
    friend exceptions::NoDeviceFoundException;
    friend exceptions::NoValueForKeyException;
    friend exceptions::NotSupportedException;
    friend exceptions::OperationFailedException;
    friend exceptions::OsFailedException;
    friend exceptions::OutOfRequestIdsException;
    friend exceptions::PvtDiscontinuityException;
    friend exceptions::PvtExecutionException;
    friend exceptions::PvtModeException;
    friend exceptions::PvtMovementFailedException;
    friend exceptions::PvtMovementInterruptedException;
    friend exceptions::PvtSequenceGenerationFailedException;
    friend exceptions::PvtSetupFailedException;
    friend exceptions::RemoteModeException;
    friend exceptions::RequestTimeoutException;
    friend exceptions::SerialPortBusyException;
    friend exceptions::SetDeviceStateFailedException;
    friend exceptions::SetPeripheralStateFailedException;
    friend exceptions::StreamDiscontinuityException;
    friend exceptions::StreamExecutionException;
    friend exceptions::StreamModeException;
    friend exceptions::StreamMovementFailedException;
    friend exceptions::StreamMovementInterruptedException;
    friend exceptions::StreamSetupFailedException;
    friend exceptions::TimeoutException;
    friend exceptions::TransportAlreadyUsedException;
    friend exceptions::UnknownRequestException;
    friend exceptions::Ge1GripperMovementFailedException;

    virtual void populateFromByteArray(const std::string& buffer) = 0;
    virtual std::string toByteArray() const = 0;

};

} // namespace motion
} // namespace zaber
