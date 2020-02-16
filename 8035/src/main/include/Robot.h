#pragma once

#include <frc/Timer.h>
#include <frc/TimedRobot.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>

#include "controllers/Controllers.h"
#include "actuators/VoltageController.h"
#include "WMLCtre.h"
#include "Gearbox.h"

#include "RobotMap.h"
#include "strategy/StrategyController.h"
#include "NTProvider.h"

#include "ClimbingWinch.h"

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

  RobotMap robotmap;

  wml::Drivetrain *drivetrain;

  ClimbingWinch *winch;
};
