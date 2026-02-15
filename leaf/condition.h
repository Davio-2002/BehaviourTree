#pragma once

#include <i_node.h>

class Condition : public INode {
public:
    Rule tick(float dT) override = 0;

    void reset() override {}
};
