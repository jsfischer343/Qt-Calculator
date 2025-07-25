#include "expression.h"

Expression::ExpressionItem::ExpressionItem(Term* newTerm)
{
    this->termPtr = newTerm;
    this->operation = '\0';
    this->parenthesis = '\0';
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
        this->parenthesis = '\0';
    }
}
Expression::ExpressionItem::~ExpressionItem()
{}

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
char Expression::ExpressionItem::getParenthesis()
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
    error = 0;
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
        expressionItemArr[0] = new ExpressionItem(termPtr);
        expressionItemArr_L = 1;
        alternator = 1;
        //clear result status
        resultCalculated = false;
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

        //clear result status
        resultCalculated = false;

        expressionItemArr_L = newExpressionItemArr_L;
        expressionItemArr = newExpressionItemArr;

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
    if(operation!='+' && operation!='-' && operation!='*' && operation!='/' && operation!='^')
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
        expressionItemArr[0] = new ExpressionItem(operation);
        expressionItemArr_L = 1;
        alternator = 0;
        //clear result status
        resultCalculated = false;
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

        //clear result status
        resultCalculated = false;

        expressionItemArr_L = newExpressionItemArr_L;
        expressionItemArr = newExpressionItemArr;

        delete[] oldExpressionItemArr;

        alternator = 0;
        return true;
    }
}

bool Expression::pushParenthesis(char parenthesis)
{
    if(parenthesis=='(')
    {
        if(alternator==1)
        {
            return false; //error: expecting operator first
        }
        parenthesisStack++;
    }
    else if(parenthesis==')')
    {
        if(alternator==0)
        {
            return false; //error: expecting term first
        }
        if(parenthesisStack==0)
        {
            return false; //error: invalid parenthesis syntax
        }
        parenthesisStack--;
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
        expressionItemArr[0] = new ExpressionItem(parenthesis);
        expressionItemArr_L = 1;
        //clear result status
        resultCalculated = false;
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

        //clear result status
        resultCalculated = false;

        expressionItemArr_L = newExpressionItemArr_L;
        expressionItemArr = newExpressionItemArr;

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

        //update parenthesisStack if relevent
        if(oldExpressionItemArr[oldExpressionItemArr_L-1]->getParenthesis()=='(')
        {
            parenthesisStack--;
        }
        else if(oldExpressionItemArr[oldExpressionItemArr_L-1]->getParenthesis()==')')
        {
            parenthesisStack++;
        }
        //clear result status
        resultCalculated = false;

        expressionItemArr_L = newExpressionItemArr_L;
        expressionItemArr = newExpressionItemArr;

        delete oldExpressionItemArr[oldExpressionItemArr_L-1];
        delete[] oldExpressionItemArr;
        return true;
    }
    else if(expressionItemArr_L==1)
    {
        delete expressionItemArr[0];
        delete[] expressionItemArr;
        expressionItemArr = NULL;
        expressionItemArr_L = 0;
        alternator = 0;
        resultCalculated = false;
        result = 0;
        parenthesisStack = 0;
        return true;
    }
    else
    {
        return false; //empty array
    }
}

void Expression::clear()
{
    if(expressionItemArr!=NULL)
    {
        for(int i=0;i<expressionItemArr_L;i++)
        {
            delete expressionItemArr[i];
        }
        delete[] expressionItemArr;
    }
    expressionItemArr = NULL;
    expressionItemArr_L = 0;
    alternator = 0;
    resultCalculated = false;
    result = 0;
    parenthesisStack = 0;
    error = 0;
}

Expression::ExpressionItem* Expression::at(int index)
{
    return expressionItemArr[index];
}

int Expression::size()
{
    return expressionItemArr_L;
}

double Expression::getResult()
{
    if(resultCalculated==false)
    {
        if(resolve())
        {
            if(error!=0)
            {
                this->throwError();
            }
            return result;
        }
        else
        {
            this->throwError();
        }
    }
    else
    {
        return result;
    }
}

bool Expression::resolve()
{
    result = resolve_recursive(this);
    return true;
}

double Expression::resolve_recursive(Expression* expressionToResolve)
{
    if(expressionToResolve->parenthesisStack!=0)
    {
        error = 1071; //error: invalid parenthesis syntax
        return 1;
    }
    else if(expressionToResolve->alternator==0)
    {
        error = 1072; //error: expression ends in operator
        return 1;
    }
    else
    {
        //Resolve and merge all parenthesis using recursion
        bool startParFound = false;
        int startPar;
        bool endParFound = false;
        int endPar;
        double tempRecursiveResult;
        int tempParenthesisStack = 0;
        for(int i=0;i<expressionToResolve->expressionItemArr_L;i++)
        {
            if(expressionToResolve->expressionItemArr[i]->isParenthesis())
            {
                if(expressionToResolve->expressionItemArr[i]->getParenthesis()=='(')
                {
                    if(!startParFound && tempParenthesisStack==0)
                    {
                        startPar = i;
                        startParFound = true;
                    }
                    tempParenthesisStack++;
                }
                else if(expressionToResolve->expressionItemArr[i]->getParenthesis()==')')
                {
                    tempParenthesisStack--;
                    if(!endParFound && tempParenthesisStack==0)
                    {
                        endPar = i;
                        endParFound = true;
                    }

                }
            }
            if(startParFound && endParFound)
            {
                startParFound = false;
                endParFound = false;
                //Create subexpression from current expression
                Expression* subExpression = new Expression();
                for(int j=startPar+1;j<(endPar-startPar)+startPar;j++) //doesn't include the outer parenthesis themselves
                {
                    if(expressionToResolve->at(j)->isTerm())
                    {
                        subExpression->pushTerm(expressionToResolve->at(j)->getTerm());
                    }
                    else if(expressionToResolve->at(j)->isOperation())
                    {
                        subExpression->pushOperation(expressionToResolve->at(j)->getOperation());
                    }
                    else if(expressionToResolve->at(j)->isParenthesis())
                    {
                        subExpression->pushParenthesis(expressionToResolve->at(j)->getParenthesis());
                    }
                }
                //Feed that subexpression into recursive resolve
                // &
                //Merge subexpression range down to single double value provided by recursive resolve
                resolve_merge(expressionToResolve,startPar,endPar,resolve_recursive(subExpression));
                i=startPar;
                delete subExpression;
            }
            if(tempParenthesisStack<0)
            {
                error = 1901;
            }
        }
        //Resolve all operations down to single term which acts as final answer
        while(expressionToResolve->expressionItemArr_L!=1)
        {
            resolve_calcAndMerge(expressionToResolve,0);
        }
        return expressionToResolve->expressionItemArr[0]->getTerm()->getValue();
    }
}

void Expression::resolve_merge(Expression* expressionToMerge, int start, int end, double value)
{
    if(start>expressionToMerge->expressionItemArr_L || end>expressionToMerge->expressionItemArr_L || end<=start)
    {
        error = 1023; //error: invalid indexes
    }
    else
    {
        int mergeSize = end-start;
        int newExpressionItemArr_L = expressionToMerge->expressionItemArr_L-mergeSize;
        ExpressionItem** newExpressionItemArr = new ExpressionItem*[newExpressionItemArr_L];
        int oldExpressionItemArr_L = expressionToMerge->expressionItemArr_L;
        ExpressionItem** oldExpressionItemArr = expressionToMerge->expressionItemArr;

        for(int i=0;i<start;i++)
        {
            newExpressionItemArr[i] = oldExpressionItemArr[i];
        }
        newExpressionItemArr[start] = new ExpressionItem(new Term(value));
        for(int i=start+mergeSize+1;i<oldExpressionItemArr_L && i-mergeSize<newExpressionItemArr_L;i++)
        {
            newExpressionItemArr[i-mergeSize] = oldExpressionItemArr[i];
        }

        expressionToMerge->expressionItemArr_L = newExpressionItemArr_L;
        expressionToMerge->expressionItemArr = newExpressionItemArr;

        for(int i=start;i<=end;i++)
        {
            delete oldExpressionItemArr[i];
        }
        delete[] oldExpressionItemArr;
    }
}

double Expression::resolve_calcAndMerge(Expression* expressionToCalcAndMerge, int index)
{
    if(index>expressionToCalcAndMerge->expressionItemArr_L-1)
    {
        error = 1030; //error: out of range
        return 1;
    }
    if(expressionToCalcAndMerge->expressionItemArr[index]->isTerm()==false)
    {
        error = 1031; //error: invalid index (can't calc and merge on an operation index)
        return 1;
    }
    if(expressionToCalcAndMerge->expressionItemArr_L==2)
    {
        error = 1032; //error: ???
        return 1;
    }
    if(expressionToCalcAndMerge->expressionItemArr_L==1)
    {
        return expressionToCalcAndMerge->expressionItemArr[index]->getTerm()->getValue();
    }
    char thisOperation = expressionToCalcAndMerge->expressionItemArr[index+1]->getOperation();
    char nextOperation = '\0';
    char nextNextOperation = '\0';
    double val1 = expressionToCalcAndMerge->expressionItemArr[index]->getTerm()->getValue();
    double val2 = expressionToCalcAndMerge->expressionItemArr[index+2]->getTerm()->getValue();
    double val3 = 0; //expressionToCalcAndMerge->expressionItemArr[index+4]->getTerm()->getValue();
    double val4 = 0; //expressionToCalcAndMerge->expressionItemArr[index+6]->getTerm()->getValue();
    double tempResult = -1;

    if(index+3<expressionToCalcAndMerge->expressionItemArr_L-1)
    {
        nextOperation = expressionToCalcAndMerge->expressionItemArr[index+3]->getOperation();
        val3 = expressionToCalcAndMerge->expressionItemArr[index+4]->getTerm()->getValue();
        if(index+5<expressionToCalcAndMerge->expressionItemArr_L-1)
        {
            nextNextOperation = expressionToCalcAndMerge->expressionItemArr[index+5]->getOperation();
            val4 = expressionToCalcAndMerge->expressionItemArr[index+6]->getTerm()->getValue();
        }
    }

    if(nextOperation=='\0')
    {
        //PEMDAS and calculate
        if(thisOperation=='+'||thisOperation=='-')
        {
            if(thisOperation=='+')
            {
                tempResult = val1+val2;
                resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                return tempResult;
            }
            else
            {
                tempResult = val1-val2;
                resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                return tempResult;
            }
        }
        else if(thisOperation=='*'||thisOperation=='/')
        {
            if(thisOperation=='*')
            {
                tempResult = val1*val2;
                resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                return tempResult;
            }
            else
            {
                tempResult = val1/val2;
                resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                return tempResult;
            }
        }
        else if(thisOperation=='^')
        {
            tempResult = pow(val1,val2);
            resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
            return tempResult;
        }
        else
        {
            error = 1040;
            return 1;
        }
    }
    else if(nextNextOperation=='\0')
    {
        //PEMDAS and calculate
        if(thisOperation=='+'||thisOperation=='-')
        {
            if(nextOperation=='^')
            {
                tempResult = pow(val2,val3);
                resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                return tempResult;
            }
            else if(nextOperation=='*'||nextOperation=='/')
            {
                if(thisOperation=='*')
                {
                    tempResult = val2*val3;
                    resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                    return tempResult;
                }
                else
                {
                    tempResult = val2/val3;
                    resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                    return tempResult;
                }
            }
            else
            {
                if(thisOperation=='+')
                {
                    tempResult = val1+val2;
                    resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                    return tempResult;
                }
                else
                {
                    tempResult = val1-val2;
                    resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                    return tempResult;
                }
            }
        }
        else if(thisOperation=='*'||thisOperation=='/')
        {
            if(nextOperation=='^')
            {
                tempResult = pow(val2,val3);
                resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                return tempResult;
            }
            else
            {
                if(thisOperation=='*')
                {
                    tempResult = val1*val2;
                    resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                    return tempResult;
                }
                else
                {
                    tempResult = val1/val2;
                    resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                    return tempResult;
                }
            }
        }
        else if(thisOperation=='^')
        {
            tempResult = pow(val1,val2);
            resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
            return tempResult;
        }
        else
        {
            error = 1040;
            return 1;
        }
    }
    else
    {
        //PEMDAS and calculate
        if(thisOperation=='+'||thisOperation=='-')
        {
            if(nextOperation=='^')
            {
                tempResult = pow(val2,val3);
                resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                return tempResult;
            }
            else if(nextOperation=='*'||nextOperation=='/')
            {
                if(nextNextOperation=='^')
                {
                    tempResult = pow(val3,val4);
                    resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                    return tempResult;
                }
                else
                {
                    if(thisOperation=='*')
                    {
                        tempResult = val2*val3;
                        resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                        return tempResult;
                    }
                    else
                    {
                        tempResult = val2/val3;
                        resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                        return tempResult;
                    }
                }
            }
            else
            {
                if(thisOperation=='+')
                {
                    tempResult = val1+val2;
                    resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                    return tempResult;
                }
                else
                {
                    tempResult = val1-val2;
                    resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                    return tempResult;
                }
            }
        }
        else if(thisOperation=='*'||thisOperation=='/')
        {
            if(nextOperation=='^')
            {
                tempResult = pow(val2,val3);
                resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                return tempResult;
            }
            else
            {
                if(thisOperation=='*')
                {
                    tempResult = val1*val2;
                    resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                    return tempResult;
                }
                else
                {
                    tempResult = val1/val2;
                    resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
                    return tempResult;
                }
            }
        }
        else if(thisOperation=='^')
        {
            tempResult = pow(val1,val2);
            resolve_calcAndMerge_merge(expressionToCalcAndMerge,index,tempResult);
            return tempResult;
        }
        else
        {
            error = 1040;
            return 1;
        }
    }
}

void Expression::resolve_calcAndMerge_merge(Expression* expressionToMerge, int index, double value)
{
    if(expressionToMerge->expressionItemArr_L<3)
    {
        return;
    }
    int newExpressionItemArr_L = expressionToMerge->expressionItemArr_L-2;
    ExpressionItem** newExpressionItemArr = new ExpressionItem*[newExpressionItemArr_L];
    int oldExpressionItemArr_L = expressionToMerge->expressionItemArr_L;
    ExpressionItem** oldExpressionItemArr = expressionToMerge->expressionItemArr;

    for(int i=0;i<index;i++)
    {
        newExpressionItemArr[i] = oldExpressionItemArr[i];
    }
    newExpressionItemArr[index] = new ExpressionItem(new Term(value));
    for(int i=index+3;i<oldExpressionItemArr_L && i-2<newExpressionItemArr_L;i++)
    {
        newExpressionItemArr[i-2] = oldExpressionItemArr[i];
    }

    expressionToMerge->expressionItemArr_L = newExpressionItemArr_L;
    expressionToMerge->expressionItemArr = newExpressionItemArr;


    delete oldExpressionItemArr[index];
    delete oldExpressionItemArr[index+1];
    delete oldExpressionItemArr[index+2];
    delete[] oldExpressionItemArr;
}

void Expression::throwError()
{
    int errorTemp = error;
    this->clear();
    throw errorTemp;
}
