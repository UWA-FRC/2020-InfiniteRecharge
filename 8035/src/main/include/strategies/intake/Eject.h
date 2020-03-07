#pragma once

#include <string>

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"

#include "ControlMap.h"
#include "subsystems/RollerIntake.h"

namespace strategies {
  namespace intake {
    class Eject : public wml::Strategy {
     public:
      Eject(RollerIntake *intake, double duration, std::string name = "<Intake Eject Strategy>") : Strategy(name), _intake(intake), _duration(duration) {
        SetCanBeInterrupted(false);
        SetCanBeReused(false);

        _dt = 0;
      };

      virtual void OnUpdate(double dt) override;

     protected:
      RollerIntake *_intake;
      double _duration;
      double _dt;
    };
  }
}
