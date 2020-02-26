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

#include "ControlMap.h"

#include "Drivetrain.h"
#include "subsystems/Climber.h"
#include "subsystems/RollerIntake.h"

struct RobotMap {
  wml::controllers::XboxController xbox{ 0 };

  wml::controllers::SmartControllerGroup controllers{ xbox };

  // frc::PowerDistributionPanel pdp{0};

  wml::loops::UpdateGroup updateGroup;

  struct DriveTrain {
    wml::TalonSrx left1{ 3 };
    wml::TalonSrx left2{ 4 };

    wml::TalonSrx right1{ 1 };
    wml::TalonSrx right2{ 2 };


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
    wml::actuators::DoubleSolenoid intakeSolenoid{ 1, 2, 0.3 };

    wml::TalonSrx intakeSrx{ 10 };


    wml::actuators::MotorVoltageController intakeMotors = wml::actuators::MotorVoltageController::Group(intakeSrx);
    wml::Gearbox intakeGearbox{ &intakeMotors, nullptr, 1 };

    RollerIntakeConfig config{ intakeGearbox, intakeSolenoid, ControlMap::Intake::Throttles::INTAKING, ControlMap::Intake::Throttles::OUTTAKING };
  }; Intake intake;


  struct Loader {
    wml::TalonSrx loaderSrx{ 11 };


    wml::actuators::MotorVoltageController loaderMotors = wml::actuators::MotorVoltageController::Group(loaderSrx);
    wml::Gearbox loaderGearbox{ &loaderMotors, nullptr, 1 };
  }; Loader loader;


  struct Shooter {
    wml::TalonSrx shooterSrx{ 12 };


    wml::actuators::MotorVoltageController shooterMotors = wml::actuators::MotorVoltageController::Group(shooterSrx);
    wml::Gearbox shooterGearbox{ &shooterMotors, nullptr, 1 };
  }; Shooter shooter;


  struct Climber {
    wml::TalonSrx climberWinchSrx{ 13 };
    wml::actuators::BinaryServo climberWinchServo{ 4, 100, 150 };

    wml::TalonSrx climberElevatorSrx{ 15 };


    wml::actuators::MotorVoltageController climberWinchMotors = wml::actuators::MotorVoltageController::Group(climberWinchSrx);
    wml::Gearbox climberWinchGearbox{ &climberWinchMotors, nullptr, 1 };

    wml::actuators::MotorVoltageController climberElevatorMotors = wml::actuators::MotorVoltageController::Group(climberElevatorSrx);
    wml::Gearbox climberElevatorGearbox{ &climberElevatorMotors, nullptr, 1 };

    ClimberConfig config{
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
    // std::shared_ptr<nt::NetworkTable> visionTable = nt::NetworkTableInstance::GetDefault().GetTable("VisionTracking");
    // std::shared_ptr<nt::NetworkTable> hatchTable = visionTable->GetSubTable("HatchTracking");
    // std::shared_ptr<nt::NetworkTable> tapeTable = visionTable->GetSubTable("TapeTracking");
    
    // nt::NetworkTableEntry hatchDistanceEntry  = hatchTable->GetEntry("Hatch Distance"),
    //                       hatchXoffsetEntry   = hatchTable->GetEntry("Hatch X Offset"),
    //                       hatchYoffsetEntry   = hatchTable->GetEntry("Hatch Y Offset"),
    //                       tapeDistanceEntry   = tapeTable->GetEntry("Distance"),
    //                       tapeAngleEntry      = tapeTable->GetEntry("Angle"),
    //                       tapeTargetEntry     = tapeTable->GetEntry("Target");
  }; ControlSystem controlSystem;
};
