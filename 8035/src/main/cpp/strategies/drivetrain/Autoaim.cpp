#include "strategies/drivetrain/Autoaim.h"

using namespace strategies::drivetrain;

void Autoaim::OnUpdate(double dt) {
  double out = 0;
  
  if (_visionReceiver->active) out = _controller.Calculate(_visionReceiver->GetHorizontalDegrees(), dt);

  std::cout << "hd: " << (double)_visionReceiver->GetHorizontalDegrees() << std::endl;
  std::cout << "out: " << out << std::endl;
  _drivetrain->Set(out, -out);

  _drivetrain->Update(dt);
}
