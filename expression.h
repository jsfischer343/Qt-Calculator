#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "term.h"
//(7+4)/(6-2)
class Expression
{
private:
    class ExpressionItem //used to create pseudo multi-type array for parsing the expression
    {
    private:
        Term* termPtr;
        char operation;
        char parenthesis;
    public:
        ExpressionItem(Term* newTerm);
        ExpressionItem(char newOpOrParenthesis);
        ~ExpressionItem();
        bool isTerm();
        bool isOperation();
        bool isParenthesis();
        Term* getTerm();
        char getOperation();
        int8_t getParenthesis();
    };
    int expressionItemArr_L;
    ExpressionItem** expressionItemArr; //An array of ExpressionItem pointers that allows for a pseudo multi-type array

    bool resultCalculated;
    double result;
    bool alternator; //used to keep track of whether a term or an operation should be next
    int parenthesisStack;
public:
    Expression();
    ~Expression();
    bool pushTerm(Term* termPtr);
    bool pushOperation(char operation);
    bool pushParenthesis(char parenthesis);
    bool popItem();
    double getResult();
private:
    bool resolve(); //do calculations to get result
};

#endif // EXPRESSION_H
