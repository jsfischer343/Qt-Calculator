#include "calculator.h"

Calculator::Calculator()
{
    calcBuffer_L = 0;
    calcBuffer = new char[200];
    for(int i=0;i<200;i++)
    {
        calcBuffer[i] = '\0';
    }

    //Buffer conversion variables
    execCalc_numberPartBuffer_L = 0;
    execCalc_numberPartBuffer = new double[100];
    execCalc_decimalPartBuffer_L = 0;
    execCalc_decimalPartBuffer = new double[100];
    decimalPartActive = false;
    mainExpression = new Expression();
}
Calculator::~Calculator()
{
    delete mainExpression;
    delete[] calcBuffer;
}

char* Calculator::getBuffer()
{
    return calcBuffer;
}
void Calculator::appendToBuffer(char input)
{
    calcBuffer[calcBuffer_L] = input;
    calcBuffer_L++;
}
void Calculator::eraseFromBuffer()
{
    calcBuffer[calcBuffer_L-1] = '\0';
    calcBuffer_L--;
}
void Calculator::clearBuffer()
{
    for(int i=0;i<200;i++)
    {
        calcBuffer[i] = '\0';
    }
    calcBuffer_L=0;
    mainExpression->clear();
}

void Calculator::execCalc()
{
    mainExpression->clear();
    for(int i=0;i<calcBuffer_L;i++)
    {
        if(calcBuffer[i]=='(')
        {
            execCalc_pushAndFlushNumBuf();
            if(!mainExpression->pushParenthesis('('))
            {
                mainExpression->clear();
                throw 1051;
            }
        }
        else if(calcBuffer[i]==')')
        {
            execCalc_pushAndFlushNumBuf();
            if(!mainExpression->pushParenthesis(')'))
            {
                mainExpression->clear();
                throw 1051;
            }
        }
        else if(calcBuffer[i]=='+')
        {
            execCalc_pushAndFlushNumBuf();
            if(!mainExpression->pushOperation('+'))
            {
                mainExpression->clear();
                throw 1051;
            }
        }
        else if(calcBuffer[i]=='-')
        {
            execCalc_pushAndFlushNumBuf();
            if(!mainExpression->pushOperation('-'))
            {
                mainExpression->clear();
                throw 1051;
            }
        }
        else if(calcBuffer[i]=='*')
        {
            execCalc_pushAndFlushNumBuf();
            if(!mainExpression->pushOperation('*'))
            {
                mainExpression->clear();
                throw 1051;
            }
        }
        else if(calcBuffer[i]=='/')
        {
            execCalc_pushAndFlushNumBuf();
            if(!mainExpression->pushOperation('/'))
            {
                mainExpression->clear();
                throw 1051;
            }
        }
        else if(calcBuffer[i]=='^')
        {
            execCalc_pushAndFlushNumBuf();
            if(!mainExpression->pushOperation('^'))
            {
                mainExpression->clear();
                throw 1051;
            }
        }
        else if(calcBuffer[i]=='0'||
                   calcBuffer[i]=='1' ||
                   calcBuffer[i]=='2' ||
                   calcBuffer[i]=='3' ||
                   calcBuffer[i]=='4' ||
                   calcBuffer[i]=='5' ||
                   calcBuffer[i]=='6' ||
                   calcBuffer[i]=='7' ||
                   calcBuffer[i]=='8' ||
                   calcBuffer[i]=='9')
        {
            if(decimalPartActive)
            {
                execCalc_decimalPartBuffer[execCalc_decimalPartBuffer_L] = (double)((int)calcBuffer[i]-48);
                execCalc_decimalPartBuffer_L++;
            }
            else
            {
                execCalc_numberPartBuffer[execCalc_numberPartBuffer_L] = (double)((int)calcBuffer[i]-48);
                execCalc_numberPartBuffer_L++;
            }
        }
        else if(calcBuffer[i]=='.')
        {
            if(decimalPartActive)
            {
                mainExpression->clear();
                throw 1051;
            }
            else
            {
                decimalPartActive = true;
            }
        }
        else
        {
            //handle functions and embedded terms
        }
    }
    execCalc_pushAndFlushNumBuf();
    sprintf(calcBuffer,"%g",mainExpression->getResult());
    for(int i=0;i<200;i++)
    {
        if(calcBuffer[i]=='\0')
        {
            calcBuffer_L = i;
            break;
        }
    }
}

void Calculator::execCalc_pushAndFlushNumBuf()
{
    if(execCalc_numberPartBuffer_L==0 && execCalc_decimalPartBuffer_L==0)
    {
        return;
    }
    double sum = 0;
    for(int i=0;i<execCalc_numberPartBuffer_L;i++)
    {
        sum = sum+(execCalc_numberPartBuffer[i]*pow(10,execCalc_numberPartBuffer_L-i-1));
    }
    for(int i=0;i<execCalc_decimalPartBuffer_L;i++)
    {
        sum = sum+(execCalc_decimalPartBuffer[i]*pow(10,(i+1)*-1));
    }
    decimalPartActive = false;
    execCalc_numberPartBuffer_L = 0;
    execCalc_decimalPartBuffer_L = 0;
    if(!mainExpression->pushTerm(new Term(sum)))
    {
        mainExpression->clear();
        throw 1051;
    }
}
