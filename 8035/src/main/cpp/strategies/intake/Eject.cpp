#include "strategies/intake/Eject.h"

using namespace strategies::intake;

void Eject::OnUpdate(double dt) {
  _intake->SetOuttaking();
  _dt += dt;
  if (_dt >= _duration) SetDone();
}
