#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "term.h"

class Expression
{
public:
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
        char getParenthesis();
    };

    int expressionItemArr_L;
    ExpressionItem** expressionItemArr; //An array of ExpressionItem pointers that allows for a pseudo multi-type array
    bool resultCalculated;
    double result;
    bool alternator; //used to keep track of whether a term or an operation should be next
    int parenthesisStack;
    int error;

    Expression();
    ~Expression();
    bool pushTerm(Term* termPtr);
    bool pushOperation(char operation);
    bool pushParenthesis(char parenthesis);
    bool popItem();
    void clear();
    ExpressionItem* at(int index);
    int size();
    double getResult();

private:
    bool resolve(); //do calculations to get result
    double resolve_recursive(Expression* expressionToResolve);
    void resolve_merge(Expression* expressionToMerge, int start, int end, double value); //used to merge part of the expression down after that portion has been resolved
    double resolve_calcAndMerge(Expression* expressionToCalcAndMerge, int index); //performs the operation on index and index+2 using index+1 merges the three indexes
    void resolve_calcAndMerge_merge(Expression* expressionToMerge, int index, double value); //performs the merge portion of the calc and merge method

    void throwError();
};

#endif // EXPRESSION_H
