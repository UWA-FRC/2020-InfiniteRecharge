#pragma once

#include <frc/Timer.h>
#include <frc/TimedRobot.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>

#include "ControlMap.h"
#include "strategies/intake/Manual.h"
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
  std::shared_ptr<strategies::intake::Manual> intakeManualStrategy;

  // intake

#if SHOOTER_TOGGLE_MODE
  bool shooterToggle = false;
#endif

  Climber *climber;
};
