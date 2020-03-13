#include "strategies/drivetrain/Manual.h"

#include "ControlMap.h"

using namespace strategies::drivetrain;

void Manual::OnUpdate(double dt) {
  double left = _contGroup->Get(ControlMap::Drivebase::LEFT);
  double right = _contGroup->Get(ControlMap::Drivebase::RIGHT);

  if (std::abs(left) <= ControlMap::AXIS_DEADZONE) left = 0;
  if (std::abs(right) <= ControlMap::AXIS_DEADZONE) right = 0;

  _drivetrain->Set(
    left * std::fabs(left) * ControlMap::Drivebase::THROTTLE,
    right * std::fabs(right) * ControlMap::Drivebase::THROTTLE
  );

  _drivetrain->Update(dt);
}

bool Manual::IsControlled() {
  if (std::fabs(_contGroup->Get(ControlMap::Drivebase::LEFT)) > ControlMap::AXIS_DEADZONE) return true;
  if (std::fabs(_contGroup->Get(ControlMap::Drivebase::RIGHT)) > ControlMap::AXIS_DEADZONE) return true;

  return false;
}
