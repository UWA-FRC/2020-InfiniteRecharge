#pragma once

#include <string>

#include "control/PIDController.h"
#include "Drivetrain.h"
#include "strategy/Strategy.h"
#include "vision/Receiver.h"

namespace strategies {
  namespace drivetrain {
    class Autoaim : public wml::Strategy {
     public:
      Autoaim(wml::Drivetrain *drivetrain, wml::vision::Receiver *visionReceiver, wml::control::PIDGains gains, std::string name = "<Drivetrain Manual Strategy>") : Strategy(name), _drivetrain(drivetrain), _visionReceiver(visionReceiver), _controller(gains) {
        Requires(drivetrain);
        SetCanBeInterrupted(true);
      };

      virtual void OnUpdate(double dt) override;

      virtual void OnStart() override { OnChange(); };
      virtual void OnStop() override { OnChange(); };

      void SetIsDoneThreshold(double threshAvgPos, double threshAvgVel) { _controller.SetIsDoneThreshold(threshAvgPos, threshAvgVel); };
      bool IsDone() { return _controller.IsDone(); };

     protected:
      virtual void OnChange() { _drivetrain->Set(0, 0); };

      wml::Drivetrain *_drivetrain;
      wml::vision::Receiver *_visionReceiver;
      wml::control::PIDController _controller;
    };
  }
}
