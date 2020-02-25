#pragma once

#include "controllers/Inputs.h"

namespace ControlMap {
  const int DRIVER = 1;
  const int CODRIVER = 2;

  namespace Intake {
    extern const wml::controllers::tButton IN;
    extern const wml::controllers::tButton OUT;
    extern const wml::controllers::tButton STOW;

    extern const double intakingThrottle;
    extern const double outtakingThrottle;
  }

  namespace Loader {
    extern const wml::controllers::tButton TOGGLE;

    extern const double throttle;
  }
} // namespace ControlMap
