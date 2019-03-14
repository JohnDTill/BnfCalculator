#ifndef COMMUTATIVEBINARYNODE_H
#define COMMUTATIVEBINARYNODE_H

#include "binarynode.h"

class CommutativeBinaryNode : public BinaryNode{
public:
    virtual void sortChildren() override;
};

#endif // COMMUTATIVEBINARYNODE_H
