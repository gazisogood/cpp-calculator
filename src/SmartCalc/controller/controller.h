#ifndef CPP3_SMARTCALC_V2_0_1_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_CONTROLLER_H

#include "model/model.h"

class View;

namespace s21 {
class Controller {
 public:
  Controller(Model *m = nullptr) : model_(m) {}
  ~Controller() {}

  ReturnCode getReturnCode() { return model_->getCalculationCode(); }
  double Calculate(const std::string &main_data, const std::string &x_data);

 private:
  Model *model_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_CONTROLLER_H
