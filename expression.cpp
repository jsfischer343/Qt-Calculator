#include "expression.h"

Expression::Expression()
{
    termArr_L = 0;
    termArr = NULL;
    opArr_L = 0;
    opArr = NULL;
    alternator = 0;
}
Expression::~Expression()
{
    if(termArr!=NULL)
    {
        delete[] termArr;
    }
    if(opArr!=NULL)
    {
        delete[] opArr;
    }
}


void Expression::pushTerm(Term nextTerm)
{
    if(alternator==1)
    {
        throw; //error: this push should have been a operation
    }
    int newTermArr_L = termArr_L+1;
    Term* newTermArr = new Term[newTermArr_L];
    int oldTermArr_L = termArr_L;
    Term* oldTermArr = termArr;

    for(int i=0;i<oldTermArr_L;i++)
    {
        newTermArr[i] = oldTermArr[i];
    }
    newTermArr[newTermArr_L-1] = nextTerm;

    termArr_L = newTermArr_L;
    termArr = newTermArr;

    delete[] oldTermArr;
    alternator=1;
}
void Expression::pushOperation(Operation nextOperation)
{
    if(alternator==0)
    {
        throw; //error: this push should have been a term
    }
    int newOpArr_L = opArr_L+1;
    Operation* newOpArr = new Operation[newOpArr_L];
    int oldOpArr_L = opArr_L;
    Operation* oldOpArr = opArr;

    for(int i=0;i<oldOpArr_L;i++)
    {
        newOpArr[i] = oldOpArr[i];
    }
    newOpArr[newOpArr_L-1] = nextOperation;

    opArr_L = newOpArr_L;
    opArr = newOpArr;

    delete[] oldOpArr;
    alternator=0;
}
bool Expression::pop()
{
    if(alternator==0) //implies: popping an operator
    {
        if(opArr_L==0)
        {
            return false;
        }
        if(opArr_L==1)
        {
            opArr_L = 0;
            delete[] opArr;
            opArr = NULL;
            return true;
        }
        else
        {
            int newOpArr_L = opArr_L-1;
            Operation* newOpArr = new Operation[newOpArr_L];
            Operation* oldOpArr = opArr;

            for(int i=0;i<newOpArr_L;i++)
            {
                newOpArr[i] = oldOpArr[i];
            }

            opArr_L = newOpArr_L;
            opArr = newOpArr;

            delete[] oldOpArr;
            alternator=1;
            return true;
        }
    }
    else //implies: popping a term
    {
        if(termArr_L==0)
        {
            return false;
        }
        if(termArr_L==1)
        {
            termArr_L = 0;
            delete[] termArr;
            termArr = NULL;
            return true;
        }
        else
        {
            int newTermArr_L = termArr_L-1;
            Term* newTermArr = new Term[newTermArr_L];
            Term* oldTermArr = termArr;

            for(int i=0;i<newTermArr_L;i++)
            {
                newTermArr[i] = oldTermArr[i];
            }

            termArr_L = newTermArr_L;
            termArr = newTermArr;

            delete[] oldTermArr;
            alternator=0;
            return true;
        }
    }
}
double Expression::getResult()
{
    return result;
}
bool Expression::resolve()
{
    if(opArr_L-1!=termArr_L)
    {
        throw; //error: inbalanced number of operators and terms
    }
    while(termArr_L!=1)
    {
        if(opArr[0].isPEMDASLesser(opArr[1])) //if this operation is less important than the next then...
        {
            if(opArr[1].isPEMDASLesser(opArr[2])) //implicit: this would imply that opArr[i+2] is an exponential operator, so we can stop here
            {
                resolve_mergeTerms(2);
            }
            else
            {
                resolve_mergeTerms(1);
            }
        }
        else
        {
            resolve_mergeTerms(0);
        }
    }
    return termArr[0].getValue();
}
void Expression::resolve_mergeTerms(int index)
{
    int newTermArr_L = termArr_L-1;
    Term* newTermArr = new Term[newTermArr_L];
    int oldTermArr_L = termArr_L;
    Term* oldTermArr = termArr;

    int newOpArr_L = opArr_L-1;
    Operation* newOpArr = new Operation[newOpArr_L];
    int oldOpArr_L = opArr_L;
    Operation* oldOpArr = opArr;

    for(int i=0;i<index;i++)
    {
        newTermArr[i] = oldTermArr[i];
    }
    newTermArr[index] = resolve_mergeTerms_Calc(oldTermArr[index],oldOpArr[index],oldTermArr[index+1]);
    for(int i=index+2;i-2<oldTermArr_L;i++)
    {
        newTermArr[i] = oldTermArr[i];
    }

    for(int i=0;i<index;i++)
    {
        newOpArr[i] = oldOpArr[i];
    }
    for(int i=index+1;i-1<oldOpArr_L;i++)
    {
        newOpArr[i] = oldOpArr[i];
    }


    opArr_L = newOpArr_L;
    opArr = newOpArr;

    termArr_L = newTermArr_L;
    termArr = newTermArr;

    delete[] oldOpArr;
    delete[] oldTermArr;
}
Term Expression::resolve_mergeTerms_Calc(Term& term1, Operation& operation, Term& term2)
{
    double tempResult = 1;
    if(operation.getOperatioAsChar()=='+')
    {
        tempResult = term1.getValue()+term2.getValue();
    }
    else if(operation.getOperatioAsChar()=='-')
    {
        tempResult = term1.getValue()-term2.getValue();
    }
    else if(operation.getOperatioAsChar()=='*')
    {
        tempResult = term1.getValue()*term2.getValue();
    }
    else if(operation.getOperatioAsChar()=='/')
    {
        tempResult = term1.getValue()/term2.getValue();
    }
    else if(operation.getOperatioAsChar()=='^')
    {
        tempResult = pow(term1.getValue(),term2.getValue());
    }
    return Term(tempResult);
}
