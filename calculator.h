#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <cmath>
#include <cstring>
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
    //Input
    void inputDigit(double digit);
    void inputOperator(char operation);
    void inputParenthesis(bool parenthesis);
    //Erase
    void eraseLastInput();
    //Excution
    bool executeCalculation();

private:
    double executeCalculation_recursive(Term& parentTerm, int start, int end);
    double executeCalculation_calculate(Term& term);

    void pushAndFlushDigitBuffer();
    bool fillDigitBuffer();
    //Validation
    bool validSyntax();
};

#endif // CALCULATOR_H
