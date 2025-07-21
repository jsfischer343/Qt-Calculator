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
    int inputBuffer_L;
    char* inputBuffer;
    int outputBuffer_L;
    char* outputBuffer;
public:
    Calculator();
    ~Calculator();
    //Get
    char* getInputBuffer();
    char* getOutputBuffer();
    //Input
    void appendToInputBuffer(char input);
    //Erase
    void eraseFromInputBuffer(); //erase last value
    void clearInputBuffer();
    void clearOutputBuffer();
    //Calculate
    bool executeCalc();

private:
    double executeCalc_recursive(Term& parentTerm, int start, int end);
    double executeCalc_calc(Term& term);
};

#endif // CALCULATOR_H
