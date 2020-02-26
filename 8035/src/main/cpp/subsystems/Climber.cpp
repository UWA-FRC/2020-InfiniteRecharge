#include "subsystems/Climber.h"

#include <cmath>

using namespace wml::actuators;

// public

std::string Climber::GetStateString() {
  switch (GetState()) {
   case ClimberState::kStationary:
    return "kStationary";
    
   case ClimberState::kManual:
    return "kManual";
    
   case ClimberState::kWinching:
    return "kWinching";

   case ClimberState::kSetpoint:
    return "kSetpoint";
  }

  return "<state error>";
}


void Climber::SetManual(double power) {
  SetState(ClimberState::kManual);
  _SetSetpoint(power * 12);
}

void Climber::SetWinching(double power) {
  SetState(ClimberState::kWinching);
  _SetSetpoint(-std::abs(power) * 12);
}

void Climber::SetSetpoint(double setpoint) {
  SetState(ClimberState::kSetpoint);
  _SetSetpoint(setpoint);
}

void Climber::SetHold() {
  SetState(ClimberState::kStationary);
}


double Climber::GetSetpoint() {
  return _setpoint;
}

void Climber::_SetSetpoint(double setpoint) {
  _setpoint = setpoint;
}

// double Climber::GetHeight() {
//   double radius = _config.spoolRadius;
//   double rotations = _config.spool.encoder->GetEncoderRotations();
//   double height = 6.283 * radius * rotations;
//   return height;
// }

ClimberConfig &Climber::GetConfig() { return _config; }

// virtual

void Climber::OnStatePeriodic(ClimberState state, double dt) {
  double voltage = 0;

  if (state == ClimberState::kSetpoint) if (GetSetpoint() < 0) SetHold();
  
  switch (state) {
   case ClimberState::kManual:
    voltage = GetSetpoint();
    GetConfig().ratchetLock.SetTarget(kReverse);
    break;

   case ClimberState::kStationary:
    voltage = 0;
    break;

   case ClimberState::kSetpoint:
    voltage = 1;
    _SetSetpoint(GetSetpoint() - dt);
    GetConfig().ratchetLock.SetTarget(kReverse);
    break;

   case ClimberState::kWinching:
    voltage = -std::abs(GetSetpoint());
    GetConfig().ratchetLock.SetTarget(kForward);
  }

  voltage = std::min(12.0, std::max(-12.0, voltage));

  GetConfig().elevator.transmission->SetVoltage(voltage * (voltage > 0 ? GetConfig().raising_throttle : GetConfig().lowering_throttle));                                         // NEED TO ACCOUNT FOR GEARBOX RATIO
  if (state == ClimberState::kWinching) { GetConfig().winch.transmission->SetVoltage(voltage * GetConfig().winch_throttle); }  // NEED TO ACCOUNT FOR GEARBOX RATIO

  GetConfig().ratchetLock.Update(dt);
}
