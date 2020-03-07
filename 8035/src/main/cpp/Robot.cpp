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
  intakeManualStrategy = std::make_shared<strategies::intake::Manual>(intake, &robotmap.controllers);
  intake->SetDefault(intakeManualStrategy);
  StrategyController::Register(intake); NTProvider::Register(intake);

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

void Robot::TeleopInit() {
  drivetrain->Set(0, 0);
  intake->SetStowed();
  robotmap.indexer.indexerGearbox.transmission->SetVoltage(0);
  robotmap.shooter.shooterGearbox.transmission->SetVoltage(0);
  climber->SetHold();
}

void Robot::TeleopPeriodic() {
  // Drivebase Controlling
#if DRIVING_ENABLED
  double left = robotmap.controllers.Get(ControlMap::Drivebase::LEFT), right = robotmap.controllers.Get(ControlMap::Drivebase::RIGHT);
  drivetrain->Set(
    left * std::fabs(left) * ControlMap::Drivebase::THROTTLE,
    right * std::fabs(right) * ControlMap::Drivebase::THROTTLE
  );
#endif

  // Intake Controlling
  if (intake->GetActiveStrategy() == intakeManualStrategy && robotmap.pdp.GetCurrent(*intake->GetConfig().motors.transmission) > ControlMap::Intake::EJECT_CURRENT) {
  }

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
