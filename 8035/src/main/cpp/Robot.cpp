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

  // Climber Setup
  climber = new Climber(robotmap.climber.config);
  StrategyController::Register(climber); NTProvider::Register(climber);


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
  // Drivebase Controlling
  drivetrain->Set(
    robotmap.controllers.Get(ControlMap::Drivebase::LEFT) * ControlMap::Drivebase::THROTTLE,
    robotmap.controllers.Get(ControlMap::Drivebase::RIGHT) * ControlMap::Drivebase::THROTTLE
  );

  // Intake Controlling
  if      (robotmap.controllers.Get(ControlMap::Intake::IN))    intake->SetIntaking();
  else if (robotmap.controllers.Get(ControlMap::Intake::OUT))   intake->SetOuttaking();
  else if (robotmap.controllers.Get(ControlMap::Intake::STOW))  intake->SetStowed();

  // Loader Controlling
  if (robotmap.controllers.Get(ControlMap::Loader::TOGGLE, ButtonMode::ONRISE)) loaderState = !loaderState;

  // Shooter Controlling
  // - WIP -

  // Climber Controlling
  double climberLower = robotmap.controllers.Get(ControlMap::Climber::LOWER);
  if (climberLower > ControlMap::AXIS_DEADZONE) {
    if (climber->GetState() == ClimberState::kWinching)
          climber->SetWinching(climberLower);
    else  climber->SetManual(robotmap.controllers.Get(ControlMap::Climber::RAISE) - climberLower);
  } else {
    if        (robotmap.controllers.Get(ControlMap::Climber::TOGGLE_RATCHET, ButtonMode::ONFALL))   climber->SetWinching(0);
    else if   (robotmap.controllers.Get(ControlMap::Climber::PRESET, ButtonMode::ONFALL))           climber->SetSetpoint(ControlMap::Climber::PRESET_SETPOINT);
  }
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
