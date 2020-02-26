#include "ControlMap.h"

#include "controllers/Controllers.h"

using namespace wml::controllers;
using namespace ControlMap;


const tButtonList Intake::IN    = { { DRIVER, XboxController::kA } };
const tButtonList Intake::OUT   = { { DRIVER, XboxController::kB } };
const tButtonList Intake::STOW  = { { DRIVER, XboxController::kX } };

const double Intake::Throttles::INTAKING    = 0.6;
const double Intake::Throttles::OUTTAKING   = 0.4;


const tButtonList Loader::TOGGLE = { { DRIVER, XboxController::kY } };

const double Loader::THROTTLE = 0.4;


const tButtonList Shooter::FIRE = { { DRIVER, XboxController::kStart } };


const tAxis Climber::RAISE = { DRIVER, XboxController::kRightThrottle };
const tAxis Climber::LOWER = { DRIVER, XboxController::kLeftThrottle };

const tButtonList Climber::TOGGLE_RATCHET   = { { DRIVER, XboxController::kBumperLeft } };
const tButtonList Climber::PRESET           = { { DRIVER, XboxController::kBumperRight } };

const double Climber::PRESET_SETPOINT = 1; // in seconds

const double Climber::Throttles::RAISING    = 0.7;
const double Climber::Throttles::LOWERING   = 0.7;
const double Climber::Throttles::WINCH      = 1;
