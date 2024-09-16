#ifndef VIEW_H
#define VIEW_H

#include <QLabel>
#include <QMainWindow>
#include <cmath>
#include <string>

#include "graph/graph.h"

namespace s21 {
class Controller;
}

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr, s21::Controller *controller = nullptr);
  ~View();

 public:
  QString getDisplayText();
  int getDisplayLength();
  std::string getMainData();
  std::string getXData();

 private slots:
  void on_all_clear_clicked();
  void on_backspace_clicked();
  void numbers_clicked();
  void trigonometry_clicked();
  void arithmetics_clicked();
  void on_sqrt_clicked();
  void on_pow_clicked();
  void on_point_clicked();
  void on_brackets_clicked();
  void on_button_x_clicked();
  void on_x_display_button_clicked();
  void on_equal_clicked();
  void on_graph_triggered();

 private:
  void setResult(long double result);
  void setDisplayStylesheet();
  void setLabelFontSize();
  int checkDataLength();

  bool arithmetic_clicked = false;
  bool dot_clicked = false;
  bool number_clicked = false;
  bool x_button_clicked = false;
  bool x_display_clicked = false;
  bool need_clear_display = false;
  bool pow_clicked = false;
  bool exp_clicked = false;
  int open_bracket_clicked = 0;
  int close_bracket_clicked = 0;

  QLabel *display;
  Graph *graphic;
  Ui::View *ui;

  s21::Controller *controller_;
};
#endif  // VIEW_H
