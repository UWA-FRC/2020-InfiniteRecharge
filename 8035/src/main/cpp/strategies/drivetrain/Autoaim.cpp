#include "strategies/drivetrain/Autoaim.h"

using namespace strategies::drivetrain;

void Autoaim::OnUpdate(double dt) {
  double out = _controller.Calculate(_visionReceiver->GetHorizontalDegrees(), dt);

  _drivetrain->Set(out, -out);
}
