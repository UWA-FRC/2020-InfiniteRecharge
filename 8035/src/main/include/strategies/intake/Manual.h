#pragma once

#include <string>

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"

#include "ControlMap.h"
#include "subsystems/RollerIntake.h"

namespace strategies {
  namespace intake {
    class Manual : public wml::Strategy {
     public:
      Manual(RollerIntake *intake, wml::controllers::SmartControllerGroup *contGroup, std::string name = "<Intake Manual Strategy>") : Strategy(name), _intake(intake), _contGroup(contGroup) {
        SetCanBeInterrupted(true);
        SetCanBeReused(true);
      };

      virtual void OnUpdate(double dt) override;

      virtual bool IsControlled();

     protected:
      RollerIntake *_intake;
      wml::controllers::SmartControllerGroup *_contGroup;
    };
  }
}
