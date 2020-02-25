#include "Robot.h"

#include <math.h>
#include <iostream>

#include <cameraserver/CameraServer.h>

#include <frc/DriverStation.h>

using namespace frc;
using namespace wml;
using ButtonMode = wml::controllers::Controller::ButtonMode;

double lastTimestamp;

void Robot::RobotInit() {
  robotmap.updateGroup(); // update the internal timestamp - DON'T REGISTER BEFORE THIS


  auto camera = CameraServer::GetInstance()->StartAutomaticCapture(0);
  camera.SetFPS(30);
  camera.SetResolution(160, 120);

  // Controller Setup
  robotmap.updateGroup += std::bind(&wml::controllers::SmartControllerGroup::Update, &robotmap.controllers);

  // Drivetrain Setup
  drivetrain = new Drivetrain(robotmap.drivetrain.config);
  StrategyController::Register(drivetrain); NTProvider::Register(drivetrain);

  // Intake Setup
  intake = new RollerIntake(robotmap.intake.config);
  StrategyController::Register(intake); NTProvider::Register(intake);

  // Loader Setup
  robotmap.updateGroup += std::bind(&Robot::LoaderUpdate, this);

  // Shooter Setup
  // - WIP -


  robotmap.updateGroup.Register(std::bind(&Robot::StrategyControllerUpdate, this, wml::loops::_dt));
  robotmap.updateGroup.Register(std::bind(&Robot::NTProviderControllerUpdate, this));
}

void Robot::RobotPeriodic() {
  robotmap.updateGroup.UpdateOnce();
}

void Robot::DisabledInit() {
  InterruptAll(true);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  // Intake Controlling
  if (robotmap.controllers.Get(ControlMap::Intake::IN))         intake->SetIntaking();
  else if (robotmap.controllers.Get(ControlMap::Intake::OUT))   intake->SetOuttaking();
  else if (robotmap.controllers.Get(ControlMap::Intake::STOW))  intake->SetStowed();

  // Loader Controlling
  if (robotmap.controllers.Get(ControlMap::Loader::TOGGLE, ButtonMode::ONRISE)) loaderState = !loaderState;

  // Shooter Controlling
  // - WIP -
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
