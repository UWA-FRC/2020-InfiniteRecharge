#pragma once

#include "actuators/BinaryServo.h"
#include "devices/StateDevice.h"
#include "Gearbox.h"

enum class WinchStates {kUnlocked, kLocked, kClimbing, kLocking, kUnlocking};

class ClimbingWinch : public wml::devices::StateDevice<WinchStates> {
 public:
  ClimbingWinch(wml::actuators::BinaryActuator *lockingServo, wml::Gearbox &winchGearbox, std::string name = "Climbing Winch") : StateDevice(name), _gearbox(winchGearbox) {
    _lockingServo = lockingServo;
  };

  virtual std::string GetStateString() final;

  void SetUnlocked();
  void SetLocked();
  void SetClimbing(double speed);

 protected:
  virtual void OnStatePeriodic(WinchStates state, double dt) final;

 private:
  double _climbingSpeed;
  wml::actuators::BinaryActuator *_lockingServo;
  wml::Gearbox &_gearbox;
};
