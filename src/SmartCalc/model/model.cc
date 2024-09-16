#include "model.h"

#include <cstdlib>
#include <sstream>

void s21::Model::CalcResult(const std::string &mainData,
                            const std::string &xData) {
  CheckCorrectData(mainData, xData);
  if (return_code_ != ReturnCode::kIncorrectInput) {
    ConvertDataToRPN(mainData, xData);
    Calculation();
    result_ = numbers_.top().value;
    if (std::isinf(result_) || std::isnan(result_)) {
      return_code_ = ReturnCode::kCalculationError;
    } else {
      return_code_ = ReturnCode::kOk;
    }
  }
}

void s21::Model::Calculation() {
  while (!reversed_polish_notation_.empty()) {
    Lexeme lexeme = reversed_polish_notation_.front();
    if (lexeme.type == Type::kNumber) {
      numbers_.push(lexeme);
    } else {
      OperandsCalculation();
    }
    reversed_polish_notation_.erase(reversed_polish_notation_.begin());
  }
}

void s21::Model::OperandsCalculation() {
  Lexeme result;
  result.priority = Priority::kPriorityLevel_0;
  result.type = Type::kNumber;
  Lexeme first_operand = getNumber();
  Lexeme second_operand;
  numbers_.pop();
  Priority current_operator_priority =
      reversed_polish_notation_.front().priority;
  if (current_operator_priority != Priority::kPriorityLevel_4 &&
      reversed_polish_notation_.front().value != 'q') {
    second_operand = getNumber();
    numbers_.pop();
  }
  char oper = reversed_polish_notation_.front().value;

  if (oper == '+') {
    result.value = first_operand.value + second_operand.value;
  } else if (oper == '-') {
    result.value = second_operand.value - first_operand.value;
  } else if (oper == '*') {
    result.value = first_operand.value * second_operand.value;
  } else if (oper == '/') {
    result.value = second_operand.value / first_operand.value;
  } else if (oper == 'm') {
    result.value = fmodl(second_operand.value, first_operand.value);
  } else if (oper == '^') {
    result.value = powl(second_operand.value, first_operand.value);
  } else if (oper == 'S') {
    result.value = asinl(first_operand.value);
  } else if (oper == 'C') {
    result.value = acosl(first_operand.value);
  } else if (oper == 'T') {
    result.value = atanl(first_operand.value);
  } else if (oper == 's') {
    result.value = sinl(first_operand.value);
  } else if (oper == 'c') {
    result.value = cosl(first_operand.value);
  } else if (oper == 't') {
    result.value = tanl(first_operand.value);
  } else if (oper == 'L') {
    result.value = log10l(first_operand.value);
  } else if (oper == 'l') {
    result.value = logl(first_operand.value);
  } else if (oper == 'q') {
    result.value = sqrtl(first_operand.value);
  }
  numbers_.push(result);
}

void s21::Model::CheckCorrectData(const std::string &mainData,
                                  const std::string &xData) {
  return_code_ = ReturnCode::kOk;
  int size = 0, x_size = 0, open_bracket = 0, close_bracket = 0;
  for (char i : mainData) {
    if (i == '(') {
      ++open_bracket;
    } else if (i == ')') {
      ++close_bracket;
    }
    ++size;
  }
  for (size_t i = 0; i < xData.size(); ++i) {
    ++x_size;
  }

  if (size > CORRECT_LENGTH || x_size > CORRECT_LENGTH ||
      (open_bracket != close_bracket)) {
    return_code_ = ReturnCode::kIncorrectInput;
  }
}

s21::Lexeme s21::Model::getOperator() {
  Lexeme lexeme;
  lexeme.value = operators_.top().value;
  lexeme.priority = operators_.top().priority;
  lexeme.type = operators_.top().type;
  return lexeme;
}

s21::Lexeme s21::Model::getNumber() {
  Lexeme lexeme;
  lexeme.value = numbers_.top().value;
  lexeme.priority = numbers_.top().priority;
  lexeme.type = numbers_.top().type;
  return lexeme;
}

void s21::Model::ConvertDataToRPN(const std::string &mainData,
                                  const std::string &xData) {
  for (auto it = mainData.begin(); it != mainData.end();) {
    if ((*it >= '0' && *it <= '9') || *it == 'e') {
      NumbersFunction(it);
    } else if (*it == '-' || *it == '+' || *it == '*' || *it == '/' ||
               *it == 'm' || *it == '^') {
      OperatorsFunction(it);
    } else if (*it == 'a' || *it == 's' || *it == 'c' || *it == 't' ||
               *it == 'l') {
      TrigonometryFunction(it);
    } else if (*it == '(') {
      OpenBracketFunction(it);
    } else if (*it == ')') {
      CloseBracketFunction(it);
    } else if (*it == 'x') {
      XValueFunction(it, xData);
    }
  }

  while (!operators_.empty()) {
    Lexeme lexeme;
    lexeme = getOperator();
    reversed_polish_notation_.push_back(lexeme);
    operators_.pop();
  }
}

void s21::Model::NumbersFunction(std::string::const_iterator &it) {
  Lexeme lexeme;
  if (isUnary_ && (*it == '-' || *it == '+')) {
    lexeme.value = 0.0f;
    ++it;
  } else {
    std::string numberStr;
    while (std::isdigit(*it) || *it == '.' || *it == 'e' ||
           (*it == '-' && *(it - 1) == 'e') ||
           (*it == '+' && *(it - 1) == 'e')) {
      numberStr.push_back(*it);
      ++it;
    }
    lexeme.value = std::stold(numberStr);
  }
  lexeme.priority = s21::Priority::kPriorityLevel_0;
  lexeme.type = s21::Type::kNumber;
  reversed_polish_notation_.push_back(lexeme);
  isUnary_ = false;
}

void s21::Model::XValueFunction(std::string::const_iterator &it,
                                const std::string &xData) {
  isUnary_ = true;
  Lexeme lexeme;
  std::string xNumberStr;
  for (char x_it : xData) {
    xNumberStr.push_back(x_it);
  }
  lexeme.value = std::stold(xNumberStr);
  lexeme.priority = s21::Priority::kPriorityLevel_0;
  lexeme.type = s21::Type::kNumber;
  reversed_polish_notation_.push_back(lexeme);
  ++it;
}

void s21::Model::OperatorsFunction(std::string::const_iterator &it) {
  Lexeme lexeme;
  Lexeme previous_lexeme;
  lexeme.value = static_cast<long double>(*it);
  lexeme.type = Type::kOperator;
  int pointer_move = 1;

  if (*it == '-' || *it == '+') {
    lexeme.priority = Priority::kPriorityLevel_1;
    if (isUnary_ && *(it - 1) == '(') {
      Lexeme unary;
      unary.value = 0.0f;
      unary.priority = Priority::kPriorityLevel_0;
      unary.type = Type::kNumber;
      reversed_polish_notation_.push_back(unary);
    }
  } else if (*it == '*' || *it == '/') {
    lexeme.priority = Priority::kPriorityLevel_2;
  } else if (*it == 'm') {
    lexeme.priority = Priority::kPriorityLevel_3;
    pointer_move = 3;
  } else if (*it == '^') {
    lexeme.priority = Priority::kPriorityLevel_3;
  }

  if (operators_.empty()) {
    operators_.push(lexeme);
  } else {
    Priority previous_operator_priority = operators_.top().priority;
    Priority current_operator_priority = lexeme.priority;
    if (previous_operator_priority < current_operator_priority ||
        ((previous_operator_priority <= current_operator_priority) &&
         *it == '^')) {
      operators_.push(lexeme);
    } else if (operators_.top().value == SQRT) {
      operators_.push(lexeme);
    } else {
      while ((*it != '^' &&
              (!operators_.empty() &&
               ((previous_operator_priority != Priority::kPriorityLevel_4) &&
                previous_operator_priority >= current_operator_priority))) ||
             (*it == '^' &&
              (!operators_.empty() &&
               (previous_operator_priority > current_operator_priority)))) {
        previous_lexeme = operators_.top();
        reversed_polish_notation_.push_back(previous_lexeme);
        operators_.pop();
        if (!operators_.empty()) {
          previous_lexeme = operators_.top();
          previous_operator_priority = previous_lexeme.priority;
        }
      }
      operators_.push(lexeme);
    }
  }
  it += pointer_move;
}

void s21::Model::TrigonometryFunction(std::string::const_iterator &it) {
  Lexeme lexeme;
  lexeme.priority = Priority::kPriorityLevel_4;
  lexeme.type = Type::kOperator;
  if (*it == 'a') {
    if (*(it + 1) == 's') {
      lexeme.value = static_cast<long double>('S');
    } else if (*(it + 1) == 'c') {
      lexeme.value = static_cast<long double>('C');
    } else if (*(it + 1) == 't') {
      lexeme.value = static_cast<long double>('T');
    }
    it += 5;
  } else if (*it == 's' || *it == 'c' || *it == 't') {
    if (*(it + 1) == 'q') {
      lexeme.priority = Priority::kPriorityLevel_3;
      lexeme.value = static_cast<long double>('q');
      it += 5;
    } else {
      lexeme.value = static_cast<long double>(*it);
      it += 4;
    }
  } else if (*it == 'l') {
    if (*(it + 1) == 'o') {
      lexeme.value = static_cast<long double>('L');
      it += 4;
    } else {
      lexeme.value = static_cast<long double>('l');
      it += 3;
    }
  }
  isUnary_ = true;
  operators_.push(lexeme);
}

void s21::Model::OpenBracketFunction(std::string::const_iterator &it) {
  Lexeme lexeme;
  lexeme.value = static_cast<long double>(*it);
  lexeme.priority = Priority::kPriorityLevel_0;
  lexeme.type = Type::kOperator;
  operators_.push(lexeme);

  if (*(it + 1) == '-' || *(it + 1) == '+') {
    Lexeme unary;
    unary.value = 0.0f;
    unary.priority = Priority::kPriorityLevel_0;
    unary.type = Type::kNumber;
    reversed_polish_notation_.push_back(unary);
  }
  ++it;
}

void s21::Model::CloseBracketFunction(std::string::const_iterator &it) {
  Lexeme lexeme;
  Priority previous_operator_priority = operators_.top().priority;
  if (previous_operator_priority == Priority::kPriorityLevel_0) {
    operators_.pop();
  } else if (previous_operator_priority == Priority::kPriorityLevel_4) {
    lexeme = getOperator();
    reversed_polish_notation_.push_back(lexeme);
    operators_.pop();
  } else {
    while (!operators_.empty() &&
           previous_operator_priority != Priority::kPriorityLevel_0) {
      lexeme = getOperator();
      reversed_polish_notation_.push_back(lexeme);
      operators_.pop();
      if (!operators_.empty()) {
        previous_operator_priority = operators_.top().priority;
      }
    }
    if (previous_operator_priority == Priority::kPriorityLevel_0)
      operators_.pop();
  }
  ++it;
}
