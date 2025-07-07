#include "term.h"

Term::Term()
{
    termArr_L = 0;
}

Term::Term(Term& parentTermObj, int subsection_start, int subsection_end)
{
    termArr_L = subsection_end-subsection_start+1;
    termArr = new int[termArr_L];
    termArr_flags = new int8_t[termArr_L];

    //Copy subsection
    for(int i=subsection_start;i<=subsection_end;i++)
    {
        termArr[i-subsection_start] = parentTermObj.at(i);
        termArr_flags[i-subsection_start] = parentTermObj.at_flags(i);
    }
}

Term::~Term()
{
    delete[] termArr;
    delete[] termArr_flags;
}

int Term::at(int index)
{
    if(index>=termArr_L || index<0)
    {
        return -1;
    }
    else
    {
        return termArr[index];
    }
}
int8_t Term::at_flags(int index)
{
    if(index>=termArr_L || index<0)
    {
        return -1;
    }
    else
    {
        return termArr_flags[index];
    }
}
int Term::size()
{
    return termArr_L;
}
bool Term::isNumber(int index)
{
    if(index>=termArr_L || index<0)
    {
        return false;
    }
    else
    {
        if(termArr_flags[index]==0b00000000)
        {
            return true;
        }
        return false;
    }
}
bool Term::isOperation(int index)
{
    if(index>=termArr_L || index<0)
    {
        return false;
    }
    else
    {
        if(termArr_flags[index]==0b00000001)
        {
            return true;
        }
        return false;
    }
}
bool Term::isOpenParenthesis(int index)
{
    if(index>=termArr_L)
    {
        return false;
    }
    else
    {
        if(termArr[index]==1 && termArr_flags[index]==0b00000010)
        {
            return true;
        }
        return false;
    }
}
bool Term::isClosedParenthesis(int index)
{
    if(index>=termArr_L)
    {
        return false;
    }
    else
    {
        if(termArr[index]==0 && termArr_flags[index]==0b00000010)
        {
            return true;
        }
        return false;
    }
}
void Term::push(int term, int8_t term_flags)
{
    if(termArr_L==0)
    {
        termArr = new int[1];
        termArr_flags = new int8_t[1];
        termArr_L++;
        termArr[0] = term;
        termArr_flags[0] = term_flags;
    }
    else
    {
        //Setup temporary pointers
        int* new_termArr = new int[termArr_L+1];
        int* old_termArr = termArr;
        int8_t* new_termArr_flags = new int8_t[termArr_L+1];
        int8_t* old_termArr_flags = termArr_flags;

        //Copy values from old to new
        for(int i=0;i<termArr_L;i++)
        {
            new_termArr[i] = old_termArr[i];
            new_termArr_flags[i] = old_termArr_flags[i];
        }

        //"Push new value"
        new_termArr[termArr_L] = term;
        new_termArr_flags[termArr_L] = term_flags;

        //Assign global "termArr" and "termArr_flags" arrays to point to the newly created memory
        termArr = new_termArr;
        termArr_flags = new_termArr_flags;

        //Free old memory
        delete[] old_termArr;
        delete[] old_termArr_flags;

        //Increment size of TermArr
        termArr_L++;
    }
}
int Term::pop()
{
    int poppedValue = -1;
    if(termArr_L==0)
    {
        return poppedValue;
    }
    else
    {
        //Setup temporary pointers
        int* new_termArr = new int[termArr_L-1];
        int* old_termArr = termArr;
        int8_t* new_termArr_flags = new int8_t[termArr_L-1];
        int8_t* old_termArr_flags = termArr_flags;

        //Grab poppedValue
        poppedValue = old_termArr[termArr_L-1];

        //Decrement size of TermArr
        termArr_L--;

        //Copy values from old to new
        for(int i=0;i<termArr_L;i++)
        {
            new_termArr[i] = old_termArr[i];
            new_termArr_flags[i] = old_termArr_flags[i];
        }

        //Assign global "termArr" and "termArr_flags" arrays to point to the newly created memory
        termArr = new_termArr;
        termArr_flags = new_termArr_flags;

        //Free old memory
        delete[] old_termArr;
        delete[] old_termArr_flags;
    }
    return poppedValue;
}
void Term::set(int term, int8_t term_flags, int index)
{
    if(index>=termArr_L || index<0)
    {
        return;
    }
    else
    {
        termArr[index] = term;
        termArr_flags[index] = term_flags;
    }
}
void Term::condenseSubsectionToSingleValue(int subsection_start, int subsection_end, int value)
{
    int new_size = termArr_L-(subsection_end-subsection_start);

    //Setup temporary pointers
    int* new_termArr = new int[new_size];
    int* old_termArr = termArr;
    int8_t* new_termArr_flags = new int8_t[new_size];
    int8_t* old_termArr_flags = termArr_flags;

    //Copy values from old to new
    for(int i=0;i<subsection_start;i++)
    {
        new_termArr[i] = old_termArr[i];
        new_termArr_flags[i] = old_termArr_flags[i];
    }
    //Set value for condensed subsection
    new_termArr[subsection_start] = value;
    new_termArr_flags[subsection_start] = 0b00000000;
    for(int i=subsection_start+1;i<new_size;i++)
    {
        new_termArr[i] = old_termArr[i+(subsection_end-subsection_start)];
        new_termArr_flags[i] = old_termArr_flags[i+(subsection_end-subsection_start)];
    }

    //Assign global "termArr" and "termArr_flags" arrays to point to the newly created memory
    termArr = new_termArr;
    termArr_flags = new_termArr_flags;

    //Free old memory
    delete[] old_termArr;
    delete[] old_termArr_flags;

    termArr_L = new_size;
}
void Term::clear()
{
    while(termArr_L>0)
    {
        this->pop();
    }
}
