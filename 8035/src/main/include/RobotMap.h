#pragma once

#include <frc/SpeedControllerGroup.h>
#include <frc/Spark.h>
#include <frc/PowerDistributionPanel.h>

#include "WMLCtre.h"
#include "controllers/Controllers.h"
#include "Gearbox.h"
#include "actuators/BinaryServo.h"
#include "actuators/Compressor.h"
#include "actuators/DoubleSolenoid.h"
#include "actuators/VoltageController.h"
#include "sensors/Encoder.h"
#include "sensors/LimitSwitch.h"
#include "sensors/NavX.h"

#include "Drivetrain.h"

struct RobotMap {
  wml::controllers::XboxController xbox{ 0 }; // Driver
  // wml::controllers::Joystick joy2{ 1 }; // Co-Driver

  // wml::controllers::SmartControllerGroup contGroup{ joy1, joy2 };

  // frc::PowerDistributionPanel pdp{0};

  struct DriveTrain {
    wml::VictorSpx left1{ 7 };
    wml::VictorSpx left2{ 6 };
    wml::actuators::MotorVoltageController leftMotors = wml::actuators::MotorVoltageController::Group(left1, left2);
    // wml::sensors::DigitalEncoder leftEncoder{ 7, 6, 2048 };
    wml::Gearbox leftGearbox{ &leftMotors, nullptr, 8.45 };

    wml::VictorSpx right1{ 5 };
    wml::VictorSpx right2{ 8 };
    wml::actuators::MotorVoltageController rightMotors = wml::actuators::MotorVoltageController::Group(right1, right2);
    // wml::sensors::DigitalEncoder rightEncoder{ 4, 5, 2048 };
    wml::Gearbox rightGearbox{ &rightMotors, nullptr, 8.45 };

    wml::sensors::NavX navx{frc::SPI::Port::kMXP, 200};
    wml::sensors::NavXGyro gyro{ navx.Angular(wml::sensors::AngularAxis::YAW) };
    // wml::sensors::NavXGyro pitchGgyro{ navx.Angular(wml::sensors::AngularAxis::ROLL) }; // navx is 'sideways';
    // wml::sensors::NavXGyro rollGyro{ navx.Angular(wml::sensors::AngularAxis::PITCH) };  // pitch <=> roll

    wml::DrivetrainConfig config{ leftGearbox, rightGearbox, &gyro, 0.71, 0.71, 0.0762, 50 };
  };

  DriveTrain drivetrain;


  struct ControlSystem {
    wml::actuators::Compressor compressor{ 1 };
  };

  ControlSystem controlSystem;

  struct ClimbingWinch {
    wml::TalonSrx winchMotor{ 9 };
    wml::actuators::MotorVoltageController winchMotorGroup = wml::actuators::MotorVoltageController::Group(winchMotor);
    wml::Gearbox winchGearbox{ &winchMotorGroup, nullptr, 8.45 };

    wml::actuators::BinaryServo servo{ 0, 50, 160 };
  };

  ClimbingWinch climbingWinch;
};
