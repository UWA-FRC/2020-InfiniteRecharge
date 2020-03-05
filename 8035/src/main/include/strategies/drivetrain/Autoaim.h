#pragma once

#include <string>

#include "Drivetrain.h"
#include "strategy/Strategy.h"
#include "vision/Receiver.h"

namespace strategies {
  namespace drivetrain {
    class Autoaim : public wml::Strategy {
     public:
      Autoaim(wml::Drivetrain *drivetrain, wml::vision::Receiver *visionReceiver, std::string name = "<Drivetrain Manual Strategy>") : Strategy(name), _drivetrain(drivetrain), _visionReceiver(visionReceiver) {
        Requires(drivetrain);
        SetCanBeInterrupted(true);  
      };

      virtual void OnUpdate(double dt) override;

      virtual void OnStart() override { OnChange(); };
      virtual void OnStop() override { OnChange(); };

     protected:
      virtual void OnChange() { _drivetrain->Set(0, 0); };

      wml::Drivetrain *_drivetrain;
      wml::vision::Receiver *_visionReceiver;
    };
  }
}
