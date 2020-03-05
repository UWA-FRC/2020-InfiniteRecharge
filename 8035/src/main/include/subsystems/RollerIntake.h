#pragma once

#include <string>

#include "devices/DeployableDevice.h"
#include "Gearbox.h"
#include "strategy/Strategy.h"
#include "strategy/StrategySystem.h"
#include "Toggle.h"

namespace subsystems {
  using RollerIntakeState = wml::devices::DeployableDeviceState;

  struct RollerIntakeConfig : public wml::devices::DeployableDeviceConfig {
    wml::Gearbox &motors;

    double intakingThrottle;
    double outtakingThrottle;

    RollerIntakeConfig(wml::Gearbox &motorsIn, wml::actuators::BinaryActuator &actuatorIn, double intakingThrottleIn = 1, double outtakingThrottleIn = 1, bool canEjectIn = false, std::string name = "<Box RollerIntake>") :
      wml::devices::DeployableDeviceConfig(actuatorIn, canEjectIn, name),
      motors(motorsIn),
      intakingThrottle(intakingThrottleIn),
      outtakingThrottle(outtakingThrottleIn)
    {};
  };

  class RollerIntake : public wml::devices::DeployableDevice, public wml::StrategySystem {
   public:
    RollerIntake(RollerIntakeConfig config) : DeployableDevice(config), _config(config) {};

    RollerIntakeConfig &GetConfig() { return _config; };

   protected:
    virtual void IntakingPeriodic() override;
    virtual void OuttakingPeriodic() override;
    virtual void DeployingPeriodic() override;
    virtual void StowingPeriodic() override;
    virtual void StowedPeriodic() override;

   private:
    RollerIntakeConfig _config;
  };
} // namespace subsystems
