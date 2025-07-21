#ifndef TERM_H
#define TERM_H
#include <bits/stdc++.h>
#include <cmath>
/* Class Description: A single number or function contained within an expression.
*/
//Predefined number of arguments for each function
#define TERM_ARGNUM_MODULUS 2
#define TERM_ARGNUM_SIN 1
#define TERM_ARGNUM_COS 1
#define TERM_ARGNUM_TAN 1


enum FunctionEnum
{
    FunctionEnum_Modulus,
    FunctionEnum_Sin,
    FunctionEnum_Cos,
    FunctionEnum_Tan
};

class Term
{
private:
    double value;
    class FunctionHandler
    {
    private:
        int args_L;
        double* args = NULL;
        int functionType;
        double result;
    public:
        FunctionHandler(int functionType, double* args, int args_L);
        ~FunctionHandler();
        double getResult();
    private: //All functions below for use with constructor only
        int getExpectedNumOfArgs(int functionType);
        bool resolve(); //calculate the result value given the function and args, true->function calculation worked, false->error or invalid input
        //Math Functions
        void resolve_Modulus(); //double data type is used but only 'integers' are considered valid inputs
        void resolve_Sin();
        void resolve_Cos();
        void resolve_Tan();
    };

public:
    Term();
    Term(double number);
    Term(int functionType, double* args, int args_L);
    //Term(int functionType, Term* termArgs, int termArgs_L); //For embedding functions in functions
    double getValue();
};

#endif // TERM_H
