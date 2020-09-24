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
#include "loops/UpdateGroup.h"
#include "sensors/Encoder.h"
#include "sensors/LimitSwitch.h"
#include "sensors/NavX.h"
#include "vision/Receiver.h"

#include "ControlMap.h"

#include "Drivetrain.h"
#include "subsystems/Climber.h"
#include "subsystems/RollerIntake.h"

struct RobotMap {
  wml::controllers::XboxController xbox{ 0 };
  wml::controllers::XboxController xbox2{ 1 };

  wml::controllers::SmartControllerGroup controllers{ xbox, xbox2 };

  // frc::PowerDistributionPanel pdp{0};

  wml::loops::UpdateGroup updateGroup;

  struct DriveTrain {
    wml::VictorSpx left1{ 5 };
    wml::VictorSpx left2{ 8 };

    wml::VictorSpx right1{ 6 };
    wml::VictorSpx right2{ 7 };


    wml::actuators::MotorVoltageController leftMotors = wml::actuators::MotorVoltageController::Group(left1, left2);
    wml::Gearbox leftGearbox{ &leftMotors, nullptr, 8.45 };

    wml::actuators::MotorVoltageController rightMotors = wml::actuators::MotorVoltageController::Group(right1, right2);
    wml::sensors::DigitalEncoder rightEncoder{ 4, 5, 2048 };
    wml::Gearbox rightGearbox{ &rightMotors, nullptr, 8.45 };

    wml::sensors::NavX navx{ frc::SPI::Port::kMXP, 200 };
    wml::sensors::NavXGyro gyro{ navx.Angular(wml::sensors::AngularAxis::YAW) };

    wml::DrivetrainConfig config{ leftGearbox, rightGearbox, &gyro, 0.71, 0.71, 0.0762, 50 };
  }; DriveTrain drivetrain;


  struct Intake {
    // wml::actuators::DoubleSolenoid intakeSolenoid{ 1, 2, 0.3 };
    wml::actuators::BinaryServo temp{ 1, 0, 1 };

    wml::TalonSrx intakeSrx{ 2 };


    wml::actuators::MotorVoltageController intakeMotors = wml::actuators::MotorVoltageController::Group(intakeSrx);
    wml::Gearbox intakeGearbox{ &intakeMotors, nullptr, 4 };

    subsystems::RollerIntakeConfig config{ intakeGearbox, temp /*intakeSolenoid*/, ControlMap::Intake::Throttles::INTAKING, ControlMap::Intake::Throttles::OUTTAKING };
  }; Intake intake;


  struct Indexer {
    wml::TalonSrx indexerSrx{ 3 };


    wml::actuators::MotorVoltageController indexerMotors = wml::actuators::MotorVoltageController::Group(indexerSrx);
    wml::Gearbox indexerGearbox{ &indexerMotors, nullptr, 4 };
  }; Indexer indexer;


  struct Shooter {
    wml::TalonSrx shooter1{ 9 };
    wml::TalonSrx shooter2{ 10 };

    wml::control::PIDGains autoAimGains{ "Auto Aim Gains", 0.15 };


    wml::actuators::MotorVoltageController shooterMotors = wml::actuators::MotorVoltageController::Group(shooter1, shooter2);
    wml::Gearbox shooterGearbox{ &shooterMotors, nullptr, 3 };
  }; Shooter shooter;


  struct Climber {
    wml::TalonSrx climberWinchSrx{ 4 };
    wml::actuators::BinaryServo climberWinchServo{ 0, 150, 50 };

    wml::TalonSrx climberElevatorSrx{ 11 };


    wml::actuators::MotorVoltageController climberWinchMotors = wml::actuators::MotorVoltageController::Group(climberWinchSrx);
    wml::Gearbox climberWinchGearbox{ &climberWinchMotors, nullptr, 30 };

    wml::actuators::MotorVoltageController climberElevatorMotors = wml::actuators::MotorVoltageController::Group(climberElevatorSrx);
    wml::Gearbox climberElevatorGearbox{ &climberElevatorMotors, nullptr, 1 };

    subsystems::ClimberConfig config{
      climberWinchGearbox,
      climberWinchServo,
      climberElevatorGearbox,
      ControlMap::Climber::Throttles::RAISING,
      ControlMap::Climber::Throttles::LOWERING,
      ControlMap::Climber::Throttles::WINCH
    };
  }; Climber climber;


  struct ControlSystem {
    // vision
    wml::vision::Receiver vision{};
  }; ControlSystem controlSystem;
};
