#include "strategies/drivetrain/Manual.h"

#include "ControlMap.h"

using namespace strategies::drivetrain;

void Manual::OnUpdate(double dt) {
  double left = _contGroup.Get(ControlMap::Drivebase::LEFT);
  double right = _contGroup.Get(ControlMap::Drivebase::RIGHT);

  drivetrain->Set(
    left * std::fabs(left) * ControlMap::Drivebase::THROTTLE,
    right * std::fabs(right) * ControlMap::Drivebase::THROTTLE
  );
}
