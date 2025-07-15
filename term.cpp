#include "term.h"


Term::Function::Function(int functionType, double* args, int args_L)
{
    this->functionType = functionType;
    this->args_L = args_L;
    this->args = args;
    bool valid = resolve(); //resolve function and store return value in valid
    if(!valid)
    {
        throw; //invalid syntax, input, or other error in function
    }
}

bool Term::Function::resolve()
{
    if(args_L==getExpectedNumOfArgs(functionType))
    {
        if(functionType==FunctionEnum_Modulus)
        {
            resolve_Modulus();
        }
        else if(functionType==FunctionEnum_Sin)
        {
            resolve_Sin();
        }
        else if(functionType==FunctionEnum_Cos)
        {
            resolve_Cos();
        }
        else if(functionType==FunctionEnum_Tan)
        {
            resolve_Tan();
        }
    }
    return false;
}
double Term::Function::getResult()
{
    return result;
}

int Term::Function::getExpectedNumOfArgs(int functionType)
{
    if(functionType==FunctionEnum_Modulus)
    {
        return MODULUS_ARGNUM;
    }
    else if(functionType==FunctionEnum_Sin)
    {
        return SIN_ARGNUM;
    }
    else if(functionType==FunctionEnum_Cos)
    {
        return COS_ARGNUM;
    }
    else if(functionType==FunctionEnum_Tan)
    {
        return TAN_ARGNUM;
    }
    return 0;
}
void Term::Function::resolve_Modulus()
{
    result = (int)args[0] % (int)args[1];
}
void Term::Function::resolve_Sin()
{
    result = sin(args[0]);
}
void Term::Function::resolve_Cos()
{
    result = cos(args[0]);
}
void Term::Function::resolve_Tan()
{
    result = tan(args[0]);
}


Term::Term(double number)
{
    this->value = number;
}
Term::Term(int functionType, double* args, int args_L)
{
    Function functionHandler = Function(functionType, args, args_L);
    this->value = functionHandler.getResult();
}
