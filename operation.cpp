#include "operation.h"

Operation::Operation()
{

}
int Operation::getOperation()
{
    return operation;
}
char Operation::getOperatioAsChar()
{
    return (char)operation;
}
bool Operation::isPEMDASGreater(Operation& otherOperation)
{
    if((this->operation==42 || this->operation==47 || this->operation==94) && (otherOperation.getOperation()==43 || otherOperation.getOperation()==45))
    {
        return true;
    }
    else if(this->operation==94 && otherOperation.getOperation()!=94)
    {
        return true;
    }
    return false;
}
bool Operation::isPEMDASEqual(Operation& otherOperation)
{
    if((this->operation==43 || this->operation==45) && (otherOperation.getOperation()==43 || otherOperation.getOperation()==45))
    {
        return true;
    }
    else if((this->operation==42 || this->operation==47) && (otherOperation.getOperation()==42 || otherOperation.getOperation()==47))
    {
        return true;
    }
    else if(this->operation==94 && otherOperation.getOperation()==94)
    {
        return true;
    }
    return false;
}
bool Operation::isPEMDASLesser(Operation& otherOperation)
{
    if((this->operation==43 || this->operation==45) && (otherOperation.getOperation()!=43 || otherOperation.getOperation()!=45))
    {
        return true;
    }
    else if((this->operation==42 || this->operation==47) && (otherOperation.getOperation()==94))
    {
        return true;
    }
    return false;
}
