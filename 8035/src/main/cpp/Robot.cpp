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
  drivetrain->GetConfig().leftDrive.transmission->SetInverted(true);

  // StrategyController::Register(drivetrain);
  // NTProvider::Register(drivetrain);
}

using state = actuators::BinaryActuatorState;

void Robot::RobotPeriodic() {
  double dt = Timer::GetFPGATimestamp() - lastTimestamp;
  lastTimestamp = Timer::GetFPGATimestamp();
  // robotmap.contGroup.Update(); // update selectors, etc. [OPTIONAL]

  // if (robotmap.contGroup.Get(ControlMap::compressorOn, controllers::Controller::ONRISE))
  robotmap.controlSystem.compressor.SetTarget(state::kForward);

  robotmap.controlSystem.compressor.Update(dt);

  StrategyController::Update(dt);
  NTProvider::Update();
}

void Robot::DisabledInit() {
  InterruptAll(true);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  double leftPower = -robotmap.xbox.GetAxis(robotmap.xbox.kLeftYAxis);
  double rightPower = -robotmap.xbox.GetAxis(robotmap.xbox.kRightYAxis);

  drivetrain->Set(leftPower, rightPower);
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
