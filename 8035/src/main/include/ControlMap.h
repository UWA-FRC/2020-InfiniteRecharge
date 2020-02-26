#pragma once

#include "controllers/Inputs.h"

namespace ControlMap {
  const int DRIVER = 1;
  const int CODRIVER = 2;

  extern const double AXIS_DEADZONE;

  namespace Drivebase {
    #define DRIVING_ENABLED true

    extern const wml::controllers::tAxis LEFT;
    extern const wml::controllers::tAxis RIGHT;

    extern const double THROTTLE;
  }

  namespace Intake {
    extern const wml::controllers::tButtonList IN;
    extern const wml::controllers::tButtonList OUT;
    extern const wml::controllers::tButtonList STOW;

    namespace Throttles {
      extern const double INTAKING;
      extern const double OUTTAKING;
    }
  }

  namespace Indexer {
    extern const wml::controllers::tAxis SPEED;

    extern const double THROTTLE;
  }

  namespace Shooter {
    #define SHOOTER_TOGGLE_MODE true

    extern const wml::controllers::tButtonList FIRE;

    extern const double THROTTLE;
  }

  namespace Climber {
    extern const wml::controllers::tAxis        RAISE; // change to button?
    extern const wml::controllers::tAxis        LOWER; // "

    extern const wml::controllers::tButtonList  TOGGLE_RATCHET;
    extern const wml::controllers::tButtonList  PRESET;

    extern const double PRESET_SETPOINT;
    
    namespace Throttles {
      extern const double RAISING;
      extern const double LOWERING;

      extern const double WINCH;
    }
  }
} // namespace ControlMap
