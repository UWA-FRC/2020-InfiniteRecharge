#include "Robot.h"

#include <math.h>
#include <iostream>

#include <cameraserver/CameraServer.h>

#include <frc/DriverStation.h>

using namespace frc;
using namespace wml;

double lastTimestamp;

void Robot::RobotInit() {
  lastTimestamp = Timer::GetFPGATimestamp();

  auto camera = CameraServer::GetInstance()->StartAutomaticCapture(0);
  camera.SetFPS(30);
  camera.SetResolution(160, 120);

  drivetrain = new Drivetrain(robotmap.drivetrain.config);

  StrategyController::Register(drivetrain);
  NTProvider::Register(drivetrain);
}

void Robot::RobotPeriodic() {
  // double dt = Timer::GetFPGATimestamp() - lastTimestamp;
  // lastTimestamp = Timer::GetFPGATimestamp();
  // robotmap.contGroup.Update(); // update selectors, etc. [OPTIONAL]

  // Redundant, as it can already be accessed on shuffleboard via nt, but ~
  // frc::SmartDashboard::PutNumber("Hatch Distance", robotmap.controlSystem.hatchDistanceEntry.GetDouble(-1));
  // frc::SmartDashboard::PutNumber("Hatch X Offset", robotmap.controlSystem.hatchXoffsetEntry.GetDouble(0));
  // frc::SmartDashboard::PutNumber("Hatch Y Offset", robotmap.controlSystem.hatchYoffsetEntry.GetDouble(0));
  
  // frc::SmartDashboard::PutNumber("Tape Distance", robotmap.controlSystem.tapeDistanceEntry.GetDouble(-1));
  // frc::SmartDashboard::PutNumber("Tape Angle", robotmap.controlSystem.tapeAngleEntry.GetDouble(0));
  // frc::SmartDashboard::PutNumber("Tape Target", robotmap.controlSystem.tapeTargetEntry.GetDouble(-1));
  

  // if (robotmap.contGroup.Get(ControlMap::compressorOn, controllers::Controller::ONRISE))
  // robotmap.controlSystem.compressor.SetTarget(actuators::BinaryActuatorState::kForward);

  // robotmap.controlSystem.compressor.Update(dt);

  // StrategyController::Update(dt);
  // NTProvider::Update();
  doubleMaster.UpdateOnce();
}

void Robot::DisabledInit() {
  InterruptAll(true);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
