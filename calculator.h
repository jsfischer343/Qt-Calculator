#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include "term.h"

class Calculator
{
private:
    char* screenOutput;
    Term mainInput;
    int digitBuffer_L;
    char* digitBuffer;
public:
    Calculator();
    ~Calculator();
    //Get
    char* getScreenOutput();
    //Input
    void inputDigitOrDecimal(char digit);
    void inputOperator(char operation);
    void inputParenthesis(bool parenthesis);
    //Erase
    void eraseLastInput();
    void clearAll();
    //Excution
    bool executeCalculation();

private:
    double executeCalculation_recursive(Term& parentTerm, int start, int end);
    double executeCalculation_calculate(Term& term);

    //Digit Buffer
    void pushAndFlushDigitBuffer();
    //Validation
    bool validSyntax();
};

#endif // CALCULATOR_H
