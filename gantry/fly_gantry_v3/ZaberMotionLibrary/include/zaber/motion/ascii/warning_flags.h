// ===== THIS FILE IS GENERATED FROM A TEMPLATE ===== //
// ============== DO NOT EDIT DIRECTLY ============== //
#pragma once

namespace zaber { namespace motion { namespace ascii {

    /**
     * Warning flag constants that indicate whether any device fault or warning is active.
     * For more information please refer to the
     * [ASCII Protocol Manual](https://www.zaber.com/protocol-manual#topic_message_format_warning_flags).
     */
    namespace warning_flags {
        /**
         * Critical System Error.
         */
        static const std::string CRITICAL_SYSTEM_ERROR = "FF";

        /**
         * Peripheral Not Supported.
         */
        static const std::string PERIPHERAL_NOT_SUPPORTED = "FN";

        /**
         * Peripheral Inactive.
         */
        static const std::string PERIPHERAL_INACTIVE = "FZ";

        /**
         * Hardware Emergency Stop Driver Disabled.
         */
        static const std::string HARDWARE_EMERGENCY_STOP = "FH";

        /**
         * Overvoltage or Undervoltage Driver Disabled.
         */
        static const std::string OVERVOLTAGE_OR_UNDERVOLTAGE = "FV";

        /**
         * Driver Disabled on Startup or by Command.
         * Devices with Firmware 7.11 and above.
         */
        static const std::string DRIVER_DISABLED_NO_FAULT = "FO";

        /**
         * Current Inrush Error.
         */
        static const std::string CURRENT_INRUSH_ERROR = "FC";

        /**
         * Motor Temperature Error.
         */
        static const std::string MOTOR_TEMPERATURE_ERROR = "FM";

        /**
         * Driver Disabled.
         * Devices with Firmware 7.10 and lower.
         */
        static const std::string DRIVER_DISABLED = "FD";

        /**
         * Encoder Error.
         */
        static const std::string ENCODER_ERROR = "FQ";

        /**
         * Index Error.
         */
        static const std::string INDEX_ERROR = "FI";

        /**
         * Analog Encoder Sync Error.
         */
        static const std::string ANALOG_ENCODER_SYNC_ERROR = "FA";

        /**
         * Overdrive Limit Exceeded.
         */
        static const std::string OVERDRIVE_LIMIT_EXCEEDED = "FR";

        /**
         * Stalled and Stopped.
         */
        static const std::string STALLED_AND_STOPPED = "FS";

        /**
         * Stream Bounds Error.
         */
        static const std::string STREAM_BOUNDS_ERROR = "FB";

        /**
         * Interpolated Path Deviation.
         */
        static const std::string INTERPOLATED_PATH_DEVIATION = "FP";

        /**
         * Limit Error.
         */
        static const std::string LIMIT_ERROR = "FE";

        /**
         * Excessive Twist.
         */
        static const std::string EXCESSIVE_TWIST = "FT";

        /**
         * Unexpected Limit Trigger.
         */
        static const std::string UNEXPECTED_LIMIT_TRIGGER = "WL";

        /**
         * Voltage Out of Range.
         */
        static const std::string VOLTAGE_OUT_OF_RANGE = "WV";

        /**
         * Controller Temperature High.
         */
        static const std::string CONTROLLER_TEMPERATURE_HIGH = "WT";

        /**
         * Stalled with Recovery.
         */
        static const std::string STALLED_WITH_RECOVERY = "WS";

        /**
         * Displaced When Stationary.
         */
        static const std::string DISPLACED_WHEN_STATIONARY = "WM";

        /**
         * Invalid Calibration Type.
         */
        static const std::string INVALID_CALIBRATION_TYPE = "WP";

        /**
         * No Reference Position.
         */
        static const std::string NO_REFERENCE_POSITION = "WR";

        /**
         * Device Not Homed.
         */
        static const std::string DEVICE_NOT_HOMED = "WH";

        /**
         * Manual Control.
         */
        static const std::string MANUAL_CONTROL = "NC";

        /**
         * Movement Interrupted.
         */
        static const std::string MOVEMENT_INTERRUPTED = "NI";

        /**
         * Stream Discontinuity.
         */
        static const std::string STREAM_DISCONTINUITY = "ND";

        /**
         * Value Rounded.
         */
        static const std::string VALUE_ROUNDED = "NR";

        /**
         * Value Truncated.
         */
        static const std::string VALUE_TRUNCATED = "NT";

        /**
         * Setting Update Pending.
         */
        static const std::string SETTING_UPDATE_PENDING = "NU";

        /**
         * Joystick Calibrating.
         */
        static const std::string JOYSTICK_CALIBRATING = "NJ";

        /**
         * Device in Firmware Update Mode.
         * Firmware 6.xx only.
         */
        static const std::string FIRMWARE_UPDATE_MODE = "NB";

    }  //namespace warning_flags

}  // namespace ascii
}  // namespace motion
}  // namespace zaber
