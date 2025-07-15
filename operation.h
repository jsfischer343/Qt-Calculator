#ifndef OPERATION_H
#define OPERATION_H

/*For Reference
 * '+' ~= 43
 * '-' ~= 45
 * '*' ~= 42
 * '/' ~= 47
 * '^' ~= 94
 */

class Operation
{
private:
    int operation;
public:
    Operation();
    int getOperation();
    char getOperatioAsChar();
    bool isPEMDASGreater(Operation& otherOperation);
    bool isPEMDASEqual(Operation& otherOperation);
    bool isPEMDASLesser(Operation& otherOperation);
};

#endif // OPERATION_H
