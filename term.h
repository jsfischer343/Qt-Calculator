#ifndef TERM_H
#define TERM_H
#include <bits/stdc++.h>
#include <cmath>
/* Class Description: A single number or function contained within an expression.
*/
//Predefined number of arguments for each function
#define MODULUS_ARGNUM 2
#define SIN_ARGNUM 1
#define COS_ARGNUM 1
#define TAN_ARGNUM 1


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
    class Function
    {
    private:
        int args_L;
        double* args = NULL;
        int functionType;
        double result;
    public:
        Function(int functionType, double* args, int args_L);
        ~Function();
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
    Term(double number);
    Term(int functionType, double* args, int args_L);
    void getValue();
};

#endif // TERM_H
