#ifndef TERM_H
#define TERM_H
#include <bits/stdc++.h>
#include <cstdint>

class Term
{
private:
    int termArr_L;
    double* termArr;
    int8_t* termArr_flags;
    /* Flags Breakdown (16 bits)
         * [0-1]   00->Number   01->Operation  10->Parenthesis  11->Unused
         * [2]   Unused
         * [3]   Unused
         * [4]   Unused
         * [5]   Unused
         * [6]   Unused
         * [7]   Unused
     */

public:
    Term();
    Term(Term& parentTermObj, int subsection_start, int subsection_end);
    ~Term();
    double at(int index);
    int8_t at_flags(int index);
    int size();
    bool isNumber(int index);
    bool isOperation(int index);
    bool isOpenParenthesis(int index);
    bool isClosedParenthesis(int index);
    void push(double term, int8_t term_flags);
    double pop();
    double pop(int index);
    void set(double term, int8_t term_flags, int index);
    void condenseSubsectionToSingleValue(int subsection_start, int subsection_end, double value);
    void clear();
};

#endif // TERM_H
