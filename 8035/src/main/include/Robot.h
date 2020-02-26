#pragma once

#include <frc/Timer.h>
#include <frc/TimedRobot.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>

#include "RobotMap.h"
#include "strategy/StrategyController.h"
#include "NTProvider.h"

#include "NTUtil/Slave.h"
#include "NTUtil/Master.h"

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


  double slave = 2, master = 4;
  wml::NTUtil::Slave<double> doubleSlave{ nt::NetworkTableInstance::GetDefault().GetTable("NTUtil"), "slave" , &slave };
  wml::NTUtil::Master<double> doubleMaster{ nt::NetworkTableInstance::GetDefault().GetTable("NTUtil"), "master", &slave };
};
