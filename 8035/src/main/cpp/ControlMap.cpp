#include "ControlMap.h"

#include "controllers/Controllers.h"

using namespace wml::controllers;
using namespace ControlMap;


const tButton Intake::IN    = { DRIVER, XboxController::kA };
const tButton Intake::OUT   = { DRIVER, XboxController::kB };
const tButton Intake::STOW  = { DRIVER, XboxController::kX };

const double Intake::intakingThrottle   = 0.6;
const double Intake::outtakingThrottle  = 0.4;


const tButton Loader::TOGGLE = { DRIVER, XboxController::kY };

const double Loader::throttle = 0.4;
