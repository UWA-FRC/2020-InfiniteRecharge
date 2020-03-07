#include "strategies/intake/Manual.h"

using namespace strategies::intake;

void Manual::OnUpdate(double dt) {
  if      (_contGroup->Get(ControlMap::Intake::IN))   _intake->SetIntaking();
  else if (_contGroup->Get(ControlMap::Intake::OUT))  _intake->SetOuttaking();
  else if (_contGroup->Get(ControlMap::Intake::STOW)) _intake->SetStowed();
}

bool Manual::IsControlled() {
  if (_contGroup->Get(ControlMap::Intake::IN)) return true;
  if (_contGroup->Get(ControlMap::Intake::OUT)) return true;
  if (_contGroup->Get(ControlMap::Intake::STOW)) return true;

  return false;
}
