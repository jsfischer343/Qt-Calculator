#include "calculator.h"

Calculator::Calculator()
{
    inputBuffer_L = 0;
    inputBuffer = new char[200];
    for(int i=0;i<200;i++)
    {
        inputBuffer[i] = '\0';
    }
    outputBuffer_L = 0;
    outputBuffer = new char[200];
    for(int i=0;i<200;i++)
    {
        outputBuffer[i] = '\0';
    }
}
Calculator::~Calculator()
{
    delete[] inputBuffer;
}

char* Calculator::getInputBuffer()
{
    return inputBuffer;
}
char* Calculator::getOutputBuffer()
{
    return outputBuffer;
}
void Calculator::appendToInputBuffer(char input)
{
    inputBuffer[inputBuffer_L] = input;
    inputBuffer_L++;
}
void Calculator::eraseFromInputBuffer()
{
    inputBuffer[inputBuffer_L-1] = '\0';
    inputBuffer_L--;
}
void Calculator::clearInputBuffer()
{
    for(int i=0;i<200;i++)
    {
        inputBuffer[i] = '\0';
    }
    inputBuffer_L=0;
}
void Calculator::clearOutputBuffer()
{
    for(int i=0;i<200;i++)
    {
        inputBuffer[i] = '\0';
    }
    inputBuffer_L=0;
}

bool Calculator::executeCalc()
{

}
