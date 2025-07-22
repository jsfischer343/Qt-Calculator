#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include "expression.h"

#define CALCULATOR_SIGNATURE_MODULUS "mod("
#define CALCULATOR_SIGNATURE_SIN "sin("
#define CALCULATOR_SIGNATURE_COS "cos("
#define CALCULATOR_SIGNATURE_TAN "tan("

class Calculator
{
private:
    int calcBuffer_L;
    char* calcBuffer;
public:
    Calculator();
    ~Calculator();
    //Get
    char* getBuffer();
    //Input
    void appendToBuffer(char input);
    //Erase
    void eraseFromBuffer(); //erase last value
    void clearBuffer();
    void clearAll();
    //Calculate
    void execCalc();

private:

    //Buffer conversion variables
    int execCalc_numberPartBuffer_L;
    double* execCalc_numberPartBuffer;
    int execCalc_decimalPartBuffer_L;
    double* execCalc_decimalPartBuffer;
    bool decimalPartActive;
    Expression* mainExpression;

    void execCalc_pushAndFlushNumBuf();
    void throw_InvalidSyntax();
};

#endif // CALCULATOR_H
