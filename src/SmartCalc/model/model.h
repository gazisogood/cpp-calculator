#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#define CORRECT_LENGTH 255
#define SQRT 113

namespace s21 {

enum class Priority {
  kPriorityLevel_0,
  kPriorityLevel_1,
  kPriorityLevel_2,
  kPriorityLevel_3,
  kPriorityLevel_4,
  kDefaultLevel
};

enum class ReturnCode { kOk, kCalculationError, kIncorrectInput };

enum class Type { kNumber, kOperator, kDefault };

struct Lexeme {
  long double value = 0.0f;
  Priority priority = Priority::kDefaultLevel;
  Type type = Type::kDefault;
};

class Model {
 public:
  Model() : result_(0.0f){};
  ~Model() = default;

  ReturnCode getCalculationCode() { return return_code_; }
  long double getResult() { return result_; }
  void CalcResult(const std::string &mainData, const std::string &xData);

 private:
  void ConvertDataToRPN(const std::string &mainData, const std::string &xData);
  void NumbersFunction(std::string::const_iterator &it);
  void OperatorsFunction(std::string::const_iterator &itr);
  void TrigonometryFunction(std::string::const_iterator &it);
  void OpenBracketFunction(std::string::const_iterator &it);
  void CloseBracketFunction(std::string::const_iterator &it);
  void XValueFunction(std::string::const_iterator &it,
                      const std::string &xData);
  void Calculation();
  void OperandsCalculation();
  void CheckCorrectData(const std::string &mainData, const std::string &xData);

  Lexeme getOperator();
  Lexeme getNumber();
  bool isUnary_ = true;

 private:
  std::vector<Lexeme> reversed_polish_notation_;
  std::stack<Lexeme> operators_;
  std::stack<Lexeme> numbers_;
  long double result_;
  ReturnCode return_code_;
};
}  // namespace s21
#endif  // MODEL_H
