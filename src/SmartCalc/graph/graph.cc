#include "graph.h"

#include "controller/controller.h"
#include "qcustomplot.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QDialog(parent), ui(new Ui::Graph) {
  ui->setupUi(this);

  QRegularExpressionValidator *validator = new QRegularExpressionValidator(
      QRegularExpression("^-?(1000000|[0-9]{1,6}(\\.[0-9]{1,7})?$)"));

  ui->x_min->setValidator(validator);
  ui->x_max->setValidator(validator);
  ui->y_min->setValidator(validator);
  ui->y_max->setValidator(validator);
}

Graph::~Graph() { delete ui; }

void Graph::on_draw_graph_clicked() {
  if (DataNotEmpty()) {
    ui->q_cutom_plot->removeGraph(0);
    ui->q_cutom_plot->replot();

    setDefinitionValues();
    CalcGraphic(x_min_, x_max_);

    ui->q_cutom_plot->xAxis->setRange(x_min_, x_max_);
    ui->q_cutom_plot->yAxis->setRange(y_min_, y_max_);

    ui->q_cutom_plot->addGraph();
    ui->q_cutom_plot->graph(0)->addData(x_, y_);
    ui->q_cutom_plot->replot();
    x_.clear();
    y_.clear();
  }
}

void Graph::setDefinitionValues() {
  x_min_ = ui->x_min->text() != "" ? ui->x_min->text().toDouble() : x_min_;
  x_max_ = ui->x_max->text() != "" ? ui->x_max->text().toDouble() : x_max_;
  y_min_ = ui->y_min->text() != "" ? ui->y_min->text().toDouble() : y_min_;
  y_max_ = ui->y_max->text() != "" ? ui->y_max->text().toDouble() : y_max_;
}

void Graph::CalcGraphic(double x_begin, double x_end) {
  s21::Model model;
  s21::Controller controller_(&model);
  double step = (x_end - x_begin) / 800;
  if (x_begin < x_end) {
    for (double i = x_begin; i <= x_end; i += step) {
      x_.push_back(i);
      y_.push_back(controller_.Calculate(getData(), std::to_string(i)));
    }
  }
}
