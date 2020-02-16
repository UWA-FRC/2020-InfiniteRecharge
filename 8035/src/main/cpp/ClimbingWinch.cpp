#include "ClimbingWinch.cpp"

std::string GetStateString() {
  switch (GetState()) {
    case WinchStates::kUnlocked:
      return "kUnlocked";
    case WinchStates::kLocked:
      return "kLocked";
    case WinchStates::kClimbing:
      return "kClimbing";
    case WinchStates::kLocking:
      return "kLocking";
    case WinchStates::kUnlocking:
      return "kUnlocking";
    default:
      return "No valid state found!";
  }
}

void SetUnlocked() {
  switch (GetState()) {
    case WinchStates::kClimbing:
      SetLocked();
      break;
    case WinchStates::kLocked:
      SetState(WinchStates::kUnlocking);
      break;
  }
}

void SetLocked() {
  SetState(WinchStates::kLocking);
}

void SetClimbing(double speed) {
  switch (GetState()) {
    case WinchStates::kUnlocked:
      SetLocked();
      break;
    case WinchStates::kLocked:
      _climbingSpeed = speed;
      SetState(WinchStates::kClimbing);
      break;
  }
}

void OnStatePeriodic(WinchStates state, double dt) {
  double climbingTarget = 0;

  switch (state) {
    case WinchStates::kUnlocking:
      lockingServo->SetTarget(lockingServo.kForward);
      break;
    case WinchStates::kLocking:
      lockingServo->SetTarget(lockingServo.kReverse);
      break;
    case WinchStates::kClimbing:
      climbingTarget = _climbingSpeed;
      break;
  }

  winchGearbox.transmission->SetVoltage(climbingTarget);
  lockingServo->Update(dt);
}
