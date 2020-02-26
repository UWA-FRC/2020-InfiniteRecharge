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
  robotmap.drivetrain.config.leftDrive.transmission->SetInverted(true);
  drivetrain = new Drivetrain(robotmap.drivetrain.config);
  /*StrategyController::Register(drivetrain);*/ NTProvider::Register(drivetrain); robotmap.updateGroup += drivetrain;

  // Intake Setup
  intake = new RollerIntake(robotmap.intake.config);
  /*StrategyController::Register(intake);*/ NTProvider::Register(intake); robotmap.updateGroup += intake;

  // Indexer Setup
  robotmap.indexer.indexerGearbox.transmission->SetInverted(true);

  // Shooter Setup
  robotmap.shooter.shooterGearbox.transmission->SetInverted(true);

  // Climber Setup
  robotmap.climber.climberElevatorGearbox.transmission->SetInverted(true);
  robotmap.climber.climberWinchGearbox.transmission->SetInverted(true);
  climber = new Climber(robotmap.climber.config);
  /*StrategyController::Register(climber);*/ NTProvider::Register(climber); robotmap.updateGroup += climber;


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
#if DRIVING_ENABLED
  drivetrain->Set(
    robotmap.controllers.Get(ControlMap::Drivebase::LEFT) * ControlMap::Drivebase::THROTTLE,
    robotmap.controllers.Get(ControlMap::Drivebase::RIGHT) * ControlMap::Drivebase::THROTTLE
  );
#endif

  // Intake Controlling
  if      (robotmap.controllers.Get(ControlMap::Intake::IN))    intake->SetIntaking();
  else if (robotmap.controllers.Get(ControlMap::Intake::OUT))   intake->SetOuttaking();
  else if (robotmap.controllers.Get(ControlMap::Intake::STOW))  intake->SetStowed();

  // Indexer Controlling
  robotmap.indexer.indexerGearbox.transmission->SetVoltage(
    robotmap.controllers.Get(ControlMap::Indexer::SPEED) * ControlMap::Indexer::THROTTLE * 12
  );

  // Shooter Controlling
  double shooterVoltage = 0;
#if SHOOTER_TOGGLE_MODE
  if (robotmap.controllers.Get(ControlMap::Shooter::FIRE, ControlMap::DEFAULT_BUTTON_MODE)) shooterToggle = !shooterToggle;
  if (shooterToggle) shooterVoltage = 12;
#else
  shooterVoltage = robotmap.controllers.Get(ControlMap::Shooter::FIRE) * 12;
#endif
  robotmap.shooter.shooterGearbox.transmission->SetVoltage(shooterVoltage * ControlMap::Shooter::THROTTLE);

  // Climber Controlling
  double climberLower = robotmap.controllers.Get(ControlMap::Climber::LOWER);
  double climberRaise = robotmap.controllers.Get(ControlMap::Climber::RAISE);
  if (std::abs(climberLower) + std::abs(climberRaise) > ControlMap::AXIS_DEADZONE) {
    double climberDiff = climberRaise - climberLower;
    if ((climber->GetState() == ClimberState::kWinching) && (climberDiff < 0)) {
      climber->SetWinching(climberDiff);
    } else {
      climber->SetManual(climberDiff);
    }
  } else {
    if        (robotmap.controllers.Get(ControlMap::Climber::TOGGLE_RATCHET, ControlMap::DEFAULT_BUTTON_MODE))    climber->SetWinching(0);
    else if   (robotmap.controllers.Get(ControlMap::Climber::PRESET, ControlMap::DEFAULT_BUTTON_MODE))            climber->SetSetpoint(ControlMap::Climber::PRESET_SETPOINT);
    else if   (climber->GetState() == ClimberState::kManual)                                                      climber->SetHold();
    else if   (climber->GetState() == ClimberState::kWinching)                                                    climber->SetWinching(0);
  }
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
