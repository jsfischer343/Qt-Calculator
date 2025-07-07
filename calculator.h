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
    int finalValue;
    int digitBuffer_L;
    int* digitBuffer;
public:
    Calculator();
    ~Calculator();
    char* getScreenOutput();
    void inputDigit(int digit);
    void inputOperator(char operation);
    void inputParenthesis(bool parenthesis);
    void executeCalculation();
    void pushAndFlushDigitBuffer();
private:
    int executeCalculation_recursive(Term parentTerm, int start, int end);
    int executeCalculation_calculate(Term term);
};

#endif // CALCULATOR_H
