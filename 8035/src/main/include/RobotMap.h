#pragma once

#include <frc/SpeedControllerGroup.h>
#include <frc/Spark.h>
#include <frc/PowerDistributionPanel.h>

#include "WMLCtre.h"
#include "WMLRev.h"
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
  wml::controllers::Joystick joy1{ 0 }; // Driver
  wml::controllers::Joystick joy2{ 1 }; // Co-Driver

  wml::controllers::SmartControllerGroup contGroup{ joy1, joy2 };

  // frc::PowerDistributionPanel pdp{0};

  struct DriveTrain {
    wml::TalonSrx leftSrx{ 3 };
    wml::VictorSpx leftSpx{ 4 };
    wml::SparkMax sparkMax{ 1, wml::SparkMax::MotorType::kNEO };
    wml::actuators::MotorVoltageController leftMotors = wml::actuators::MotorVoltageController::Group(leftSrx, leftSpx);
    wml::sensors::DigitalEncoder leftEncoder{ 7, 6, 2048 };
    wml::Gearbox leftGearbox{ &leftMotors, &leftEncoder, 8.45 };

    wml::TalonSrx rightSrx{ 1 };
    wml::VictorSpx rightSpx{ 2 };
    wml::actuators::MotorVoltageController rightMotors = wml::actuators::MotorVoltageController::Group(rightSrx, rightSpx);
    wml::sensors::DigitalEncoder rightEncoder{ 4, 5, 2048 };
    wml::Gearbox rightGearbox{ &rightMotors, &rightEncoder, 8.45 };

    wml::sensors::NavX navx{frc::SPI::Port::kMXP, 200};
    wml::sensors::NavXGyro gyro{ navx.Angular(wml::sensors::AngularAxis::YAW) };
    wml::sensors::NavXGyro pitchGgyro{ navx.Angular(wml::sensors::AngularAxis::ROLL) }; // navx is 'sideways';
    wml::sensors::NavXGyro rollGyro{ navx.Angular(wml::sensors::AngularAxis::PITCH) };  // pitch <=> roll

    wml::DrivetrainConfig config{ leftGearbox, rightGearbox, &gyro, 0.71, 0.71, 0.0762, 50 };
  };

  DriveTrain drivetrain;


  struct ControlSystem {
    wml::actuators::Compressor compressor{ 1 };
    
    // vision
    std::shared_ptr<nt::NetworkTable> visionTable = nt::NetworkTableInstance::GetDefault().GetTable("VisionTracking");
    std::shared_ptr<nt::NetworkTable> hatchTable = visionTable->GetSubTable("HatchTracking");
    std::shared_ptr<nt::NetworkTable> tapeTable = visionTable->GetSubTable("TapeTracking");
    
    nt::NetworkTableEntry hatchDistanceEntry  = hatchTable->GetEntry("Hatch Distance"),
                          hatchXoffsetEntry   = hatchTable->GetEntry("Hatch X Offset"),
                          hatchYoffsetEntry   = hatchTable->GetEntry("Hatch Y Offset"),
                          tapeDistanceEntry   = tapeTable->GetEntry("Distance"),
                          tapeAngleEntry      = tapeTable->GetEntry("Angle"),
                          tapeTargetEntry     = tapeTable->GetEntry("Target");
  };

  ControlSystem controlSystem;
};
