#ifndef PROTOCOLEX_H
#define PROTOCOLEX_H
#include <string>
#include <exception>
class missing_ans_end : public std::exception {
public:
  const char* what() const throw() {
      return "Missing ANS_END!";
  }
};

class wrong_anstype : public std::exception {
public:
  const char* what() const throw() {
      return "Wrong answer byte!";
  }
};
#endif
