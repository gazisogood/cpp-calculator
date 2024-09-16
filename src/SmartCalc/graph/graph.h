#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QLabel>
#include <QRegularExpressionValidator>

#include "model/model.h"
#include "qcustomplot.h"

namespace Ui {
class Graph;
}

class Graph : public QDialog, public s21::Model {
  Q_OBJECT

 public:
  explicit Graph(QWidget* parent = nullptr);
  ~Graph();
  QLabel* disp;

  std::string getData() const { return disp->text().toStdString(); }
  void CalcGraphic(double x_begin, double x_end);

 private slots:
  void on_draw_graph_clicked();

 private:
  bool DataNotEmpty() const { return !disp->text().isEmpty(); }
  void setDefinitionValues();

  Ui::Graph* ui;
  double x_min_ = 0;
  double x_max_ = 5;
  double y_min_ = 0;
  double y_max_ = 5;
  QVector<double> x_;
  QVector<double> y_;
};

#endif  // GRAPH_H
