#include "ControlMap.h"

#include "controllers/Controllers.h"

using namespace wml::controllers;
using namespace ControlMap;


const double ControlMap::AXIS_DEADZONE = 0.1;


const tAxis Drivebase::LEFT     = { DRIVER, XboxController::kLeftYAxis };
const tAxis Drivebase::RIGHT    = { DRIVER, XboxController::kRightYAxis };

const double Drivebase::THROTTLE = 1;


const tButtonList Intake::IN    = { { CODRIVER, XboxController::kA } };
const tButtonList Intake::OUT   = { { CODRIVER, XboxController::kY } };
const tButtonList Intake::STOW  = { { CODRIVER, XboxController::kX } };

const double Intake::Throttles::INTAKING    = 0.8;
const double Intake::Throttles::OUTTAKING   = 0.5;


const tAxis Indexer::SPEED = { CODRIVER, XboxController::kLeftYAxis };

const double Indexer::THROTTLE = 0.4;


const tButtonList Shooter::FIRE = { { CODRIVER, XboxController::kStart } };

const double Shooter::THROTTLE = 0.25;


const tAxis Climber::RAISE = { CODRIVER, XboxController::kRightThrottle };
const tAxis Climber::LOWER = { CODRIVER, XboxController::kLeftThrottle };

const tButtonList Climber::TOGGLE_RATCHET   = { { CODRIVER, XboxController::kBumperLeft } };
const tButtonList Climber::PRESET           = { { CODRIVER, XboxController::kBumperRight } };

const double Climber::PRESET_SETPOINT = 1; // in seconds

const double Climber::Throttles::RAISING    = 0.7;
const double Climber::Throttles::LOWERING   = 0.7;
const double Climber::Throttles::WINCH      = 1;
