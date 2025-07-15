#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "term.h"
#include "operation.h"

class Expression
{
private:
    int termArr_L;
    Term* termArr;
    int opArr_L;
    Operation* opArr;

    double result;
    bool alternator; //used to keep track of whether a term or an operation should be next
public:
    Expression();
    ~Expression();
    void pushTerm(Term nextTerm);
    void pushOperation(Operation nextOperation);
    bool pop();
    double getResult();
private:
    bool resolve(); //do calculations to get result
    void resolve_mergeTerms(int index); //implicit: it will be merged with the next term following the operation that sits between them
    Term resolve_mergeTerms_Calc(Term& term1, Operation& operation, Term& term2); //implicit: it will be merged with the next term following the operation that sits between them
};

#endif // EXPRESSION_H
