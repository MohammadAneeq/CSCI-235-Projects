#ifndef POST_FIX_CALCULATOR_
#define POST_FIX_CALCULATOR_

#include "PrecondViolatedExcep.hpp"

#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

class PostfixCalculator{
  public:
    PostfixCalculator();
    string convertToPostfix(string infix_expression);
    double calculatePostfix(string postfix_expression);
    void testCalculator(string input_file_name);

    int precedence(char c);
    bool operator_present(string &pos);
    double compute(char c, double n1, double n2);
    bool is_error_m(string m);
    string removes_zeros_and_dot(string s);
    bool parenthesis_balanced(string p);
};

#endif
