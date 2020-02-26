#pragma once

#include <string>

#include "actuators/BinaryActuator.h"
#include "devices/StateDevice.h"
#include "Gearbox.h"
#include "sensors/BinarySensor.h"
#include "strategy/StrategySystem.h"

struct ClimberConfig {
  wml::Gearbox &winch;
  wml::actuators::BinaryActuator &ratchetLock;

  wml::Gearbox &elevator;

  // SOME WAY TO MEASURE HEIGHT

  double raising_throttle = 1;
  double lowering_throttle = 1;
  double winch_throttle = 1;

  std::string name = "<Climber>";
};

enum class ClimberState { kStationary = 0, kManual, kWinching, kSetpoint };

class Climber : public wml::devices::StateDevice<ClimberState>, public wml::StrategySystem {
 public:
  Climber(ClimberConfig config) : StateDevice(config.name), _config(config), _setpoint(0) {};

  virtual std::string GetStateString() final;

  void SetManual(double power);       // -1 to 1
  void SetWinching(double power);     // -1 to 1 => -1 to 0 (abs-ed)
  void SetSetpoint(double setpoint);  // countdown timer - temp
  void SetHold();

  double GetSetpoint(); // Do we need that?
  // double GetHeight();

  ClimberConfig &GetConfig();

 protected:
  virtual void OnStatePeriodic(ClimberState state, double dt) override;

  void _SetSetpoint(double setpoint);

 private:
  ClimberConfig _config;

  double _setpoint;
};
