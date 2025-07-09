#include "calculator.h"

Calculator::Calculator()
{
    screenOutput = new char[100];
    digitBuffer_L = 0;
    digitBuffer = new char[100];
    for(int i=0;i<100;i++)
    {
        screenOutput[i]='\0';
        digitBuffer[i]='\0';
    }
}
Calculator::~Calculator()
{
    delete[] screenOutput;
    delete[] digitBuffer;
}


char* Calculator::getScreenOutput()
{
    return screenOutput;
}

void Calculator::inputDigit(char digit)
{
    if(digitBuffer_L<100)
    {
        digitBuffer[digitBuffer_L] = digit;
        digitBuffer_L++;
    }

    //Add to screen output
    sprintf(screenOutput, "%s%c", screenOutput,digit);
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
        digitBuffer[digitBuffer_L] = '\0';
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
        int bufferKnockOffSize = 1;
        //if number then entire length of number needs to be deleted
        if(mainInput.isNumber(mainInput.size()-1))
        {
            std::string numberAsString = std::to_string(mainInput.pop());
            bufferKnockOffSize = numberAsString.size();
        }
        //else just remove one character since operators and parenthesis are only 1 char long
        else
        {
            mainInput.pop();
        }
        //get length of screenOutput
        int i=0;
        while(screenOutput[i]!='\0')
        {
            i++;
        }
        for(int j=0;j<bufferKnockOffSize;j++)
        {
            i--;
            screenOutput[i] = '\0';
        }
    }
}
bool Calculator::executeCalculation()
{
    if(this->validSyntax()==false)
    {
        return false;
    }
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
    double finalValue = executeCalculation_calculate(mainInput);
    sprintf(screenOutput, "%g", finalValue);
    return true;
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

void Calculator::pushAndFlushDigitBuffer()
{
    if(digitBuffer_L==0)
    {
        return;
    }

    //Convert buffer to double and push to mainInput
    char* end = NULL;
    double valueToBePushed = strtod(digitBuffer, &end);
    mainInput.push(valueToBePushed, 0b00000000);

    //Flush buffer
    for(int i=0;i<digitBuffer_L;i++)
    {
        digitBuffer[i]='\0';
    }
    digitBuffer_L = 0;
}

bool Calculator::validSyntax()
{
    //check start and end are not operators
    if(mainInput.isOperation(0) || (mainInput.isOperation(mainInput.size()-1) && digitBuffer_L==0))
    {
        return false;
    }
    //check for bad parethesis, multiple adjacent operators
    int parenthesisStack = 0;
    bool prevIsOperator = 0;
    for(int i=0;i<mainInput.size();i++)
    {
        if(mainInput.isOpenParenthesis(i))
        {
            parenthesisStack++;
        }
        else if(mainInput.isClosedParenthesis(i))
        {
            parenthesisStack--;
        }
        if(parenthesisStack<0)
        {
            return false;
        }

        if(mainInput.isOperation(i) && prevIsOperator)
        {
            return false;
        }
        else if(mainInput.isOperation(i))
        {
            prevIsOperator = 1;
        }
        else
        {
            prevIsOperator = 0;
        }
    }
    return true;
}
