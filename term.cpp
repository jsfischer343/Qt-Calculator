#include "term.h"


Term::FunctionHandler::FunctionHandler(int functionType, double* args, int args_L)
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

bool Term::FunctionHandler::resolve()
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
double Term::FunctionHandler::getResult()
{
    return result;
}

int Term::FunctionHandler::getExpectedNumOfArgs(int functionType)
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
void Term::FunctionHandler::resolve_Modulus()
{
    result = (int)args[0] % (int)args[1];
}
void Term::FunctionHandler::resolve_Sin()
{
    result = sin(args[0]);
}
void Term::FunctionHandler::resolve_Cos()
{
    result = cos(args[0]);
}
void Term::FunctionHandler::resolve_Tan()
{
    result = tan(args[0]);
}


Term::Term()
{}
Term::Term(double number)
{
    this->value = number;
}
Term::Term(int functionType, double* args, int args_L)
{
    FunctionHandler functionHandler = FunctionHandler(functionType, args, args_L);
    this->value = functionHandler.getResult();
}
Term::Term(int functionType, Term* termArgs, int termArgs_L)
{
    int args_L = termArgs_L;
    double* args = new double[args_L];
    for(int i=0;i<termArgs_L;i++)
    {
        args[i] = termArgs[i].getValue();
    }
    FunctionHandler functionHandler = FunctionHandler(functionType, args, args_L);
    this->value = functionHandler.getResult();
    delete[] args;
}

double Term::getValue()
{
    return value;
}
