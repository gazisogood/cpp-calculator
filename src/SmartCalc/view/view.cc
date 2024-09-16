#include "view.h"

#include "controller/controller.h"
#include "model/model.h"
#include "ui_view.h"

View::View(QWidget *parent, s21::Controller *controller)
    : QMainWindow(parent), controller_(controller), ui(new Ui::View) {
  ui->setupUi(this);

  connect(ui->num_zero, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
  connect(ui->num_one, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
  connect(ui->num_two, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
  connect(ui->num_three, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
  connect(ui->num_four, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
  connect(ui->num_five, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
  connect(ui->num_six, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
  connect(ui->num_seven, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
  connect(ui->num_eight, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
  connect(ui->num_nine, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
  connect(ui->exponent, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
  connect(ui->add, SIGNAL(clicked()), this, SLOT(arithmetics_clicked()));
  connect(ui->div, SIGNAL(clicked()), this, SLOT(arithmetics_clicked()));
  connect(ui->mult, SIGNAL(clicked()), this, SLOT(arithmetics_clicked()));
  connect(ui->sub, SIGNAL(clicked()), this, SLOT(arithmetics_clicked()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(arithmetics_clicked()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(trigonometry_clicked()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(trigonometry_clicked()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(trigonometry_clicked()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(trigonometry_clicked()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(trigonometry_clicked()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(trigonometry_clicked()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(trigonometry_clicked()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(trigonometry_clicked()));

  display = ui->label;
}

View::~View() { delete ui; }

QString View::getDisplayText() { return display->text(); }
int View::getDisplayLength() { return display->text().length(); }
std::string View::getMainData() { return ui->label->text().toStdString(); }
std::string View::getXData() {
  if (ui->label_x->text() == "") ui->label_x->setText("0");
  return ui->label_x->text().toStdString();
}
int View::checkDataLength() { return ui->label->text().length(); }

void View::setLabelFontSize() {
  QString text = ui->label->text();
  int length = text.length();
  int fontSize = 45;
  if (length > 10 && length <= 13) {
    fontSize = 35;
  } else if (length > 13 && length <= 15) {
    fontSize = 30;
  } else if (length > 15) {
    fontSize = 25;
  }
  QFont font = ui->label->font();
  font.setPointSize(fontSize);
  ui->label->setFont(font);
}

// clear
void View::on_all_clear_clicked() {
  display->clear();
  arithmetic_clicked = false;
  dot_clicked = false;
  number_clicked = false;
  x_button_clicked = false;
  need_clear_display = false;
  pow_clicked = false;
  exp_clicked = false;
  open_bracket_clicked = 0;
  close_bracket_clicked = 0;
  setLabelFontSize();
}

void View::on_backspace_clicked() {
  if (need_clear_display) on_all_clear_clicked();
  QString str = getDisplayText();
  if (getDisplayLength()) {
    QString lastThreeChars = str.right(3);
    QString lastFourChars = str.right(4);
    QString lastFiveChars = str.right(5);
    if (getDisplayLength() >= 3) {
      lastThreeChars = str.right(3);
    } else if (getDisplayLength() >= 4) {
      lastFourChars = str.right(4);
    } else if (getDisplayLength() >= 5) {
      lastFiveChars = str.right(5);
    }
    if (str.back() == '.') {
      str.chop(1);
      dot_clicked = false;
    } else if (str.back() == 'e') {
      str.chop(1);
      exp_clicked = false;
    } else if (lastFiveChars == "asin(" || lastFiveChars == "acos(" ||
               lastFiveChars == "atan(" || lastFiveChars == "sqrt(") {
      str.chop(5);
      open_bracket_clicked--;
    } else if (lastFourChars == "sin(" || lastFourChars == "cos(" ||
               lastFourChars == "tan(" || lastFourChars == "log(") {
      str.chop(4);
      open_bracket_clicked--;
    } else if (lastThreeChars == "ln(") {
      str.chop(3);
      open_bracket_clicked--;
    } else if (lastThreeChars == "mod") {
      str.chop(3);
    } else if (str.back() == '(') {
      str.chop(1);
      open_bracket_clicked--;
      number_clicked = true;
    } else if (str.back() == ')') {
      str.chop(1);
      close_bracket_clicked--;
      number_clicked = true;
    } else if (str.back() == 'x') {
      str.chop(1);
      x_button_clicked = false;
    } else if (str.back() == '^') {
      str.chop(1);
      pow_clicked = false;
    } else if (str.back() == '+' || str.back() == '-' || str.back() == '*' ||
               str.back() == '/') {
      str.chop(1);
      arithmetic_clicked = false;
      number_clicked = true;
    } else if (getDisplayLength()) {
      str.chop(1);
      number_clicked = false;
    }
    if (str.length() != 0 && str.back() >= '0' && str.back() <= '9') {
      number_clicked = true;
    }
  }
  need_clear_display = false;
  display->setText(str);
  setLabelFontSize();
}

// numbers
void View::numbers_clicked() {
  if (need_clear_display) on_all_clear_clicked();
  if (!x_button_clicked) {
    QPushButton *numbersButton = (QPushButton *)sender();
    if (numbersButton->text() == 'e' && !exp_clicked && number_clicked) {
      QString result = getDisplayText();
      display->setText(result + numbersButton->text());
      exp_clicked = true;
      pow_clicked = false;
      need_clear_display = false;
    } else if (numbersButton->text() != 'e') {
      QString result = getDisplayText();
      display->setText(result + numbersButton->text());
      number_clicked = true;
      pow_clicked = false;
      need_clear_display = false;
    }
  }
  setLabelFontSize();
}

// arithmetics
void View::arithmetics_clicked() {
  if (need_clear_display) on_all_clear_clicked();
  if (!x_display_clicked) {
    QPushButton *arithmeticsButton = (QPushButton *)sender();
    QString result = getDisplayText();
    if (getDisplayLength()) {
      QString is_mod = result.right(3);
      if (result.back() == '(') {
        if (arithmeticsButton->text() == '+' ||
            arithmeticsButton->text() == '-') {
          display->setText(result + arithmeticsButton->text());
          arithmetic_clicked = true;
          dot_clicked = false;
          x_button_clicked = false;
          number_clicked = false;
          exp_clicked = false;
          need_clear_display = false;
        }
      } else if (result.back() != '-' && result.back() != '+' &&
                 result.back() != '/' && result.back() != '*' &&
                 is_mod != "mod" && result.back() != '^') {
        display->setText(result + arithmeticsButton->text());
        arithmetic_clicked = true;
        dot_clicked = false;
        x_button_clicked = false;
        number_clicked = false;
        exp_clicked = false;
        need_clear_display = false;
      }
    } else if (arithmeticsButton->text() == '-' ||
               arithmeticsButton->text() == '+') {
      display->setText(result + arithmeticsButton->text());
      arithmetic_clicked = true;
      x_button_clicked = false;
      number_clicked = false;
      exp_clicked = false;
      need_clear_display = false;
    }
  }
  setLabelFontSize();
}

// trigonometry
void View::trigonometry_clicked() {
  if (need_clear_display) on_all_clear_clicked();
  if (!x_display_clicked) {
    QPushButton *trigonometryButton = (QPushButton *)sender();
    QString result;
    if (!checkDataLength()) {
      result = (display->text() + trigonometryButton->text() + "(");
    } else if (ui->label->text().back() >= '0' &&
                   ui->label->text().back() <= '9' ||
               ui->label->text().back() == 'x') {
      result = (display->text() + "*" + trigonometryButton->text() + "(");
    } else {
      result = (display->text() + trigonometryButton->text() + "(");
    }
    display->setText(result);
    open_bracket_clicked++;
    dot_clicked = false;
    x_button_clicked = false;
    number_clicked = false;
    exp_clicked = false;
    need_clear_display = false;
    pow_clicked = false;
  }
  setLabelFontSize();
}

void View::on_sqrt_clicked() {
  if (need_clear_display) on_all_clear_clicked();
  QString result;
  if (!x_display_clicked) {
    if (!checkDataLength()) {
      result = display->text() + "sqrt(";
    } else if (ui->label->text().back() >= '0' &&
                   ui->label->text().back() <= '9' ||
               ui->label->text().back() == 'x') {
      result = display->text() + "*sqrt(";
    } else {
      result = display->text() + "sqrt(";
    }
    display->setText(result);
    open_bracket_clicked++;
    dot_clicked = false;
    x_button_clicked = false;
    number_clicked = false;
    exp_clicked = false;
    need_clear_display = false;
  }
  setLabelFontSize();
}

void View::on_pow_clicked() {
  if (need_clear_display) on_all_clear_clicked();
  if (!x_display_clicked) {
    if (!pow_clicked && (number_clicked || x_button_clicked)) {
      display->setText(display->text() + "^");
      pow_clicked = true;
      dot_clicked = false;
      x_button_clicked = false;
      number_clicked = false;
      exp_clicked = false;
      need_clear_display = false;
    }
  }
  setLabelFontSize();
}

void View::on_point_clicked() {
  if (need_clear_display) {
    on_all_clear_clicked();
  }
  if (!dot_clicked && !x_button_clicked) {
    display->setText(display->text() + ".");
    dot_clicked = true;
    arithmetic_clicked = false;
    need_clear_display = false;
  }
  setLabelFontSize();
}

void View::on_brackets_clicked() {
  if (need_clear_display) on_all_clear_clicked();
  if (!x_display_clicked) {
    QString str = display->text();
    if (!getDisplayLength()) {
      display->setText("(");
      open_bracket_clicked++;
      x_button_clicked = false;
      number_clicked = false;
      exp_clicked = false;
      need_clear_display = false;
    } else if (str.back() == '+' || str.back() == '-' || str.back() == '*' ||
               str.back() == '/' || str.back() == '^' || str.back() == '(') {
      display->setText(display->text() + "(");
      open_bracket_clicked++;
      x_button_clicked = false;
      number_clicked = false;
      exp_clicked = false;
      need_clear_display = false;
    } else if ((str.back() >= '0' && str.back() <= '9' || str.back() == ')' ||
                str.back() == '.' || str.back() == 'x') &&
               (open_bracket_clicked > close_bracket_clicked)) {
      display->setText(display->text() + ")");
      close_bracket_clicked++;
      need_clear_display = false;
    } else if (open_bracket_clicked == close_bracket_clicked) {
      display->setText(display->text() + "*(");
      open_bracket_clicked++;
      x_button_clicked = false;
      number_clicked = false;
      exp_clicked = false;
      need_clear_display = false;
    }
  }
  setLabelFontSize();
}

void View::on_button_x_clicked() {
  if (need_clear_display) on_all_clear_clicked();
  if (!x_display_clicked) {
    if (!x_button_clicked && !number_clicked) {
      display->setText(display->text() + "x");
      x_button_clicked = true;
    }
  }
  need_clear_display = false;
  setLabelFontSize();
}

void View::on_x_display_button_clicked() {
  if (!x_display_clicked) {
    setDisplayStylesheet();
    display = ui->label_x;
    x_display_clicked = true;
    x_button_clicked = false;
    dot_clicked = false;
    number_clicked = false;
    exp_clicked = false;
  } else if (x_display_clicked) {
    setDisplayStylesheet();
    display = ui->label;
    x_display_clicked = false;
    dot_clicked = false;
    number_clicked = false;
    exp_clicked = false;
  }
}

void View::setResult(long double result) {
  if (controller_->getReturnCode() == s21::ReturnCode::kIncorrectInput) {
    ui->label->setText("Incorrect input");
    if (ui->label_x->text() == "0") {
      ui->label_x->setText("");
    }
    need_clear_display = true;
  } else if (controller_->getReturnCode() ==
             s21::ReturnCode::kCalculationError) {
    ui->label->setText("Calculation error");
    if (ui->label_x->text() == "0") {
      ui->label_x->setText("");
    }
    need_clear_display = true;
  } else {
    long double checkRemainder = trunc(result);
    long double returnValue = result - checkRemainder;
    if (returnValue != 0) {
      QString resultString = QString::number(result, 'L', 7);
      if (resultString.length() > 19) {
        resultString = QString::number(result, 'e', 7);
      }
      ui->label->setText(resultString);
      dot_clicked = true;
      number_clicked = true;
    } else {
      QString resultString = QString::number(result, 'L', 0);
      if (resultString.length() > 19) {
        resultString = QString::number(result, 'e');
      }
      ui->label->setText(resultString);
      if (ui->label->text() == '0') {
        need_clear_display = true;
      }
      number_clicked = true;
    }
    if (ui->label_x->text() == "0") {
      ui->label_x->setText("");
    }
  }
}

void View::on_equal_clicked() {
  if (need_clear_display) on_all_clear_clicked();
  if (checkDataLength()) {
    if (number_clicked || x_button_clicked) {
      setResult(controller_->Calculate(getMainData(), getXData()));
    }
  }
  setLabelFontSize();
}

void View::on_graph_triggered() {
  graphic = new Graph(this);
  graphic->disp = ui->label;
  graphic->show();
}

void View::setDisplayStylesheet() {
  if (!x_display_clicked) {
    ui->x_display_button->setStyleSheet(
        "QPushButton {"
        "background-color: #b7c0c7;"
        "border:none;"
        "border-radius:20px;"
        "color:#46494C;"
        "}"
        "QPushButton:hover {"
        "background-color: #bdcddb;"
        "border:none;"
        "border-radius:20px;"
        "color:#46494C;"
        "}");
    ui->label->setStyleSheet(
        "border-bottom-left-radius:25px;"
        "border-bottom-right-radius:25px;"
        "padding:10px;"
        "color:#353535;"
        "background-color:#ccd7de;");
    ui->label_x->setStyleSheet(
        "background-color:#dae4ed;"
        "color:#353535;"
        "border-radius:20px;"
        "padding:10px;");
  } else {
    ui->x_display_button->setStyleSheet(
        "QPushButton {"
        "background-color: #bdcddb;"
        "border:none;"
        "border-radius:20px;"
        "color:#787878;"
        "}"
        "QPushButton:hover {"
        "background-color: #b7c0c7;"
        "border:none;"
        "border-radius:20px;"
        "color:#46494C;"
        "}");
    ui->label->setStyleSheet(
        "border-bottom-left-radius:25px;"
        "border-bottom-right-radius:25px;"
        "padding:10px;"
        "color:#353535;"
        "background-color:#dae4ed;");
    ui->label_x->setStyleSheet(
        "background-color:#ccd7de;"
        "color:#353535;"
        "border-radius:20px;"
        "padding:10px;");
  }
}
