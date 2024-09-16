#include "controller.h"

double s21::Controller::Calculate(const std::string &main_data,
                                  const std::string &x_data) {
  model_->CalcResult(main_data, x_data);
  return model_->getResult();
}