#pragma once

#include "controllers/Inputs.h"

namespace wml::controllers { typedef std::vector<tButton> tButtonList; }

namespace ControlMap {
  const int DRIVER = 1;
  const int CODRIVER = 2;

  extern const double AXIS_DEADZONE;

  namespace Drivebase {
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

  namespace Loader {
    extern const wml::controllers::tButtonList TOGGLE;

    extern const double THROTTLE;
  }

  namespace Shooter {
    extern const wml::controllers::tButtonList FIRE;

    // extern const int 
  }

  namespace Climber {
    extern const wml::controllers::tAxis        RAISE;
    extern const wml::controllers::tAxis        LOWER;

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
