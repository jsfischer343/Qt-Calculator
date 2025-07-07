#ifndef CALCULATOR_H
#define CALCULATOR_H
//#include <bits/stdc++.h>
#include <cmath>
#include "term.h"

class Calculator
{
private:
    char* screenOutput;
    Term mainInput;
    double finalValue;
    int digitBuffer_L;
    double* digitBuffer;
public:
    Calculator();
    ~Calculator();
    char* getScreenOutput();
    void inputDigit(double digit);
    void inputOperator(char operation);
    void inputParenthesis(bool parenthesis);
    void eraseLastInput();
    void executeCalculation();
    void pushAndFlushDigitBuffer();
private:
    double executeCalculation_recursive(Term& parentTerm, int start, int end);
    double executeCalculation_calculate(Term& term);
};

#endif // CALCULATOR_H
