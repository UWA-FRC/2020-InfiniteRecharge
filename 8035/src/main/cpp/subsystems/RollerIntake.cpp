#include "subsystems/RollerIntake.h"

using namespace subsystems;

void RollerIntake::IntakingPeriodic() {
  _config.motors.transmission->SetVoltage(12 * _config.intakingThrottle);
}

void RollerIntake::OuttakingPeriodic() {
  _config.motors.transmission->SetVoltage(-12 * _config.outtakingThrottle);
}

void RollerIntake::DeployingPeriodic() {
  _config.motors.transmission->SetVoltage(0);
}

void RollerIntake::StowingPeriodic() {
  _config.motors.transmission->SetVoltage(0);
}

void RollerIntake::StowedPeriodic() {
  _config.motors.transmission->SetVoltage(0);
}
