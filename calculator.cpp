#include "calculator.h"

Calculator::Calculator()
{
    screenOutput = new char[100];
    for(int i=0;i<100;i++)
    {
        screenOutput[i]='\0';
    }
    finalValue = 0;
    digitBuffer_L = 0;
    digitBuffer = new double[100];
}
Calculator::~Calculator()
{
    delete[] screenOutput;
    delete[] digitBuffer;
}

void Calculator::inputDigit(double digit)
{
    if(digitBuffer_L<100)
    {
        digitBuffer[digitBuffer_L] = digit;
        digitBuffer_L++;
    }

    //Add to screen output
    sprintf(screenOutput, "%s%g", screenOutput,digit);
}
void Calculator::inputOperator(char operation)
{
    pushAndFlushDigitBuffer();
    mainInput.push((double)operation, 0b00000001);

    //Add to screen output
    sprintf(screenOutput, "%s%c", screenOutput,operation);
}
void Calculator::inputParenthesis(bool parenthesis)
{
    pushAndFlushDigitBuffer();
    mainInput.push(parenthesis, 0b00000010);

    //Add to screen output
    if(parenthesis==1)
    {
        sprintf(screenOutput, "%s(", screenOutput);
    }
    else
    {
        sprintf(screenOutput, "%s)", screenOutput);
    }
}
void Calculator::eraseLastInput()
{
    //if digit buffer is non-empty then remove last number
    if(digitBuffer_L!=0)
    {
        digitBuffer_L--;
        digitBuffer[digitBuffer_L] = 0;
        //get length of screenOutput
        int i=0;
        while(screenOutput[i]!='\0')
        {
            i++;
        }
        //knock off last character
        i--;
        screenOutput[i] = '\0';
    }
    //otherwise knock off last term in term object
    else
    {
        mainInput.pop();
        //get length of screenOutput
        int i=0;
        while(screenOutput[i]!='\0')
        {
            i++;
        }
        //knock off last character
        i--;
        screenOutput[i] = '\0';
    }
}
void Calculator::pushAndFlushDigitBuffer()
{
    if(digitBuffer_L==0)
    {
        return;
    }
    double pushedVal = 0;
    for(int i=0;i<digitBuffer_L;i++)
    {
        pushedVal = pushedVal+(digitBuffer[i]*pow(10,digitBuffer_L-i-1));
    }
    digitBuffer_L=0;
    mainInput.push(pushedVal, 0b00000000);
}
void Calculator::executeCalculation()
{
    this->pushAndFlushDigitBuffer();
    int subsection_start = -1;
    int subsection_end = -1;
    int parenthesisStack = 0;
    for(int i=0;i<mainInput.size();i++)
    {
        if(mainInput.isOpenParenthesis(i))
        {
            if(parenthesisStack==0)
            {
                subsection_start = i;
            }
            parenthesisStack++;
        }
        else if(mainInput.isClosedParenthesis(i))
        {
            parenthesisStack--;
            if(parenthesisStack==0)
            {
                subsection_end = i;
            }
        }
        if(subsection_start!=-1 && subsection_end!=-1)
        {
            mainInput.condenseSubsectionToSingleValue(subsection_start, subsection_end, executeCalculation_recursive(mainInput, subsection_start, subsection_end));
            i=subsection_start;
            subsection_start=-1;
            subsection_end=-1;
        }
    }
    finalValue = executeCalculation_calculate(mainInput);
    sprintf(screenOutput, "%g", finalValue);
}
double Calculator::executeCalculation_recursive(Term& parentTerm, int start, int end)
{
    start = start+1;
    end = end-1;
    Term subTerm = Term(parentTerm, start, end);

    int subsection_start = -1;
    int subsection_end = -1;
    int parenthesisStack = 0;

    for(int i=0;i<subTerm.size();i++)
    {
        if(subTerm.isOpenParenthesis(i))
        {
            if(parenthesisStack==0)
            {
                subsection_start = i;
            }
            parenthesisStack++;
        }
        else if(subTerm.isClosedParenthesis(i))
        {
            parenthesisStack--;
            if(parenthesisStack==0)
            {
                subsection_end = i;
            }
        }
        if(subsection_start!=-1 && subsection_end!=-1)
        {
            subTerm.condenseSubsectionToSingleValue(subsection_start, subsection_end, executeCalculation_recursive(subTerm, subsection_start, subsection_end));
            i=subsection_start;
            subsection_start=-1;
            subsection_end=-1;
        }
    }
    return executeCalculation_calculate(subTerm);
}
double Calculator::executeCalculation_calculate(Term& term)
{
    while(term.size()!=1)
    {
        //Addition (next operation NOT more important according to PEMDAS)
        if((char)term.at(1)=='+' && ((char)term.at(3)=='+' || (char)term.at(3)=='-' || term.at(3)==-1))
        {
            term.condenseSubsectionToSingleValue(0,2,term.at(0)+term.at(2));
        }

        //Subtraction (next operation NOT more important according to PEMDAS)
        if((char)term.at(1)=='-' && ((char)term.at(3)=='+' || (char)term.at(3)=='-' || term.at(3)==-1))
        {
            term.condenseSubsectionToSingleValue(0,2,term.at(0)-term.at(2));
        }

        //Multiplication (next operation NOT more important according to PEMDAS)
        if((char)term.at(1)=='*')
        {
            term.condenseSubsectionToSingleValue(0,2,term.at(0)*term.at(2));
        }

        //Division (next operation NOT more important according to PEMDAS)
        if((char)term.at(1)=='/')
        {
            term.condenseSubsectionToSingleValue(0,2,term.at(0)/term.at(2));
        }

        //Addition (next operation more important according to PEMDAS)
        if((char)term.at(1)=='+' && (char)term.at(3)=='*')
        {
            term.condenseSubsectionToSingleValue(2,4,term.at(2)*term.at(4));
        }
        else if((char)term.at(1)=='+' && (char)term.at(3)=='/')
        {
            term.condenseSubsectionToSingleValue(2,4,term.at(2)/term.at(4));
        }

        //Subtraction (next operation more important according to PEMDAS)
        if((char)term.at(1)=='-' && (char)term.at(3)=='*')
        {
            term.condenseSubsectionToSingleValue(2,4,term.at(2)*term.at(4));
        }
        else if((char)term.at(1)=='-' && (char)term.at(3)=='/')
        {
            term.condenseSubsectionToSingleValue(2,4,term.at(2)/term.at(4));
        }
    }
    return term.at(0);
}
char* Calculator::getScreenOutput()
{
    return screenOutput;
}
