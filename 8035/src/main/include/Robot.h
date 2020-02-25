#pragma once

#include <frc/Timer.h>
#include <frc/TimedRobot.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>

#include "ControlMap.h"
#include "RobotMap.h"
#include "strategy/StrategyController.h"
#include "NTProvider.h"

class Robot : public frc::TimedRobot, protected wml::StrategyController, protected wml::NTProvider {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;

  void DisabledInit() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  void StrategyControllerUpdate(double dt) { StrategyController::Update(dt); };
  void NTProviderControllerUpdate() { NTProvider::Update(); };


  RobotMap robotmap;

  wml::Drivetrain *drivetrain;

  RollerIntake *intake;

  bool loaderState = false;
  void LoaderUpdate() { robotmap.loader.loaderGearbox.transmission->SetVoltage(loaderState ? ControlMap::Loader::throttle : 0); };
};
