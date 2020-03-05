#pragma once

#include <string>

#include "Drivetrain.h"
#include "controllers/Controllers.h"
#include "strategy/Strategy.h"

namespace strategies {
  namespace drivetrain {
    class Manual : public wml::Strategy {
     public:
      Manual(wml::Drivetrain *drivetrain, wml::controllers::SmartControllerGroup *contGroup, std::string name = "<Drivetrain Manual Strategy>") : Strategy(name), _drivetrain(drivetrain), _contGroup(contGroup) {
        Requires(drivetrain);
        SetCanBeInterrupted(true);
        SetCanBeReused(true);
      };

      virtual void OnUpdate(double dt) override;

      virtual void OnStart() override { OnChange(); };
      virtual void OnStop() override { OnChange(); };

     protected:
      virtual void OnChange() { _drivetrain->Set(0, 0); };

      wml::Drivetrain *_drivetrain;
      wml::controllers::SmartControllerGroup *_contGroup;
    };
  }
}
