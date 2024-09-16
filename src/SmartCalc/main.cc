#include <QApplication>

#include "controller/controller.h"
#include "model/model.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  View view(nullptr, &controller);
  view.show();
  view.setWindowTitle("calculator X arboriob");
  return a.exec();
}
