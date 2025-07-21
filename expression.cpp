#include "expression.h"

Expression::ExpressionItem::ExpressionItem(Term* newTerm)
{
    this->termPtr = newTerm;
    this->operation = '\0';
    this->parenthesis = 0;
}
Expression::ExpressionItem::ExpressionItem(char newOpOrParenthesis)
{
    if(newOpOrParenthesis=='(' || newOpOrParenthesis==')')
    {
        this->termPtr = NULL;
        this->operation = '\0';
        this->parenthesis = newOpOrParenthesis;
    }
    else
    {
        this->termPtr = NULL;
        this->operation = newOpOrParenthesis;
        this->parenthesis = 0;
    }
}
bool Expression::ExpressionItem::isTerm()
{
    if(termPtr!=NULL)
    {
        return true;
    }
    return false;
}
bool Expression::ExpressionItem::isOperation()
{
    if(operation!='\0')
    {
        return true;
    }
    return false;
}
bool Expression::ExpressionItem::isParenthesis()
{
    if(parenthesis=='(' || parenthesis==')')
    {
        return true;
    }
    return false;
}
Term* Expression::ExpressionItem::getTerm()
{
    return termPtr;
}
char Expression::ExpressionItem::getOperation()
{
    return operation;
}
int8_t Expression::ExpressionItem::getParenthesis()
{
    return parenthesis;
}

Expression::Expression()
{
    expressionItemArr_L = 0;
    expressionItemArr = NULL;
    resultCalculated = false;
    alternator = 0;
    parenthesisStack = 0;
}
Expression::~Expression()
{
    if(expressionItemArr!=NULL)
    {
        for(int i=0;i<expressionItemArr_L;i++)
        {
            delete expressionItemArr[i];
        }
        delete[] expressionItemArr;
    }
}

bool Expression::pushTerm(Term* termPtr)
{
    if(alternator==1)
    {
        return false; //error: an operation was expected but a term was given
    }
    if(expressionItemArr_L==0)
    {
        if(expressionItemArr!=NULL)
        {
            return false; //error: expressionItemArr should be NULL if length is 0
        }
        expressionItemArr = new ExpressionItem*[1];
        expressionItemArr[1] = new ExpressionItem(termPtr);
        expressionItemArr_L = 1;
        alternator = 1;
        return true;
    }
    else
    {
        int newExpressionItemArr_L = expressionItemArr_L+1;
        ExpressionItem** newExpressionItemArr = new ExpressionItem*[newExpressionItemArr_L];
        int oldExpressionItemArr_L = expressionItemArr_L;
        ExpressionItem** oldExpressionItemArr = expressionItemArr;

        for(int i=0;i<oldExpressionItemArr_L;i++)
        {
            newExpressionItemArr[i] = oldExpressionItemArr[i];
        }
        newExpressionItemArr[newExpressionItemArr_L-1] = new ExpressionItem(termPtr); //push newest item to the end

        expressionItemArr_L = newExpressionItemArr_L;
        expressionItemArr = newExpressionItemArr;

        for(int i=0;i<oldExpressionItemArr_L;i++)
        {
            delete oldExpressionItemArr[i];
        }
        delete[] oldExpressionItemArr;

        alternator = 1;
        return true;
    }
}

bool Expression::pushOperation(char operation)
{
    if(alternator==0)
    {
        return false; //error: an operation was expected but a term was given
    }
    if(operation!='+'||operation!='-'||operation!='*'||operation!='/'||operation!='^')
    {
        return false; //error: not a valid operation
    }
    if(expressionItemArr_L==0)
    {
        if(expressionItemArr!=NULL)
        {
            return false; //error: expressionItemArr should be NULL if length is 0
        }
        expressionItemArr = new ExpressionItem*[1];
        expressionItemArr[1] = new ExpressionItem(operation);
        expressionItemArr_L = 1;
        alternator = 0;
        return true;
    }
    else
    {
        int newExpressionItemArr_L = expressionItemArr_L+1;
        ExpressionItem** newExpressionItemArr = new ExpressionItem*[newExpressionItemArr_L];
        int oldExpressionItemArr_L = expressionItemArr_L;
        ExpressionItem** oldExpressionItemArr = expressionItemArr;

        for(int i=0;i<oldExpressionItemArr_L;i++)
        {
            newExpressionItemArr[i] = oldExpressionItemArr[i];
        }
        newExpressionItemArr[newExpressionItemArr_L-1] = new ExpressionItem(operation); //push newest item to the end

        expressionItemArr_L = newExpressionItemArr_L;
        expressionItemArr = newExpressionItemArr;

        for(int i=0;i<oldExpressionItemArr_L;i++)
        {
            delete oldExpressionItemArr[i];
        }
        delete[] oldExpressionItemArr;

        alternator = 0;
        return true;
    }
}

bool Expression::pushParenthesis(char parenthesis)
{
    if(parenthesis=='(')
    {
        parenthesisStack++;
        if(parenthesisStack<0)
        {
            return false; //error: invalid parenthesis syntax
        }
    }
    else if(parenthesis==')')
    {
        parenthesisStack--;
        if(parenthesisStack<0)
        {
            return false; //error: invalid parenthesis syntax
        }
    }
    else
    {
        return false; //error: not a prenthesis input
    }
    if(expressionItemArr_L==0)
    {
        if(expressionItemArr!=NULL)
        {
            return false; //error: expressionItemArr should be NULL if length is 0
        }
        expressionItemArr = new ExpressionItem*[1];
        expressionItemArr[1] = new ExpressionItem(parenthesis);
        expressionItemArr_L = 1;
        return true;
    }
    else
    {
        int newExpressionItemArr_L = expressionItemArr_L+1;
        ExpressionItem** newExpressionItemArr = new ExpressionItem*[newExpressionItemArr_L];
        int oldExpressionItemArr_L = expressionItemArr_L;
        ExpressionItem** oldExpressionItemArr = expressionItemArr;

        for(int i=0;i<oldExpressionItemArr_L;i++)
        {
            newExpressionItemArr[i] = oldExpressionItemArr[i];
        }
        newExpressionItemArr[newExpressionItemArr_L-1] = new ExpressionItem(parenthesis); //push newest item to the end

        expressionItemArr_L = newExpressionItemArr_L;
        expressionItemArr = newExpressionItemArr;

        for(int i=0;i<oldExpressionItemArr_L;i++)
        {
            delete oldExpressionItemArr[i];
        }
        delete[] oldExpressionItemArr;
        return true;
    }
}

bool Expression::popItem()
{
    if(expressionItemArr_L>=2)
    {
        int newExpressionItemArr_L = expressionItemArr_L-1;
        ExpressionItem** newExpressionItemArr = new ExpressionItem*[newExpressionItemArr_L];
        int oldExpressionItemArr_L = expressionItemArr_L;
        ExpressionItem** oldExpressionItemArr = expressionItemArr;

        for(int i=0;i<newExpressionItemArr_L;i++)
        {
            newExpressionItemArr[i] = oldExpressionItemArr[i];
        }

        expressionItemArr_L = newExpressionItemArr_L;
        expressionItemArr = newExpressionItemArr;

        for(int i=0;i<oldExpressionItemArr_L;i++)
        {
            delete oldExpressionItemArr[i];
        }
        delete[] oldExpressionItemArr;
        return true;
    }
    else if(expressionItemArr_L==1)
    {
        delete expressionItemArr[0];
        delete[] expressionItemArr;
        expressionItemArr = NULL;
        expressionItemArr_L = 0;
        return true;
    }
    else
    {
        return false; //empty array
    }
}

double Expression::getResult()
{
    if(resultCalculated==false)
    {
        resolve();
        return result;
    }
    else
    {
        return result;
    }
}

bool Expression::resolve()
{
    //Code to resolve expression and gain result as number
}
