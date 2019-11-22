#include "PostfixCalculator.hpp"

PostfixCalculator::PostfixCalculator(){

}

string PostfixCalculator::convertToPostfix(string infix_expression){
  int p = 0;
  stack<char> par;
  string postf = "";
  if(!parenthesis_balanced(infix_expression)){
    return "Precondition Violated Exception: Unbalanced parenthesis";
  }
  for(int i = 0; i < infix_expression.length(); i++){
    char a;
    a = infix_expression[i];
    if((a != '+') && (a != '-') && (a != '*') && (a != '/') && (a != '(')
      && (a != ')') && (isdigit(a) == false) && (a != ' '))
    {
        return "Precondition Violated Exception: Unknown operator";
    }
    if(isdigit(a)){
        postf = postf + a;
        while(isdigit(infix_expression[i+1])){
          postf = postf + infix_expression[i+1];
          i = i+1;
        }
        postf = postf + ' ';
    }
    else if(a == '('){
        par.push(a);
    }
    else if(a == '-' || a == '+' || a == '/' || a == '*'){
        while(!par.empty() && (par.top() != '(') && (precedence(a) <=
          precedence(par.top()))){
            postf = postf + par.top() + ' ';
            par.pop();
        }
        par.push(a);
    }
    else if(a == ')'){
        while(par.top() != '('){
          postf = postf + par.top() + ' ';
          par.pop();
        }
        par.pop();
    }
  }
  while(!par.empty()){
    postf = postf + par.top() + ' ';
    par.pop();
  }
  return postf;
}

double PostfixCalculator::calculatePostfix(string postfix_expression){
  double result;
    while(operator_present(postfix_expression)){
      char a;
      string num1 = "", num2 = "";
      int stop3 = 0, stop2 = 0, stop1 = 0;
      for(int i = 0; i < postfix_expression.length(); i++){
        a = postfix_expression[i];
        if((a == '-' || a == '+' || a == '/' || a == '*') && (postfix_expression[i+1] == ' ')){
          stop3 = i - 1;
          for(int j = stop3 - 1; j > 0; j--){
            if(postfix_expression[j] == ' '){
              stop2 = j;
              j = -1;
            }
          }
          for(int k = stop2 - 1; k > 0; k--){
            if(postfix_expression[k] == ' '){
              stop1 = k;
              k = -1;
            }
          }
          i = postfix_expression.length();
        }
      }
      if(stop1 == 0){
        num1 = postfix_expression.substr(stop1, (stop2 - stop1));
      }
      else{
        num1 = postfix_expression.substr(stop1 + 1, (stop2 - stop1));
      }
      num2 = postfix_expression.substr(stop2 + 1, (stop3 - stop2));
      double num1d, num2d;
      num1d = stod(num1);
      num2d = stod(num2);
      string news = to_string(compute(a, num1d, num2d));
      string news2;
      if(stop1 == 0){
        stop1 = -1;
      }
      news2 = postfix_expression.substr(0, stop1 + 1) + news + postfix_expression.substr(stop3 + 2, postfix_expression.length());
      postfix_expression = news2;
    }
  postfix_expression = removes_zeros_and_dot(postfix_expression);
  result = stod(postfix_expression);
  return result;
}

void PostfixCalculator::testCalculator(std::string input_file_name){
  string to_compute;
  ifstream receive;
  receive.open(input_file_name);
  PostfixCalculator calc;
  ofstream write_pf;
  write_pf.open("postfix.txt");
  ofstream write_results;
  write_results.open("results.txt");
  while(getline(receive, to_compute)){
    if(to_compute != ""){
      string postf, results;
      double gresult;
      postf = calc.convertToPostfix(to_compute);
      write_pf<<postf<<endl;
      if(calc.is_error_m(postf)){
        write_results<<postf<<endl;
      }
      else{
        gresult = calc.calculatePostfix(postf);
        results = to_string(gresult);
        results = removes_zeros_and_dot(results);
        write_results<<results<<endl;
      }
    }
  }
  receive.close();
  write_pf.close();
  write_results.close();
}

int PostfixCalculator::precedence(char c){
  if((c == '*') || (c == '/')){
    return 1;
  }
  return 0;
}

bool PostfixCalculator::operator_present(string &pos){
  for(int i = 0; i < pos.length(); i++){
    char a = pos[i];
    if((a == '-' || a == '+' || a == '/' || a == '*') && (pos[i - 1] == ' ')){
      return true;
    }
  }
  return false;
}

double PostfixCalculator::compute(char c, double n1, double n2){
  if(c == '-'){
    return n1 - n2;
  }
  if(c == '+'){
    return n1 + n2;
  }
  if(c == '*'){
    return n1 * n2;
  }
  if(c == '/'){
    return n1 / n2;
  }
}

bool PostfixCalculator::is_error_m(string m){
  if((m == "Precondition Violated Exception: Unknown operator") ||
    (m == "Precondition Violated Exception: Unbalanced parenthesis")){
      return true;
  }
  else{
    return false;
  }
}


string PostfixCalculator::removes_zeros_and_dot(string s){
  int  i = s.length() - 1;
  while((s.substr(i, 1) == "0") || (s.substr(i, 1) == " ")){
    i--;
    s = s.substr(0, s.length() - 1);
  }
  if(s.substr(s.length() - 1) == "."){
    s = s.substr(0, s.length() - 1);
  }
  return s;
}

bool PostfixCalculator::parenthesis_balanced(string p){
  int c = 0;
  for(int i = 0; i < p.length(); i++){
    if(p.substr(i, 1) == "("){
      c = c + 1;
    }
    if(p.substr(i, 1) == ")"){
      c = c - 1;
    }
    if(c < 0){
      return false;
    }
  }
  if(c != 0){
    return false;
  }
  return true;
}
